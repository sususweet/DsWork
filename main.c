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
        printf("请输入第一个一元多项式，按照\"系数,指数\"的格式输入，各项之间以空格分开：\n");
        polyList1 = poly_getPoly();
        printf("你输入的多项式为: 确认请输入y，否则请输入任意其他字符！\n");
        poly_showPoly(polyList1);
        scanf("%c",&confirm);
        if (confirm == 'y') break;
    }

    while(1){
        printf("请输入第二个一元多项式，按照\"系数,指数\"的格式输入，各项之间以空格分开：\n");
        polyList2 = poly_getPoly();
        printf("你输入的多项式为: 确认请输入y，否则请输入任意其他字符！\n");
        poly_showPoly(polyList2);
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
    printf("多项式相加的结果是: \n");
    poly_showPoly(polyPlusResult);

    LinkListEntry* polyMultiResult = poly_multiPoly(polyList1,polyList2);
    /*printf("多项式相乘的结果是: \n");
    poly_showPoly(polyMultiResult);*/

    printf("多项式相乘合并同类项的结果是: \n");
    LinkListEntry* polyMergeResult = poly_mergePoly(polyMultiResult);
    poly_showPoly(polyMergeResult);

    printf("降序排列的结果是: \n");
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
    printf("数组长度为：%d \n",arrayList_getLength(arrayList));
    arrayList_insert(arrayList,2,201);
    arrayList_show(arrayList);
    arrayList_remove(arrayList,4);
    arrayList_show(arrayList);
    printf("201 的数组索引为：%d \n",arrayList_getIndexByValue(arrayList,201));
    printf("数组索引为1的值为：%d \n",(int)arrayList_getValueByIndex(arrayList,1));
    arrayList_destroy(arrayList);

    return 0;
}