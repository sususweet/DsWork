//
// Created by tangyq on 2017/3/7.
//
#include <stdlib.h>
#include <stdio.h>
#include "linkList.h"


/*检查是否成功申请内存*/
#define Asert(par) if(par==NULL) {\
                printf("%s,%d 请求内存失败！\n",__FILE__,__LINE__);\
                return NULL;}

/*************************************
*@desc: 建立一个包含有头结点的链表，头结点数据为空
*@return: 包含有头结点的链表起始地址
*************************************
*/
LinkListEntry* linkList_initList(){
    LinkListEntry* linkList;
    linkList = (LinkListEntry*) malloc(sizeof(LinkListEntry));
    Asert(linkList);

    linkList -> next = NULL;
    linkList -> data = NULL;
    return linkList;
}

void linkList_destroy(LinkListEntry *linkList){
    if(linkList != NULL) {
        free(linkList);
    }
}

void linkList_show(LinkListEntry* linkList){
    if(linkList_getLength(linkList) == 0) {
        printf("The linkList is empty.\n");
    } else {
        linkList = linkList->next;
        printf("Elements in the linkList are: ");
        while (linkList != NULL){
            printf("%d \t", (int) linkList->data);
            linkList = linkList->next;
        }
        printf("\n");
    }
}

int linkList_swapNode(LinkListEntry* node1, LinkListEntry* node2){
    if (node1 == NULL || node2 == NULL) return -1;
    LinkListValue temp;
    temp = node1 -> data;
    node1 -> data = node2 -> data;
    node2 -> data = temp;
    return 0;
}

LinkListEntry* linkList_getBefore(LinkListEntry* linkList, LinkListEntry* index){
    LinkListEntry* linkListCache = linkList;
    LinkListEntry* linkListBefore = NULL;
    while (linkListCache != NULL && linkListCache != index){
        linkListBefore = linkListCache;
        linkListCache = linkListCache->next;
    }
    return linkListBefore;
}

LinkListEntry* linkList_getAfter(LinkListEntry* index){
    return index->next;
}

LinkListEntry* linkList_getFirstNode(LinkListEntry* linkList){
    return linkList->next;
}

LinkListEntry* linkList_getLastNode(LinkListEntry* linkList){
    LinkListEntry* linkListCache = linkList;
    while (linkListCache->next != NULL) {
        linkListCache = linkListCache ->next;
    }
    return linkListCache;
}

unsigned int linkList_getLength(LinkListEntry* linkList){
    LinkListEntry* linkListCache = linkList;
    unsigned int count = 0;
    while (linkListCache->next != NULL) {
        count++;
        linkListCache = linkListCache ->next;
    }
    return count;
}

LinkListEntry* linkList_getIndexEntryByIndex(LinkListEntry* linkList, unsigned int index){
    LinkListEntry* linkListCache;
    printf("linkList getIndex: %d\n",index);
    unsigned int count = 0;
    for (linkListCache = linkList->next; linkListCache != NULL; linkListCache = linkListCache->next){
        if (index == count) break;
        count++;
    }
    return linkListCache;
}

LinkListEntry* linkList_getIndexEntryByData(LinkListEntry* linkList, LinkListValue* linkListValue, LinkListEqualFunc callback){
    LinkListEntry* linkListCache;
    unsigned int index = 0;
    for (linkListCache = linkList->next; linkListCache != NULL; linkListCache = linkListCache->next){
        if (callback(linkListCache->data,linkListValue) == 0){
            printf("linkList_getIndexEntryByData, the index is : %d\n",index);
            return linkListCache;
        }
        index ++;
    }
    printf("linkList_getIndexEntryByData, data not found.\n");
    return NULL;
}

LinkListEntry* linkList_addNode(LinkListEntry* insertIndex, LinkListValue* data){
    if (insertIndex == NULL) return NULL;

    LinkListEntry* newLinkListEntry;
    newLinkListEntry = (LinkListEntry*) malloc(sizeof(LinkListEntry));
    if (newLinkListEntry == NULL) return NULL;
    newLinkListEntry -> data = data;

    newLinkListEntry -> next = insertIndex ->next;
    insertIndex ->next = newLinkListEntry;

    return newLinkListEntry;
}

LinkListEntry* linkList_prependNode(LinkListEntry* linkList, LinkListValue* data){
    linkList_addNode(linkList, data);
}

LinkListEntry* linkList_appendNode(LinkListEntry* linkList, LinkListValue* data){
    linkList_addNode(linkList_getLastNode(linkList), data);
}

int linkList_deleteNode(LinkListEntry* linkList, LinkListEntry* deleteIndex){
    if (deleteIndex == NULL) {
        printf("linkList delete operation failed. Please check the index for deletion!\n");
        return -1;
    }

    LinkListEntry* linkListBefore = linkList_getBefore(linkList, deleteIndex);
    linkListBefore->next = deleteIndex->next;
    free(deleteIndex);
    //printf("linkList delete operation succeed.\n");
    return 0;
}

LinkListEntry* linkList_push(LinkListEntry* linkList, LinkListValue* data){
    if (linkList_prependNode(linkList, data) == NULL){
        printf("stack PUSH operation failed!\n");
        return NULL;
    };
}

LinkListValue linkList_pop(LinkListEntry* linkList){
    LinkListEntry* targetEntry = linkList_getFirstNode(linkList);
    if (targetEntry != NULL){
        LinkListValue targetData = targetEntry -> data;
        if (linkList_deleteNode(linkList,targetEntry) == 0) return targetData;
        else {
            printf("stack POP operation failed. Please check the stack!\n");
            return NULL;
        }
    }
    printf("stack POP operation failed. Please check the stack!\n");
    return NULL;
}

LinkListValue linkList_peek(LinkListEntry* linkList){
    LinkListEntry* targetEntry = linkList_getFirstNode(linkList);
    if (targetEntry != NULL){
        LinkListValue targetData = targetEntry -> data;
        return targetData;
    }else {
        printf("stack PEEK operation failed. Please check the stack!\n");
        return NULL;
    }
}