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
    printf("��ӭʹ�ö���ʽ������\n");
    printf("CopyRight @2017 sususweet. All rights reserved.\n");
    printf("\n");

    while(1){
        printf("�������һ��һԪ����ʽ������\"ϵ�� ָ��\"�ĸ�ʽ���룬����֮���Կո�ֿ���\n");
        polyList1 = poly_getPoly();
        if (polyList1 == NULL) {
            printf("����ʽ��ʽ���������ԣ�\n");
            continue;
        }
        printf("������Ķ���ʽΪ: \n");
        poly_showPoly(polyList1);
        printf("ȷ��������y���������������������ַ���\n");
        scanf("%c",&confirm);
        if (confirm == 'y') break;
    }

    while(1){
        printf("������ڶ���һԪ����ʽ������\"ϵ�� ָ��\"�ĸ�ʽ���룬����֮���Կո�ֿ���\n");
        polyList2 = poly_getPoly();
        if (polyList2 == NULL) {
            printf("����ʽ��ʽ���������ԣ�\n");
            continue;
        }
        printf("������Ķ���ʽΪ: \n");
        poly_showPoly(polyList2);
        printf("ȷ��������y���������������������ַ���\n");
        scanf("%c",&confirm);
        if (confirm == 'y') break;
    }

    printf("����ȷ�ϳɹ���\n");

    printf("������ĵ�һ������ʽΪ:\n");
    polyList1 = poly_sortPoly(polyList1);
    poly_showPoly(polyList1);

    printf("������ĵڶ�������ʽΪ:\n");
    polyList2 = poly_sortPoly(polyList2);
    poly_showPoly(polyList2);

    LinkListEntry* polyPlusResult = poly_plusPoly(polyList1,polyList2);
    /*printf("����ʽ��ӵĽ����: \n");
    poly_showPoly(polyPlusResult);*/
    printf("����ʽ��Ӻϲ��Ľ����: \n");
    LinkListEntry* polyMergePlusResult = poly_mergePoly(polyPlusResult);
    poly_showPoly(polyMergePlusResult);

    LinkListEntry* polyMultiResult = poly_multiPoly(polyList1,polyList2);
    /*printf("����ʽ��˵Ľ����: \n");
    poly_showPoly(polyMultiResult);*/

    printf("����ʽ��˺ϲ�ͬ����Ľ����: \n");
    LinkListEntry* polyMergeResult = poly_mergePoly(polyMultiResult);
    poly_showPoly(polyMergeResult);

    printf("�������еĽ����: \n");
    LinkListEntry* polySortResult = poly_sortPoly(polyMergeResult);
    poly_showPoly(polySortResult);
}