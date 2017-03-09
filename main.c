#include <stdio.h>
#include <stdlib.h>
#include "arrayList.h"
#include "linkList.h"
#include "polynomial.h"

int operationArrayList();
int operationLinkList();
int linkList_compare(LinkListValue value1, LinkListValue value2);

int main(){
    char confirm;
    LinkListEntry *polyList1, *polyList2;

    while(1){
        printf("�������һ��һԪ����ʽ������\"ϵ��,ָ��\"�ĸ�ʽ���룬����֮���Կո�ֿ���\n");
        polyList1 = poly_getPoly();
        printf("������Ķ���ʽΪ: ȷ��������y���������������������ַ���\n");
        poly_showPoly(polyList1);
        scanf("%c",&confirm);
        if (confirm == 'y') break;
    }

    while(1){
        printf("������ڶ���һԪ����ʽ������\"ϵ��,ָ��\"�ĸ�ʽ���룬����֮���Կո�ֿ���\n");
        polyList2 = poly_getPoly();
        printf("������Ķ���ʽΪ: ȷ��������y���������������������ַ���\n");
        poly_showPoly(polyList2);
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
    printf("����ʽ��ӵĽ����: \n");
    poly_showPoly(polyPlusResult);

    LinkListEntry* polyMultiResult = poly_multiPoly(polyList1,polyList2);
    /*printf("����ʽ��˵Ľ����: \n");
    poly_showPoly(polyMultiResult);*/

    printf("����ʽ��˺ϲ�ͬ����Ľ����: \n");
    LinkListEntry* polyMergeResult = poly_mergePoly(polyMultiResult);
    poly_showPoly(polyMergeResult);

    printf("�������еĽ����: \n");
    LinkListEntry* polySortResult = poly_sortPoly(polyMergeResult);
    poly_showPoly(polySortResult);
    system("pause");
    return 0;
}


int linkList_compare(LinkListValue value1, LinkListValue value2){
    if (value1 == value2){
        return 0;
    }else if (value1 > value2) return 1;
    else if (value1 < value2) return -1;
}

int operationLinkList(){
    LinkListEntry* linkList = linkList_initList();
    linkList_appendNode(linkList, 1);
    linkList_appendNode(linkList, 2);
    linkList_appendNode(linkList, 5);
    linkList_appendNode(linkList, 6);
    linkList_appendNode(linkList, 2);
    linkList_show(linkList);
    linkList_deleteNode(linkList_getIndexEntryByIndex(linkList,0),linkList);
    linkList_show(linkList);
    linkList_getIndexEntryByData(linkList, 2 ,linkList_compare);
    printf("The length of the linkList is : %d\n",linkList_getLength(linkList));
    linkList_destroy(linkList);
}

int operationArrayList() {
    ArrayList *arrayList;
    arrayList = arrayList_init();
    arrayList_append(arrayList,1);
    arrayList_append(arrayList,5);
    arrayList_append(arrayList,2);
    arrayList_append(arrayList,7);
    arrayList_append(arrayList,3);
    arrayList_show(arrayList);
    printf("���鳤��Ϊ��%d \n",arrayList_getLength(arrayList));
    arrayList_insert(arrayList,2,201);
    arrayList_show(arrayList);
    arrayList_remove(arrayList,4);
    arrayList_show(arrayList);
    printf("201 ����������Ϊ��%d \n",arrayList_getIndexByValue(arrayList,201));
    printf("��������Ϊ1��ֵΪ��%d \n",(int)arrayList_getValueByIndex(arrayList,1));
    arrayList_destroy(arrayList);

    return 0;
}