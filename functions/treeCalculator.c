//
// Created by tangyq on 2017/3/27.
//

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "treeCalculator.h"
#include "../common/expressionBase.h"

char legalDoubleOperator[] = {'+', '-', '*', '/', '^', '%'};

char legalSingleOperator[] = {'-','s', 'c', 't', 'a', 'e'};

/*
int treeCalculator(){
    /* �洢����ı��ʽ�ַ��� */
/*
char exp[1000];
char expReform[1003] = "0+";
double result = 0;
while (1){
    puts("��������Ҫ����ı��ʽ:");
    fflush (stdin);
    gets(exp);
    /*�����ʽ֮ǰ��0+���Է�ֹ���ʽ��-��ͷ��������ֶ��������*/
/*
    strcat(expReform, exp);
    result = doExpressionCal(expReform);
    /*��������ֹ���벻�Ϸ�ʱ�������*/
/*
    if (result == 0){
        printf("�������������ʽ����������!�����в��ܰ�����һ���ʽ\n");
    } else{
        break;
    }
}

return 0;
}*/

double doExpressionCalWithVariable(char *exp, double* rst, double value){
    if (!strchr(exp,'x')){
        printf("Wrong expression��unknown variable!\n");
        return -1;
    }
    char* valueStr = (char *)malloc(8 * sizeof(char));
    sprintf(valueStr,"%.8lf",value);
    while (strchr(exp,'x')){
        strReplace(exp,"x",valueStr);
    }
    doExpressionCal(exp, rst);
    return 0;
}

double doExpressionCal(char *exp, double* rst){
    shortenExpression(exp);
    BinaryTree* binaryTree = binaryTree_init();
    create_expression_tree(binaryTree, binaryTree->rootNode, BITREE_NODE_LEFT, exp, (int) strlen(exp));
    calculate(binaryTree->rootNode,rst);
    return 0;
    /* printf("%s = ", exp_temp);
    printf("%.3f\n", *result);*/
}


