//
// Created by tangyq on 2017/3/11.
//

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "expressionCalculation.h"

//检查是否成功申请内存
#define Asert(par) if(par==NULL) {\
                printf("%s,%d 请求内存失败！\n",__FILE__,__LINE__);\
                return NULL;}

//申请计算器存储值的内存空间
LinkListValue linkListValue_init(){
    LinkListValue linkListValue_tmp = (LinkListValue) malloc(sizeof(LinkListValue));
    Asert(linkListValue_tmp);
    return linkListValue_tmp;
}

//C语言计算器主函数
int expCalculation(){
    printf("欢迎使用C语言简易计算器\n");
    printf("CopyRight @2017 sususweet. All rights reserved.\n");
    printf("\n");
    /* 存储输入的表达式字符串 */
    char exp[1000];
    char exp_temp[1000];
    char expReform[1003] = "0+";
    double* result = NULL;
    while (1){
        puts("请输入您要计算的表达式:");
        gets(exp);
        strcpy(exp_temp, exp);
        strcat(expReform, exp);//给表达式之前加0+，以防止表达式以-开头的情况出现而程序出错
        result = expCal(expReform);
        /*错误处理，防止输入不合法时程序崩溃*/
        if (result == NULL){
            printf("计算出错，请检查表达式并重新输入!括号中不能包括单一表达式\n");
        } else{
            break;
        }
    }
    puts("计算结果如下:");
    printf("%s = ", exp_temp);
    printf("%.3f\n", *result);
    return 0;
}

//C语言计算器表达式计算函数（核心函数）
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
    //也可以写成：while((*(exp + i)) != '\0') {
        char expTemp = *(exp + i);
            if (expTemp == ' ') {/* 跳过空格 */
                i++;
                continue;
            } else if (expTemp == '-' && isNegative == 1) {/* 处理负号的有关逻辑 */
                i++;
                continue;
            } else if (expTemp == '(') { /* 处理左括号 */
                i++;
                calResult = expCal(exp + i);
                linkList_push(numStack, calResult);    /* 计算完括号的表达式，压入栈中 */
                i += length;
            } else if(expTemp == ')') {
                i++;
                continue;
            } else if (expTemp >= '0' && expTemp <= '9') { /* 处理数字 */
                numTemp = linkListValue_init();
                do {
                    *(double *) numTemp = *(double *) numTemp * 10 + ((double) (expTemp - '0'));
                    i++;
                    expTemp = *(exp + i);
                } while (expTemp >= '0' && expTemp <= '9');

                if (expTemp == '.'){/* 处理小数 */
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

            } else if (!getPriority(expTemp)){/* 单目运算符处理 */
                linkList_push(singleOperateStack,(LinkListValue *)expTemp);
                i++;
            } else {  /* 处理运算符 */
                LinkListValue operationTop = linkList_peek(doubleOperateStack);/* 栈顶的算符 */
                if (*(exp + i + 1) == '-') {/*判断下一个运算符是否为'-'，进而处理负数*/
                    isNegative = 1;
                    /*此处不能对i的位置进行操作，以防止漏读运算符*/
                }

                if (getPriority((char) operationTop) >= getPriority(expTemp)) { /* 比较两个运算符的优先级 */
                    /* 从算子栈中退出两个算子 */
                    double* value2 = (double *) linkList_pop(numStack);
                    double* value1 = (double *) linkList_pop(numStack);
                    /*错误处理，防止输入不合法时程序崩溃*/
                    if (value1 == NULL || value2 == NULL) return NULL;
                    calResult = linkListValue_init();
                    *(double *) calResult = numDoubleCal(*value1, *value2, (char) operationTop);
                    linkList_push(numStack, calResult);    /* 计算结果压入栈中 */
                    linkList_pop(doubleOperateStack); /* 从算符栈中退栈 */
                } else {
                    /* 将算符压入栈中 */
                    linkList_push(doubleOperateStack, (LinkListValue *) expTemp);
                    i++;
                }
            }
    }


    /* 弹出算符栈中的所有算符，并计算 */
    LinkListValue operationTop;
    while((char) (operationTop = linkList_peek(doubleOperateStack)) != '#') {/* 栈顶的算符 */
        /* 从算子栈中退出两个算子 */
        double* value2 = linkList_pop(numStack);
        double* value1 = linkList_pop(numStack);
        /*错误处理，防止输入不合法时程序崩溃*/
        if (value2 == NULL || value1 == NULL) return NULL;
        calResult = linkListValue_init();
        *(double *) calResult = numDoubleCal(*value1, *value2, (char) operationTop);
        linkList_push(numStack, calResult);    /* 计算结果压入栈中 */
        linkList_pop(doubleOperateStack); /* 从算符栈中退栈 */
    }
    numTemp = linkList_pop(numStack);
    /*错误处理，防止输入不合法时程序崩溃*/
    if (numTemp == NULL) return NULL;
    else return (double *) numTemp;
}

//字符串替换，以识别输入的sin、cos等三角函数计算符
char* shortenExpression(char* exp){
    strReplace(exp,"sin", "s");
    strReplace(exp,"cos", "c");
    strReplace(exp,"tan", "t");
    strReplace(exp,"cot", "o");
    return exp;
}

//双目运算符计算
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
            return ((int)val1 % (int)val2); //强制转换类型，防止计算出错
        case '^':
            return pow(val1,val2);
        default:
            return -1;
    }
}

//单目运算符计算
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

//获取运算符优先级，#优先级最低，防止被弹出算符栈，也标记着运算结束
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

//字符串替换函数
char* strReplace(char originalString[], char key[], char swap[]){
    int lengthOfOriginalString, lengthOfKey, lengthOfSwap, i, j , flag;
    char tmp[1000];

    //获取各个字符串的长度
    lengthOfOriginalString = (int)strlen(originalString);
    lengthOfKey =  (int)strlen(key);
    lengthOfSwap =  (int)strlen(swap);

    for(i = 0; i <= lengthOfOriginalString - lengthOfKey; i++){
        flag = 1;
        //搜索key
        for(j  = 0; j < lengthOfKey; j ++){
            if(originalString[i + j] != key[j]){
                flag = 0;
                break;
            }
        }
        //如果搜索成功，则进行替换
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
