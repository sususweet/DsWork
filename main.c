#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "arrayList.h"
#include "linkList.h"
#include "./functions/polyCalculation.h"
#include "functions/expressionCalculation.h"

int operationArrayList();
int operationLinkList();
int operationStack();

int linkList_compare(LinkListValue value1, LinkListValue value2);

int main(){
    //polyCalculation();
    //operationStack();

    expCalculation();


    system("pause");
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