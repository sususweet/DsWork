//
// Created by tangyq on 2017/3/9.
//

#ifndef PROJECT1_POLYNOMIAL_H
#define PROJECT1_POLYNOMIAL_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _polyNode PolyNode;

typedef struct _polyNode{
    int coefficient;    //系数
    int exponent;   //指数
};

char poly_judgePositive(int coefficient);

PolyNode* poly_initItem();

LinkListEntry* poly_getPoly();

void poly_showPoly(LinkListEntry* polyList);

LinkListEntry* poly_plusPoly(LinkListEntry* poly1, LinkListEntry* poly2);

LinkListEntry* poly_multiPoly(LinkListEntry* poly1, LinkListEntry* poly2);

LinkListEntry* poly_mergePoly(LinkListEntry* polyList);

int poly_compare(int exponent1, int exponent2);

LinkListEntry* poly_sortPoly(LinkListEntry* polyList);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //PROJECT1_POLYNOMIAL_H
