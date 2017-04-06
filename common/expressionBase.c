//
// Created by tangyq on 2017/4/6.
//

#include <math.h>
#include <string.h>
#include "expressionBase.h"

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
        case 'e':
            return exp(val1);
        default:
            return -1;
    }
}

//字符串替换，以识别输入的sin、cos等三角函数计算符
char* shortenExpression(char* exp){
    strReplace(exp,"exp", "e");
    strReplace(exp,"sin", "s");
    strReplace(exp,"tan", "t");
    strReplace(exp,"cot", "o");
    return exp;
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