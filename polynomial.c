//
// Created by tangyq on 2017/3/9.
//

#include <stdlib.h>
#include <stdio.h>
#include "linkList.h"
#include "polynomial.h"

/*检查是否成功申请内存*/
#define Asert(par) if(par==NULL) {\
                printf("%s,%d 请求内存失败！\n",__FILE__,__LINE__);\
                return NULL;}

char poly_judgePositive(int coefficient){
    if (coefficient<0){
        return '-';
    }else return '+';
}

PolyNode* poly_initItem(){
    PolyNode* poly_tmp = (PolyNode*) malloc(sizeof(poly_tmp));
    Asert(poly_tmp);
    return poly_tmp;
}

LinkListEntry* poly_getPoly(){
    int exp_temp,coe_tmp;
    char lf;
    int scanResult;

    LinkListEntry* polyList = linkList_initList();

    while(1){
        scanResult = scanf("%d %d%c",&coe_tmp, &exp_temp, &lf);
        if (scanResult != 3) {
            free (polyList);
            fflush (stdin);
            return NULL;
        }

        PolyNode* poly_tmp = poly_initItem();
        poly_tmp -> coefficient = coe_tmp;
        poly_tmp -> exponent = exp_temp;

        linkList_appendNode(polyList, poly_tmp);
        if (lf == '\n') break;
    }
    return polyList;
}

void poly_showPoly(LinkListEntry* polyList){
    if(linkList_getLength(polyList) == 0) {
        printf("The polyList is empty.\n");
    } else {
        polyList = polyList->next;
        while (polyList != NULL){
            PolyNode* polyNode = polyList->data;
            printf("%dx^%d", polyNode->coefficient, polyNode->exponent);
            polyList = polyList->next;
            if (polyList != NULL) printf(" %c ",poly_judgePositive(polyNode->coefficient));
        }
        printf("\n");
    }
}

LinkListEntry* poly_mergePoly(LinkListEntry* polyList){
    LinkListEntry *polyCache1, *polyCache2, *polyListTemp;
    polyListTemp = polyList;
    if(linkList_getLength(polyListTemp) == 0) {
        printf("The polyList is empty.\n");
    } else {
        for (polyCache1 = polyListTemp->next; polyCache1 != NULL; polyCache1 = polyCache1 -> next){
            PolyNode* polyNode1 = polyCache1->data;
            for (polyCache2 = polyCache1 -> next; polyCache2 != NULL; polyCache2 = polyCache2 -> next){
                PolyNode* polyNode2 = polyCache2->data;
                if  (polyNode1->exponent == polyNode2->exponent){
                    polyNode1->coefficient = polyNode1->coefficient + polyNode2->coefficient;
                    LinkListEntry* temp = linkList_getBefore(polyListTemp, polyCache2);
                    linkList_deleteNode(polyListTemp, polyCache2);
                    polyCache2 = temp;
                }
            }

        }
    }

    return polyListTemp;
}

int poly_compare(int exponent1, int exponent2){
    if (exponent1 == exponent2){
        return 0;
    }else if (exponent1 > exponent2) return 1;
    else if (exponent1 < exponent2) return -1;
}

LinkListEntry* poly_sortPoly(LinkListEntry* polyList){
    LinkListEntry *polyCache1, *polyCache2, *polyListTemp;
    polyListTemp = polyList;
    if(linkList_getLength(polyListTemp) == 0) {
        printf("The polyList is empty.\n");
    } else {
        for (polyCache1 = polyListTemp->next; polyCache1 != NULL; polyCache1 = polyCache1 -> next){
            for (polyCache2 = polyCache1 -> next; polyCache2 != NULL; polyCache2 = polyCache2 -> next){
                PolyNode* polyNode1 = polyCache1->data;
                PolyNode* polyNode2 = polyCache2->data;
                if  (polyNode1->exponent < polyNode2->exponent){
                    linkList_swapNode(polyCache1, polyCache2);
                }
            }

        }
    }

    return polyListTemp;
}


LinkListEntry* poly_plusPoly(LinkListEntry* poly1, LinkListEntry* poly2){
    if(linkList_getLength(poly1) == 0 || linkList_getLength(poly2) == 0) {
        printf("poly_plusPoly:The polyList is empty.\n");
        return NULL;
    }
    LinkListEntry *polyCache1, *polyCache2, *polyResult = linkList_initList();
    polyCache1 = poly1 ->next;
    polyCache2 = poly2 ->next;
    while(polyCache1 != NULL && polyCache2 != NULL){ //两个多项式链表均还有数据
        PolyNode* polyNode1 = polyCache1->data;
        PolyNode* polyNode2 = polyCache2->data;
        PolyNode* newNode = poly_initItem();
        if (polyNode1 -> exponent == polyNode2-> exponent){
            newNode -> exponent = polyNode1-> exponent;
            newNode -> coefficient = polyNode1 -> coefficient + polyNode2 -> coefficient;
            linkList_appendNode(polyResult, newNode);
            polyCache1 = polyCache1 ->next;
            polyCache2 = polyCache2 ->next;
        }else if (polyNode1 -> exponent > polyNode2-> exponent){
            newNode -> exponent = polyNode1-> exponent;
            newNode -> coefficient = polyNode1 -> coefficient;
            linkList_appendNode(polyResult, newNode);
            polyCache1 = polyCache1 ->next;
        }else if (polyNode1 -> exponent < polyNode2-> exponent){
            newNode -> exponent = polyNode2-> exponent;
            newNode -> coefficient = polyNode2 -> coefficient;
            linkList_appendNode(polyResult, newNode);
            polyCache2 = polyCache2 ->next;
        }
    }
    while(polyCache1 != NULL){ //两个多项式链表均还有数据
        PolyNode* newNode = poly_initItem();
        PolyNode* polyNode1 = polyCache1->data;
        newNode -> exponent = polyNode1-> exponent;
        newNode -> coefficient = polyNode1 -> coefficient;
        linkList_appendNode(polyResult, newNode);
        polyCache1 = polyCache1 -> next;
    }
    while(polyCache2 != NULL){ //两个多项式链表均还有数据
        PolyNode* newNode = poly_initItem();
        PolyNode* polyNode2 = polyCache2->data;
        newNode -> exponent = polyNode2-> exponent;
        newNode -> coefficient = polyNode2 -> coefficient;
        linkList_appendNode(polyResult, newNode);
        polyCache2 = polyCache2 -> next;
    }
    return polyResult;
}

LinkListEntry* poly_multiPoly(LinkListEntry* poly1, LinkListEntry* poly2){
    if(linkList_getLength(poly1) == 0 || linkList_getLength(poly2) == 0) {
        printf("poly_multiPoly:The polyList is empty.\n");
        return NULL;
    }
    LinkListEntry *polyCache1, *polyCache2, *polyResult = linkList_initList();
    polyCache1 = poly1 -> next;
    while(polyCache1 != NULL){
        PolyNode* polyNode1 = polyCache1->data;
        polyCache2 = poly2 -> next;
        while(polyCache2 != NULL){
            PolyNode* polyNode2 = polyCache2->data;
            PolyNode* newNode = poly_initItem();
            newNode -> exponent = polyNode1-> exponent + polyNode2-> exponent;
            newNode -> coefficient = polyNode1 -> coefficient * polyNode2 -> coefficient;
            linkList_appendNode(polyResult, newNode);
            polyCache2 = polyCache2 -> next;
        }
        polyCache1 = polyCache1 -> next;
    }
    return polyResult;
}