#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "test/test-arrayList.h"
#include "structure/arrayList.h"
#include "structure/linkList.h"
#include "./functions/polyCalculation.h"
#include "functions/expressionCalculation.h"
#include "functions/matrixCalculation.h"
#include "structure/orthogonalList.h"
#include "functions/hashTableOperation.h"
#include "test/test-linkList.h"
#include "test/test-binaryTree.h"
#include "test/test-treeCalculator.h"

int operationArrayList();
int operationLinkList();
int operationStack();

int linkList_compare(LinkListValue value1, LinkListValue value2);

int main(){
    //arrayListTest();
    //polyCalculation();
    //operationStack();
    //operationArrayList();
    //operationLinkList();
    //linkListTest();
    //expCalculation();
    //hashTableCalculation();
    //binaryTreeTest();
    treeCalculatorTest();
    //matrixCalculation();

    //system("pause");

    return 0;
}

int linkList_compare(LinkListValue value1, LinkListValue value2){
    if (value1 == value2){
        return 0;
    }else if (value1 > value2) return 1;
    else if (value1 < value2) return -1;
}

int operationStack(){
    LinkListEntry* linkList = linkList_initList();
    linkList_pop(linkList);
    linkList_pop(linkList);
    linkList_pop(linkList);

    linkList_push(linkList, 2);
    linkList_push(linkList, 5);
    linkList_push(linkList, 6);
    linkList_push(linkList, 2);
    linkList_show(linkList);

    linkList_pop(linkList);
    linkList_show(linkList);

    printf("The top value of the stack is : %d\n", linkList_peek(linkList));;
    linkList_show(linkList);

    printf("The length of the stack is : %d\n",linkList_getLength(linkList));
    linkList_destroy(linkList);
}


int operationLinkList(){
    LinkListEntry* linkList = linkList_initList();
    linkList_appendNode(linkList, 1);
    linkList_appendNode(linkList, 2);
    linkList_appendNode(linkList, 5);
    linkList_appendNode(linkList, 6);
    linkList_appendNode(linkList, 2);
    linkList_prependNode(linkList, 1231321);
    linkList_show(linkList);
    linkList_deleteNode(linkList,linkList_getIndexEntryByIndex(linkList,0));
    linkList_show(linkList);
    linkList_getIndexEntryByData(linkList, 2 ,linkList_compare);
    printf("�������еĽ��Ϊ: ");
    linkList_sort(linkList,0,linkList_compare);
    linkList_show(linkList);
    printf("�������еĽ��Ϊ: ");
    linkList_sort(linkList,1,linkList_compare);
    linkList_show(linkList);
    printf("The length of the linkList is : %d\n",linkList_getLength(linkList));
    linkList_destroy(linkList);
}

int operationArrayList() {
    ArrayList *arrayList;
    arrayList = arrayList_init();
    int entries[] = { 89, 4, 23, 42, 4, 16, 15, 4, 8, 99, 50, 30, 4 };
    for (int i = 0 ;i<13;i++){
        arrayList_append(arrayList,entries[i]);
    }
    /*
    arrayList_append(arrayList,1);
    arrayList_append(arrayList,5);
    arrayList_append(arrayList,2);
    arrayList_append(arrayList,7);
    arrayList_append(arrayList,3);*/
    arrayList_show(arrayList);
    printf("���鳤��Ϊ��%d \n",arrayList_getLength(arrayList));
    //arrayList_insert(arrayList,2,201);
   // arrayList_show(arrayList);
   // arrayList_remove(arrayList,4);
   // arrayList_show(arrayList);

    printf("�������еĽ��Ϊ��\n");
    arrayList_sort(arrayList, 0);
    arrayList_show(arrayList);

    printf("�������еĽ��Ϊ��\n");
    arrayList_sort(arrayList, 1);
    arrayList_show(arrayList);

    printf("201 ����������Ϊ��%d \n",arrayList_getIndexByValue(arrayList,201));
    printf("��������Ϊ1��ֵΪ��%d \n",(int)arrayList_getValueByIndex(arrayList,1));
    arrayList_destroy(arrayList);

    return 0;
}