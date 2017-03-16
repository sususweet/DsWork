//
// Created by tangyq on 2017/3/16.
//

#include <stdlib.h>
#include <stdio.h>
#include "orthogonalList.h"

/*����Ƿ�ɹ������ڴ�*/
#define Asert(par) if(par==NULL) {\
                printf("%s,%d �����ڴ�ʧ�ܣ�\n",__FILE__,__LINE__);\
                return NULL;}

OList* OList_initOList(){
    OList* oList;
    oList = (OList*) malloc(sizeof(OList));
    Asert(oList);
    return oList;
}

OLNode* OList_createOLNode(int row, int col, MatrixValue value){
    OLNode* oLNode;
    oLNode = (OLNode*) malloc(sizeof(OLNode));
    Asert(oLNode);
    oLNode->row = row;
    oLNode->col = col;
    oLNode->down = NULL;
    oLNode->right = NULL;
    oLNode->val = value;
    return oLNode;
}

OList* OList_createOList(int rowCount, int colCount){
    OList* oList = OList_initOList();
    if (oList == NULL) return NULL;

    //ʮ�������������Ϣ������Ϣ������Ԫ������ʼ��
    oList->rowCount = rowCount;
    oList->colCount = colCount;
    oList->nonZeroCount = 0;

    //ʮ�����������ͷ����ʼ����ע������Ҫ������һ���ڴ�ռ䣬��Ϊ��ͷ���
    oList->rowHead = (OLNode*) malloc(sizeof(OLNode) * (rowCount+1));
    for (int i = 0; i <= rowCount;i++){
        oList->rowHead[i].right = NULL;
        oList->rowHead[i].down = NULL;
        oList->rowHead[i].col = 0;
    }

    //ʮ�����������ͷ����ʼ����ע������Ҫ������һ���ڴ�ռ䣬��Ϊ��ͷ���
    oList->colHead = (OLNode*) malloc(sizeof(OLNode) * (colCount+1));
    for (int i = 0;i <= colCount;i++){
        oList->colHead[i].down = NULL;
        oList->colHead[i].right = NULL;
        oList->colHead[i].row = 0;
    }

    return oList;
}

OList* OList_addNode(OList* oList, int row, int col, MatrixValue value){
    OLNode* newNode = NULL;
    OLNode *rowLink, *colLink;

    if ((newNode = OList_createOLNode(row, col, value)) == NULL) {
        printf("�ڴ�����ʧ�ܣ������ԣ�");
        return NULL;
    }

    //��p����������
    rowLink = &(oList->rowHead[row]);
    while(rowLink->right != NULL && rowLink->col < col) {
        rowLink = rowLink->right;
    }
    newNode->right = rowLink->right;
    rowLink->right = newNode;

    //��p����������
    colLink = &(oList->colHead[col]);
    while(colLink->down != NULL && colLink->row < row) {
        colLink = colLink->down;
    }
    newNode->down = colLink->down;
    colLink->down = newNode;

    oList->nonZeroCount++;

    return oList;
}

void OList_showOList(OList* oList){
    if (oList == NULL) {
        printf("��Ч����ռ䣬�޷���ʾ��\n");
        return;
    }
    for (int i = 1; i <= oList->rowCount; i++){
        OLNode* rowLink = oList->rowHead[i].right;

        printf("| ");
        for (int j = 1; j <= oList-> colCount; j++){
            if (rowLink && rowLink->col == j){
                printf("%4d",(int) rowLink->val);
                rowLink = rowLink->right;
            }else printf("%4d",0);
        }
        printf(" | \n");
    }
}

OList* OList_plusOList(OList* oList1, OList* oList2){
    if (oList1->rowCount != oList2->rowCount) {
        printf("������ӽṹ���Ϸ���");
        return NULL;
    }
    if (oList1->colCount != oList2->colCount) {
        printf("������ӽṹ���Ϸ����������");
        return NULL;
    }

    int rowCount = oList1->rowCount;
    int colCount = oList1->colCount;
    OList* oListResult = OList_createOList(rowCount, colCount);

    for (int i = 1; i < rowCount; i++){
        OLNode* rowLink1 = oList1->rowHead[i].right;
        OLNode* rowLink2 = oList2->rowHead[i].right;
        for (int j = 1; j < colCount; j++){
            if (rowLink1 && rowLink2 && rowLink1->col == j && rowLink2->col == j){
                OList_addNode(oListResult, i, j, rowLink1->val+rowLink2->val);
                rowLink1 = rowLink1->right;
                rowLink2 = rowLink2->right;
            }else if (rowLink1 && rowLink1->col == j){
                OList_addNode(oListResult, i, j, rowLink1->val);
                rowLink1 = rowLink1->right;
            }else if (rowLink2 && rowLink2->col == j){
                OList_addNode(oListResult, i, j, rowLink2->val);
                rowLink2 = rowLink2->right;
            }
        }
    }
    return oListResult;
}

OList* OList_multiOList(OList* oList1, OList* oList2){
    if (oList1->colCount != oList2->rowCount) {
        printf("������˽ṹ���Ϸ����������");
        return NULL;
    }

    int rowCount = oList1->rowCount;
    int colCount = oList2->colCount;
    OList* oListResult = OList_createOList(rowCount, colCount);

    for (int i = 1; i < rowCount; i++){
        OLNode* rowLink1 = oList1->rowHead[i].right;

        for (int j = 1; j < colCount; j++){
            OLNode* colLink2 = oList2->colHead[j].down;

            //����λ���
            MatrixValue temp = 0;

            //���к����к���ͬ��Ԫ�ز����
            while(rowLink1 != NULL && colLink2 != NULL) {
                if(rowLink1->col < colLink2->row)
                    rowLink1 = rowLink1->right;
                else if(rowLink1->col > colLink2->row)
                    colLink2 = colLink2->down;
                else {
                    temp += rowLink1->val*colLink2->val;
                    rowLink1 = rowLink1->right;
                    colLink2 = colLink2->down;
                }
            }
            OList_addNode(oListResult, i, j, temp);
        }
    }
    return oListResult;
}

OList* OList_inverseOList(OList* oList){
    int rowCount = oList->rowCount;
    int colCount = oList->colCount;
    OList* oListResult = OList_createOList(colCount, rowCount);

    for (int i = 1; i < rowCount; i++) {
        OLNode *rowLink = oList->rowHead[i].right;
        for (int j = 1; j < colCount; j++) {
            if (rowLink && rowLink->col == j) {
                OList_addNode(oListResult, j, i, rowLink->val);
                rowLink = rowLink->right;
            }
        }
    }

    return oListResult;
}