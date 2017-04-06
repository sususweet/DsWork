//
// Created by tangyq on 2017/4/6.
//

#ifndef PROJECT1_EXPRESSIONBASE_H
#define PROJECT1_EXPRESSIONBASE_H

#ifdef __cplusplus
extern "C" {
#endif

int getPriority(char op);

double numDoubleCal(double, double, char);    /* 计算两个数的运算和 */

double numSingleCal(double val1, char op);

char* shortenExpression(char* exp);

char* strReplace(char originalString[], char key[], char swap[]);

#ifdef __cplusplus
}
#endif

#endif //PROJECT1_EXPRESSIONBASE_H
