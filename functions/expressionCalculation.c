//
// Created by tangyq on 2017/3/11.
//

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "expressionCalculation.h"

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

//�ַ����滻����ʶ�������sin��cos�����Ǻ��������
char* shortenExpression(char* exp){
    strReplace(exp,"sin", "s");
    strReplace(exp,"cos", "c");
    strReplace(exp,"tan", "t");
    strReplace(exp,"cot", "o");
    return exp;
}

//˫Ŀ���������
double numDoubleCal(double val1, double val2, char op) {
    switch(op) {
        case '+':
            return (val1+val2);
        case '-':
            return (val1-val2);
        case '*':
            return (val1*val2);
        case '/':
            return (val1/val2);
        case '%':
            return ((int)val1 % (int)val2); //ǿ��ת�����ͣ���ֹ�������
        case '^':
            return pow(val1,val2);
        default:
            return -1;
    }
}

//��Ŀ���������
double numSingleCal(double val1, char op) {
    switch(op) {
        case 's':
            return sin(val1);
        case 'c':
            return cos(val1);
        case 't':
            return tan(val1);
        case 'o':
            return 1/tan(val1);
        default:
            return -1;
    }
}

//��ȡ��������ȼ���#���ȼ���ͣ���ֹ���������ջ��Ҳ������������
int getPriority(char op) {
    switch(op) {
        case '^':
            return 14;
        case '+':
        case '-':
            return 12;
        case '*':
        case '/':
        case '%':
            return 13;
        case ';':
        case '\0':
        case ')':
            return 2;
        case '(':
        case '#':
            return 1;
        default:
            return 0;
    }
}

//�ַ����滻����
char* strReplace(char originalString[], char key[], char swap[]){
    int lengthOfOriginalString, lengthOfKey, lengthOfSwap, i, j , flag;
    char tmp[1000];

    //��ȡ�����ַ����ĳ���
    lengthOfOriginalString = (int)strlen(originalString);
    lengthOfKey =  (int)strlen(key);
    lengthOfSwap =  (int)strlen(swap);

    for(i = 0; i <= lengthOfOriginalString - lengthOfKey; i++){
        flag = 1;
        //����key
        for(j  = 0; j < lengthOfKey; j ++){
            if(originalString[i + j] != key[j]){
                flag = 0;
                break;
            }
        }
        //��������ɹ���������滻
        if(flag){
            strcpy(tmp, originalString);
            strcpy(&tmp[i], swap);
            strcpy(&tmp[i + lengthOfSwap], &originalString[i  + lengthOfKey]);
            strcpy(originalString, tmp);
            i += lengthOfSwap - 1;
            lengthOfOriginalString =  (int)strlen(originalString);
        }
    }
}