int create_expression_tree(BinaryTree *tree, BinaryTreeNode *parent, BinaryTreeNodeSide side, char *exp, int length) {
     // leftBracketNum"("��δ�ɶԸ�����
     // primaryPosition/secondaryPosition��¼���ʽ��("*"��"/")/("+"��"-")��λ��;
     // pn��¼��������"."�ĸ���,���ж�����������Ƿ�Ϸ�
    int i = 0, leftBracketNum = 0, primaryPosition = -1, secondaryPosition = -1, pn = 0;
    int positionList[POSITION_SIZE];
    for (int j = 0; j < POSITION_SIZE; j++){
        positionList[j] = -1;
    }

    /*�жϱ��ʽ�Ƿ���ȷ*/
    /*���ʽ����Ϊ0,���ش���*/
    if(length == 0){
        printf("Wrong expression��length of expression is error!\n");
        return -1;
    }

    /*���ʽ�������ֻ��������ſ�ʼ*/
    if(!(*exp =='(' || isNumber(*exp) || isSingleOperator(*exp))) {
        printf("Wrong expression��not start with number or left bracket!\n");
        return -1;
    }else if(*exp=='(') leftBracketNum++;

    /*���ʽ�������ֻ��������Ž���*/
    if(!(*(exp+length-1)==')' || isNumber(*(exp+length-1)))) {
        printf("Wrong expression��not end with number or right bracket!\n");
        return -1;
    }

    /*�������ʽ*/
    for(i = 1; i < length; i++) {
        if(*(exp+i)=='.') {
            /*С�������߲������֣����ش���*/
            if(!isNumber(*(exp+i-1)) || !isNumber(*(exp+i+1))) {
                printf("Wrong expression: no number around dot(.)!\n");
                return -1;
            }
        } else if(isDoubleOperator(*(exp+i)) && *(exp+i) != '-') {
            /*�ж�˫Ŀ���������Ƿ�Ϊ���ֻ��������ţ��������򷵻ش���*/
            if(!(isValidDoubleOperator(*(exp+i-1)))) {
                printf("Wrong expression: not number or right bracket on the left of (operator)!\n");
                return -1;
            }
            if(leftBracketNum == 0) {
                positionList[getTreePriority(*(exp+i))] = i;
                //primaryPosition = i;
            }//todo:˵������
        }else if(isSingleOperator(*(exp+i)) && *(exp+i) != '-') {
            if(isDoubleOperator(*(exp+i-1)) && *(exp+i+1) != '(') {
                printf("Wrong expression: not operator on the left or not left bracket on the right of (single operator)!\n");
                return -1;
            }
        } else if(*(exp+i) == '-') {
            if(!(isValidDoubleOperator(*(exp+i-1)) || *(exp+i-1)=='(')) {
                printf("Wrong expression: unexpected char appears on the left of (-)!\n");
                return -1;
                /* ���Ӷ� *(exp+i-1)=='(' ���жϣ���ʶ������������Ϊ���������*/
            }
            if(leftBracketNum == 0) {
                positionList[getTreePriority(*(exp+i))] = i;
               // secondaryPosition = i;
            }//todo:˵������
        } else if(*(exp+i) == '(') {
            if(isSingleOperator(*(exp+i-1)) || isDoubleOperator(*(exp+i-1)) || *(exp+i-1)=='(') leftBracketNum++;
            else {
                printf("Wrong expression: unexpected char appears on the left of left bracket!\n");
                return -1;
            }
        } else if(*(exp+i)==')') {
            if(isNumber(*(exp+i-1)) || *(exp+i-1)==')') leftBracketNum--;
            else {
                printf("Wrong expression: unexpected char appears on the left of right bracket!\n");
                return -1;
            }
            if(leftBracketNum < 0) {
                printf("Wrong expression: left bracket and right bracket not equal!\n");
                return -1;
            }
        }
    }
    /*"("��")"δ����ȫ���,���ʽ���벻�Ϸ�*/
    if(leftBracketNum != 0) {
        printf("Wrong expression�� left bracket and right bracket not equal!\n");
        return -1;
    }
    /*�жϱ��ʽ�Ƿ���ȷ����*/

    for (int j = 0; j < POSITION_SIZE ;j++){
        if (positionList[j] != -1) {
            secondaryPosition = positionList[j];
            break;
        }
    }
    for (int j = 0; j < POSITION_SIZE ;j++){
        if (positionList[j] != -1 && positionList[j] != secondaryPosition) {
            primaryPosition = positionList[j];
            break;
        }
    }

    if(secondaryPosition > -1) {
        char * value = (char *)malloc(2 * sizeof(char));
        strncpy(value, exp + secondaryPosition, 1);
        *(value + 1) = '\0';
        BinaryTreeNode *newNode = binaryTree_insert(tree, value, parent, side);
        if(!create_expression_tree(tree, newNode, BITREE_NODE_LEFT,
                                  exp, secondaryPosition)){
            if(!create_expression_tree(tree, newNode, BITREE_NODE_RIGHT,
                                      exp + secondaryPosition + 1, length - secondaryPosition - 1)) {
                return 0;
            }
        }
        return -1;
    }
    
    //��ʱ�������ʽ������һ�����֣����Ǳ��ʽ���屻һ������������
    if(primaryPosition < 0) {
        /*��ʱ���ʽ���屻һ������������*/
        if(*exp=='(') {
            /*ȥ�������������ţ���ȡ�����е�����*/
            if(!create_expression_tree(tree, parent, side, exp+1, length-2)) return 0;
            else return -1;
        } else {//todo:Check
            if(*(exp+1)!='(' || (isSingleOperator(*exp) && *exp != '-')) {//��ʱ���ʽһ����һ������
                for(i = 0; i < length; i++) {
                    if(*(exp+i)=='.')
                        pn++;
                    if(pn > 1) {
                        printf("Wrong expression: more than one dot(.) found in a number!\n");
                        return -1;
                    }
                }
                /*��Ŀ���������s(12)��ȥ�����ź������־*/
                char * value = (char *)malloc((length + 1) * sizeof(char));
                strncpy(value, exp, (size_t) length);
                *(value+length) = '\0';
                char operator = getSingleOperator(value);
                if (operator){
                    strReplace(value,"(", "");
                    strReplace(value,")", "");
                    if (*exp == '-'){
                        gcvt(-numSingleCal(atof(value + 2), operator), 8, value);
                    } else{
                        gcvt(numSingleCal(atof(value + 1), operator), 8, value);
                    }
                }
                binaryTree_insert(tree, value, parent, side);
                return 0;
            } else {//��ʱ���ʽ��һ���ǲ�����"-"�����ಿ�ֱ�һ������������
                char * value = (char *)malloc(2 * sizeof(char));
                strncpy(value, exp, 1);
                *(value + 1) = '\0';
                BinaryTreeNode * newNode = binaryTree_insert(tree, value, parent, side);
                if(!create_expression_tree(tree, newNode, BITREE_NODE_RIGHT, exp + 2, length - 3))
                    return 0;
                else
                    return -1;
            }
        }
    } else {//��ʱ�������ʽΪ����������˻��������ɵ�
        char * value = (char *)malloc(2 * sizeof(char));
        strncpy(value, exp + primaryPosition, 1);
        *(value + 1) = '\0';
        BinaryTreeNode * newNode = binaryTree_insert(tree, value, parent, side);
        if(!create_expression_tree(tree, newNode, BITREE_NODE_LEFT,
                                  exp, primaryPosition)){
            if(!create_expression_tree(tree, newNode, BITREE_NODE_RIGHT,
                                      exp + primaryPosition + 1, length - primaryPosition - 1)){
                return 0;
            }
        }
        return -1;
    }
}

