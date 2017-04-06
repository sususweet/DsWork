//
// Created by tangyq on 2017/3/11.
//

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "expressionCalculation.h"
#include "../common/expressionBase.h"

//����Ƿ�ɹ������ڴ�
#define Asert(par) if(par==NULL) {\
                printf("%s,%d �����ڴ�ʧ�ܣ�\n",__FILE__,__LINE__);\
                return NULL;}

//����������洢ֵ���ڴ�ռ�
LinkListValue linkListValue_init(){
    LinkListValue linkListValue_tmp = (LinkListValue) malloc(sizeof(LinkListValue));
    Asert(linkListValue_tmp);
    return linkListValue_tmp;
}

//C���Լ�����������
int expCalculation(){
    printf("��ӭʹ��C���Լ��׼�����\n");
    printf("CopyRight @2017 sususweet. All rights reserved.\n");
    printf("\n");
    /* �洢����ı��ʽ�ַ��� */
    char exp[1000];
    char exp_temp[1000];
    char expReform[1003] = "0+";
    double* result = NULL;
    while (1){
        puts("��������Ҫ����ı��ʽ:");
        fflush (stdin);
        gets(exp);
        strcpy(exp_temp, exp);
        strcat(expReform, exp);//�����ʽ֮ǰ��0+���Է�ֹ���ʽ��-��ͷ��������ֶ��������
        result = expCal(expReform);
        /*��������ֹ���벻�Ϸ�ʱ�������*/
        if (result == NULL){
            printf("�������������ʽ����������!�����в��ܰ�����һ���ʽ\n");
        } else{
            break;
        }
    }
    puts("����������:");
    printf("%s = ", exp_temp);
    printf("%.3f\n", *result);
    return 0;
}

//C���Լ��������ʽ���㺯�������ĺ�����
double* expCal(char* exp){
    LinkListEntry *numStack = linkList_initList();
    LinkListEntry *doubleOperateStack = linkList_initList();
    LinkListEntry *singleOperateStack = linkList_initList();
    LinkListValue numTemp;
    LinkListValue calResult = NULL;
    linkList_push(doubleOperateStack,'#');
    linkList_push(singleOperateStack,'#');

    shortenExpression(exp);

    int length = (int) strlen(exp);
    int i = 0;
    int isNegative = 0;
    while(i < length){
    //Ҳ����д�ɣ�while((*(exp + i)) != '\0') {
        char expTemp = *(exp + i);
            if (expTemp == ' ') {/* �����ո� */
                i++;
                continue;
            } else if (expTemp == '-' && isNegative == 1) {/* �����ŵ��й��߼� */
                i++;
                continue;
            } else if (expTemp == '(') { /* ���������� */
                i++;
                calResult = expCal(exp + i);
                linkList_push(numStack, calResult);    /* ���������ŵı��ʽ��ѹ��ջ�� */
                i += length;
            } else if(expTemp == ')') {
                i++;
                continue;
            } else if (expTemp >= '0' && expTemp <= '9') { /* �������� */
                numTemp = linkListValue_init();
                do {
                    *(double *) numTemp = *(double *) numTemp * 10 + ((double) (expTemp - '0'));
                    i++;
                    expTemp = *(exp + i);
                } while (expTemp >= '0' && expTemp <= '9');

                if (expTemp == '.'){/* ����С�� */
                    i++;
                    expTemp = *(exp + i);
                    int digitCount = -1;
                    while (expTemp >= '0' && expTemp <= '9') {
                        *(double *) numTemp = *(double *) numTemp + ((double) (expTemp - '0')) * pow(10,digitCount);
                        i++;
                        digitCount--;
                        expTemp = *(exp + i);
                    }
                }

                if ((char) linkList_peek(singleOperateStack) != '#'){
                    LinkListValue sOper = linkList_pop(singleOperateStack);
                    *(double *)numTemp = numSingleCal(*(double *)numTemp, (char)sOper);
                }
                if (isNegative == 1) {
                    *(double *)numTemp = - *(double *)numTemp;
                    isNegative = 0;
                }
                linkList_push(numStack, numTemp);

            } else if (!getPriority(expTemp)){/* ��Ŀ��������� */
                linkList_push(singleOperateStack,(LinkListValue *)expTemp);
                i++;
            } else {  /* ��������� */
                LinkListValue operationTop = linkList_peek(doubleOperateStack);/* ջ������� */
                if (*(exp + i + 1) == '-') {/*�ж���һ��������Ƿ�Ϊ'-'������������*/
                    isNegative = 1;
                    /*�˴����ܶ�i��λ�ý��в������Է�ֹ©�������*/
                }

                if (getPriority((char) operationTop) >= getPriority(expTemp)) { /* �Ƚ���������������ȼ� */
                    /* ������ջ���˳��������� */
                    double* value2 = (double *) linkList_pop(numStack);
                    double* value1 = (double *) linkList_pop(numStack);
                    /*��������ֹ���벻�Ϸ�ʱ�������*/
                    if (value1 == NULL || value2 == NULL) return NULL;
                    calResult = linkListValue_init();
                    *(double *) calResult = numDoubleCal(*value1, *value2, (char) operationTop);
                    linkList_push(numStack, calResult);    /* ������ѹ��ջ�� */
                    linkList_pop(doubleOperateStack); /* �����ջ����ջ */
                } else {
                    /* �����ѹ��ջ�� */
                    linkList_push(doubleOperateStack, (LinkListValue *) expTemp);
                    i++;
                }
            }
    }


    /* �������ջ�е���������������� */
    LinkListValue operationTop;
    while((char) (operationTop = linkList_peek(doubleOperateStack)) != '#') {/* ջ������� */
        /* ������ջ���˳��������� */
        double* value2 = linkList_pop(numStack);
        double* value1 = linkList_pop(numStack);
        /*��������ֹ���벻�Ϸ�ʱ�������*/
        if (value2 == NULL || value1 == NULL) return NULL;
        calResult = linkListValue_init();
        *(double *) calResult = numDoubleCal(*value1, *value2, (char) operationTop);
        linkList_push(numStack, calResult);    /* ������ѹ��ջ�� */
        linkList_pop(doubleOperateStack); /* �����ջ����ջ */
    }
    numTemp = linkList_pop(numStack);
    /*��������ֹ���벻�Ϸ�ʱ�������*/
    if (numTemp == NULL) return NULL;
    else return (double *) numTemp;
}