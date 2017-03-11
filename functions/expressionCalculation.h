//
// Created by tangyq on 2017/3/11.
//

#ifndef PROJECT1_EXPRESSIONCALCULATION_H
#define PROJECT1_EXPRESSIONCALCULATION_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../linkList.h"

int expCalculation();

double* expCal(char*);    /* 计算表达式的值 */

char* shortenExpression(char* exp);

double numDoubleCal(double, double, char);    /* 计算两个数的运算和 */

double numSingleCal(double val1, char op);

int getPriority(char op);

char* strReplace(char strRes[],char from[], char to[]);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //PROJECT1_EXPRESSIONCALCULATION_H