int calculate(BinaryTreeNode * node, double* rst) {
    double l = 0, r = 0;//l��r�ֱ�������������������ֱ��ʽ��ֵ
    if(!node) {
        *rst = 0;
        return 0;
    }
    if(node->children[BITREE_NODE_LEFT] == NULL && node->children[BITREE_NODE_RIGHT] == NULL) {
        *rst = atof(node->value);
        return 0;
    } else {
        //�ȼ�����������������
        if(!calculate(node->children[BITREE_NODE_LEFT], &l))
            if(!calculate(node->children[BITREE_NODE_RIGHT], &r)) {
                *rst = numDoubleCal(l, r, ((char *)node->value)[0]);
                return 0;
            }
        return -1;
    }
}

bool isDoubleOperator(char op){
    int length = sizeof(legalDoubleOperator) / sizeof(legalDoubleOperator[0]);
    for (int i = 0; i < length; i++){
        if (op == legalDoubleOperator[i]) return true;
    }
    return false;
}

bool isSingleOperator(char op){
    int length = sizeof(legalSingleOperator) / sizeof(legalSingleOperator[0]);
    for (int i = 0; i < length; i++){
        if (op == legalSingleOperator[i]) return true;
    }
    return false;
}

char getSingleOperator(char *op){
    int length = sizeof(legalSingleOperator) / sizeof(legalSingleOperator[0]);
    for (int i = 1; i < length; i++){
        if (strchr(op,legalSingleOperator[i])){
            return legalSingleOperator[i];
        }
    }
    return NULL;
}

bool isValidDoubleOperator(char op){
    return isNumber(op) || op==')';
}

bool isNumber(char c){
    if (c>='0'&& c<='9') return true;
    else return false;
}

int getTreePriority(char op) {
    switch(op) {
        case '^':
            return 4;
        case '+':
        case '-':
            return 2;
        case '*':
        case '/':
        case '%':
            return 3;
        default:
            return 0;
    }
}