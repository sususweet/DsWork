//
// Created by tangyq on 2017/3/27.
//

#ifndef PROJECT1_TREECALCULATOR_H
#define PROJECT1_TREECALCULATOR_H

#include "../structure/binaryTree.h"
#include "stdbool.h"

#ifdef __cplusplus
extern "C" {
#endif

#define POSITION_SIZE 10

int create_expression_tree(BinaryTree *tree, BinaryTreeNode *parent, BinaryTreeNodeSide side, char *exp, int length);

double doExpressionCalWithVariable(char *exp, double* rst, double value);

double doExpressionCal(char *exp, double* rst);

int getPriority(char op);

int calculate(BinaryTreeNode *node, double* rst);

bool isDoubleOperator(char op);

bool isSingleOperator(char op);

char getSingleOperator(char *op);

bool isValidDoubleOperator(char op);

bool isNumber(char c);

int getTreePriority(char op);

#ifdef __cplusplus
}
#endif

#endif //PROJECT1_TREECALCULATOR_H
