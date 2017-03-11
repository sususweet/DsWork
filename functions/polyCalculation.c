//
// Created by tangyq on 2017/3/11.
//

#include <stdio.h>
#include "../linkList.h"
#include "../polynomial.h"
#include "polyCalculation.h"

int polyCalculation(){
    char confirm;
    LinkListEntry *polyList1, *polyList2;
    printf("欢迎使用多项式计算器\n");
    printf("CopyRight @2017 sususweet. All rights reserved.\n");
    printf("\n");

    while(1){
        printf("请输入第一个一元多项式，按照\"系数 指数\"的格式输入，各项之间以空格分开：\n");
        polyList1 = poly_getPoly();
        if (polyList1 == NULL) {
            printf("多项式格式错误，请重试！\n");
            continue;
        }
        printf("你输入的多项式为: \n");
        poly_showPoly(polyList1);
        printf("确认请输入y，否则请输入任意其他字符！\n");
        scanf("%c",&confirm);
        if (confirm == 'y') break;
    }

    while(1){
        printf("请输入第二个一元多项式，按照\"系数 指数\"的格式输入，各项之间以空格分开：\n");
        polyList2 = poly_getPoly();
        if (polyList2 == NULL) {
            printf("多项式格式错误，请重试！\n");
            continue;
        }
        printf("你输入的多项式为: \n");
        poly_showPoly(polyList2);
        printf("确认请输入y，否则请输入任意其他字符！\n");
        scanf("%c",&confirm);
        if (confirm == 'y') break;
    }

    printf("参数确认成功！\n");

    printf("你输入的第一个多项式为:\n");
    polyList1 = poly_sortPoly(polyList1);
    poly_showPoly(polyList1);

    printf("你输入的第二个多项式为:\n");
    polyList2 = poly_sortPoly(polyList2);
    poly_showPoly(polyList2);

    LinkListEntry* polyPlusResult = poly_plusPoly(polyList1,polyList2);
    /*printf("多项式相加的结果是: \n");
    poly_showPoly(polyPlusResult);*/
    printf("多项式相加合并的结果是: \n");
    LinkListEntry* polyMergePlusResult = poly_mergePoly(polyPlusResult);
    poly_showPoly(polyMergePlusResult);

    LinkListEntry* polyMultiResult = poly_multiPoly(polyList1,polyList2);
    /*printf("多项式相乘的结果是: \n");
    poly_showPoly(polyMultiResult);*/

    printf("多项式相乘合并同类项的结果是: \n");
    LinkListEntry* polyMergeResult = poly_mergePoly(polyMultiResult);
    poly_showPoly(polyMergeResult);

    printf("降序排列的结果是: \n");
    LinkListEntry* polySortResult = poly_sortPoly(polyMergeResult);
    poly_showPoly(polySortResult);
}