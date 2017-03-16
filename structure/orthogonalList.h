//
// Created by tangyq on 2017/3/16.
//

#ifndef PROJECT1_ORTHOGONALLIST_H
#define PROJECT1_ORTHOGONALLIST_H

typedef double MatrixValue;

typedef struct _OLNode OLNode;

typedef struct _OList OList;

typedef struct _OLNode {
    int row, col;   /* 该非零元的行和列下标 */
    MatrixValue val;    /* 该非零元的值 */
    OLNode *down, *right;    /* 该非零元所在行表和列表的后继链域 */
};

typedef struct _OList{
    OLNode *rowHead, *colHead;  /* 行表头和列表头的指针 */
    int rowCount, colCount, nonZeroCount; /* 矩阵的行数、列数及非零元个数 */
} ;    /* 十字链表矩阵结构 */

OList* OList_createOList(int rowCount, int colCount);

OList* OList_addNode(OList* oList, int row, int col, MatrixValue value);

void OList_showOList(OList* oList);

OList* OList_plusOList(OList* oList1, OList* oList2);

OList* OList_multiOList(OList* oList1, OList* oList2);

OList* OList_inverseOList(OList* oList);

#endif //PROJECT1_ORTHOGONALLIST_H
