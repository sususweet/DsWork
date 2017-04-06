//
// Created by tangyq on 2017/4/6.
//

#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "test-treeCalculator.h"

int treeCalculatorTest(){
    char exp1[] = "2*3";
    char exp2[] = "2+3/1.5-10*3+40";
    char exp3[] = "-2+3/1.5-(10*3)+40";
    char exp4[] = "-(3+4*5)+1*2.5";
    char exp5[] = "(3^2+5%3)+1";
    char exp6[] = "sin(1)+2";
    char exp7[] = "5+9*8-exp(1)";
    char exp8[] = "5+x*8-x";
    double rst = 0;

    doExpressionCal(exp1, &rst);
    assert(rst == 6.0);
    doExpressionCal(exp2, &rst);
    assert(rst == 14.0);
    doExpressionCal(exp3, &rst);
    assert(rst == 10.0);
    doExpressionCal(exp4, &rst);
    assert(rst == -20.5);
    doExpressionCal(exp5, &rst);
    assert(rst == 12);
    doExpressionCal(exp6, &rst);
    assert((fabs(rst - 2.841470)<0.0001));
    doExpressionCal(exp7, &rst);
    assert((fabs(rst - 74.281718)<0.0001));

    doExpressionCalWithVariable(exp8, &rst, 1);
    printf("%lf\n",rst);
    /*binaryTree_inOrderNode(binaryTree->rootNode);
    printf("\n");
    binaryTree_postOrderNode(binaryTree->rootNode);*/
    return 0;
}