//
// Created by tangyq on 2017/3/16.
//

#include <stdlib.h>
#include <stdio.h>
#include "orthogonalList.h"

/*检查是否成功申请内存*/
#define Asert(par) if(par==NULL) {\
                printf("%s,%d 请求内存失败！\n",__FILE__,__LINE__);\
                return NULL;}

/*************************************
*@desc: 初始化十字链表
*@return: 十字链表入口地址
*************************************
*/
OList* OList_initOList(){
    OList* oList;
    oList = (OList*) malloc(sizeof(OList));
    Asert(oList);
    return oList;
}

/*************************************
*@desc: 新增十字链表节点
*@param: row->节点行位置
*@param: col->节点列位置
*@param: value->节点值
*@return: 十字链表节点地址
*************************************
*/
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

/*************************************
*@desc: 根据行列数建立十字链表
*@param: rowCount->十字链表矩阵行数
*@param: colCount->十字链表矩阵列数
*@return: 十字链表入口地址
*************************************
*/
OList* OList_createOList(int rowCount, int colCount){
    OList* oList = OList_initOList();
    if (oList == NULL) return NULL;

    //十字链表矩阵行信息、列信息、非零元个数初始化
    oList->rowCount = rowCount;
    oList->colCount = colCount;
    oList->nonZeroCount = 0;

    //十字链表矩阵行头结点初始化，注意这里要多申请一个内存空间，因为有头结点
    oList->rowHead = (OLNode*) malloc(sizeof(OLNode) * (rowCount + 1));
    for (int i = 0; i <= rowCount;i++){
        oList->rowHead[i].right = NULL;
        oList->rowHead[i].down = NULL;
        oList->rowHead[i].col = 0;
    }

    //十字链表矩阵列头结点初始化，注意这里要多申请一个内存空间，因为有头结点
    oList->colHead = (OLNode*) malloc(sizeof(OLNode) * (colCount + 1));
    for (int i = 0;i <= colCount;i++){
        oList->colHead[i].down = NULL;
        oList->colHead[i].right = NULL;
        oList->colHead[i].row = 0;
    }

    return oList;
}

/*************************************
*@desc: 给十字链表增加矩阵节点
*@param: oList -> 十字链表
*@param: row -> 矩阵节点行位置
*@param: col -> 矩阵节点列位置
*@param: value -> 矩阵节点值
*@return: 十字链表入口地址
*************************************
*/
OList* OList_addNode(OList* oList, int row, int col, MatrixValue value){
    OLNode* newNode = NULL;
    OLNode *rowLink, *colLink;

    if ((newNode = OList_createOLNode(row, col, value)) == NULL) {
        printf("内存申请失败，请重试！");
        return NULL;
    }

    //将p插入行链中
    rowLink = &(oList->rowHead[row]);
    while(rowLink->right != NULL && rowLink->col < col) {
        rowLink = rowLink->right;
    }
    if (rowLink->col == col){
        rowLink->val = newNode->val;
    } else{
        newNode->right = rowLink->right;
        rowLink->right = newNode;
    }

    //将p插入列链中
    colLink = &(oList->colHead[col]);
    while(colLink->down != NULL && colLink->row < row) {
        colLink = colLink->down;
    }
    if (colLink->row == row){
        colLink->val = newNode->val;
    } else{
        newNode->down = colLink->down;
        colLink->down = newNode;
    }

    oList->nonZeroCount++;

    return oList;
}

/*************************************
*@desc: 显示十字链表矩阵内容
*@param: oList->十字链表矩阵入口地址
*************************************
*/
void OList_showOList(OList* oList){
    if (oList == NULL) {
        printf("无效矩阵空间，无法显示！\n");
        return;
    }
    for (int i = 1; i <= oList->rowCount; i++){
        OLNode* rowLink = oList->rowHead[i].right;
        printf("| ");
        for (int j = 1; j <= oList-> colCount; j++){
            if (rowLink && rowLink->col == j){
                printf("%4d",(int) rowLink->val);
                rowLink = rowLink->right;
            }else printf("%4d",0); //保证矩阵输出数字对齐
        }
        printf(" | \n");
    }
}

/*************************************
*@desc: 十字链表矩阵加法操作
*@param: oList1 -> 链表矩阵1地址
*@param: oList2 -> 链表矩阵2地址
*@return: 计算结果十字链表矩阵入口地址
*************************************
*/
OList* OList_plusOList(OList* oList1, OList* oList2){
    //矩阵相加前置判断算法
    if (oList1->rowCount != oList2->rowCount) {
        printf("矩阵相加结构不合法！");
        return NULL;
    }
    if (oList1->colCount != oList2->colCount) {
        printf("矩阵相加结构不合法，请检查矩阵！");
        return NULL;
    }

    int rowCount = oList1->rowCount;
    int colCount = oList1->colCount;
    OList* oListResult = OList_createOList(rowCount, colCount);

    for (int i = 1; i <= rowCount; i++){
        OLNode* rowLink1 = oList1->rowHead[i].right;
        OLNode* rowLink2 = oList2->rowHead[i].right;
        for (int j = 1; j <= colCount; j++){
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

/*************************************
*@desc: 十字链表矩阵乘法操作
*@param: oList1 -> 链表矩阵1地址
*@param: oList2 -> 链表矩阵2地址
*@return: 计算结果十字链表矩阵入口地址
*************************************
*/
OList* OList_multiOList(OList* oList1, OList* oList2){

    //矩阵相乘前置判断算法
    if (oList1->colCount != oList2->rowCount) {
        printf("矩阵相乘结构不合法，请检查矩阵！");
        return NULL;
    }

    int rowCount = oList1->rowCount;
    int colCount = oList2->colCount;
    OList* oListResult = OList_createOList(rowCount, colCount);

    //矩阵定位开始
    for (int i = 1; i <= rowCount; i++){
        for (int j = 1; j <= colCount; j++){
            //注意，这里的rowLink1和colLink2的赋值一定要在两层循环体内，防止接下来的while循环改变其地址导致计算错误
            OLNode* rowLink1 = oList1->rowHead[i].right;
            OLNode* colLink2 = oList2->colHead[j].down;
            //矩阵定位完成
            MatrixValue temp = 0;

            //有列号与行号相同的元素才相乘
            while(rowLink1 != NULL && colLink2 != NULL) {
                if(rowLink1->col < colLink2->row)
                    rowLink1 = rowLink1->right;
                else if(rowLink1->col > colLink2->row)
                    colLink2 = colLink2->down;
                else {
                    temp += rowLink1->val * colLink2->val;
                    rowLink1 = rowLink1->right;
                    colLink2 = colLink2->down;
                }
            }
            OList_addNode(oListResult, i, j, temp);
        }
    }
    return oListResult;
}

/*************************************
*@desc: 十字链表矩阵转置操作
*@param: oList -> 链表矩阵地址
*@return: 转置后十字链表矩阵入口地址
*************************************
*/
OList* OList_inverseOList(OList* oList){
    int rowCount = oList->rowCount;
    int colCount = oList->colCount;
    OList* oListResult = OList_createOList(colCount, rowCount);

    for (int i = 1; i <= rowCount; i++) {
        OLNode *rowLink = oList->rowHead[i].right;
        for (int j = 1; j <= colCount; j++) {
            if (rowLink && rowLink->col == j) {
                OList_addNode(oListResult, j, i, rowLink->val);
                rowLink = rowLink->right;
            }
        }
    }

    return oListResult;
}