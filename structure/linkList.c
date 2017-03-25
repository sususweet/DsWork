//
// Created by tangyq on 2017/3/7.
//
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "linkList.h"
#include "../test/alloc-testing.h"

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

    linkList -> key = -1;
    linkList -> next = NULL;
    linkList -> data = NULL;
    return linkList;
}
/*************************************
*@desc: 销毁整个链表
*@param: linkList->链表入口地址
*************************************
*/
void linkList_destroy(LinkListEntry *linkList){
    LinkListEntry *linkListTemp;
    while (linkList != NULL && linkList->next != NULL){
        linkListTemp = linkList -> next;
        linkList -> next = linkListTemp ->next;
        free(linkListTemp);
    }
    if(linkList != NULL) free(linkList);
}

/*************************************
*@desc: 打印链表的数据
*@param: linkList->链表入口地址
*************************************
*/
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
/*************************************
*@desc: 交换链表两个节点
*@param: node1->节点1地址
*@param: node2->节点2地址
*@return: 操作是否成功
*************************************
*/
int linkList_swapNode(LinkListEntry* node1, LinkListEntry* node2){
    if (node1 == NULL || node2 == NULL) return -1;
    LinkListValue temp;
    temp = node1 -> data;
    node1 -> data = node2 -> data;
    node2 -> data = temp;
    return 0;
}
/*************************************
*@desc: 找到链表某个节点的前一个节点
*@param: linkList->链表入口地址
*@param: index->待处理的节点地址
*@return: 前一个节点地址
*************************************
*/
LinkListEntry* linkList_getBefore(LinkListEntry* linkList, LinkListEntry* index){
    LinkListEntry* linkListCache = linkList;
    LinkListEntry* linkListBefore = NULL;
    while (linkListCache != NULL && linkListCache != index){
        linkListBefore = linkListCache;
        linkListCache = linkListCache->next;
    }
    return linkListBefore;
}
/*************************************
*@desc: 找到链表某个节点的后一个节点
*@param: index->待处理的节点地址
*@return: 后一个节点地址
*************************************
*/
LinkListEntry* linkList_getAfter(LinkListEntry* index){
    return index->next;
}
/*************************************
*@desc: 找到链表的第一个节点
*@note: 因为本数据结构建立的链表有头结点，因此需要查找入口节点的下一个节点
*@param: linkList->链表入口地址
*@return: 链表的第一个节点地址
*************************************
*/
LinkListEntry* linkList_getFirstNode(LinkListEntry* linkList){
    return linkList->next;
}
/*************************************
*@desc:  找到链表的最后一个节点
*@param: linkList->链表入口地址
*@return: 链表的最后一个节点地址
*************************************
*/
LinkListEntry* linkList_getLastNode(LinkListEntry* linkList){
    LinkListEntry* linkListCache = linkList;
    while (linkListCache->next != NULL) {
        linkListCache = linkListCache ->next;
    }
    return linkListCache;
}
/*************************************
*@desc: 计算链表长度
*@param: linkList->链表入口地址
*@return: 链表长度
*@note: 链表中包含头结点，此处处理需要特别注意，同时返回的长度不含头结点
*************************************
*/
unsigned int linkList_getLength(LinkListEntry* linkList){
    LinkListEntry* linkListCache = linkList;
    unsigned int count = 0;
    while (linkListCache->next != NULL) {
        count++;
        linkListCache = linkListCache ->next;
    }
    return count;
}
/*************************************
*@desc: 找到某个索引的链表节点地址
*@param: linkList->链表入口地址
*@param: index->索引数，为自然数
*@return: 链表节点地址
*************************************
*/
LinkListEntry* linkList_getIndexEntryByIndex(LinkListEntry* linkList, unsigned int index){
    LinkListEntry* linkListCache;
    //printf("linkList getIndex: %d\n",index);
    unsigned int count = 0;
    for (linkListCache = linkList->next; linkListCache != NULL; linkListCache = linkListCache->next){
        if (index == count) break;
        count++;
    }
    return linkListCache;
}
/*************************************
*@desc: 找到某个特定数据的链表节点地址
*@param: linkList->链表入口地址
*@param: linkListValue->待查找的数据
*@param: callback->数据比较函数
*@return: 链表节点地址
*@note: 此处只能查找到匹配的第一个数据
*************************************
*/
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
/*************************************
*@desc: 给链表特定节点后增加节点
*@param: insertIndex->待处理的特定节点
*@param: data->待增加的节点数据指针
*@return: 增加的节点地址
*************************************
*/
LinkListEntry* linkList_addNode(LinkListEntry* insertIndex, LinkListValue* data){
    if (insertIndex == NULL) return NULL;

    LinkListEntry* newLinkListEntry;
    newLinkListEntry = (LinkListEntry*) malloc(sizeof(LinkListEntry));
    if (newLinkListEntry == NULL) return NULL;
    newLinkListEntry -> data = data;
    newLinkListEntry -> key = 0;
    newLinkListEntry -> next = insertIndex -> next;
    insertIndex ->next = newLinkListEntry;

    return newLinkListEntry;
}
/*************************************
*@desc: 在链表开头增加节点
*@param: linkList->链表入口地址
*@param: data->待处理的节点地址
*@return: 增加的节点地址
*************************************
*/
LinkListEntry* linkList_prependNode(LinkListEntry* linkList, LinkListValue* data){
    linkList_addNode(linkList, data);
}
/*************************************
*@desc: 在链表末尾增加节点
*@param: linkList->链表入口地址
*@param: data->待处理的节点地址
*@return: 增加的节点地址
*************************************
*/
LinkListEntry* linkList_appendNode(LinkListEntry* linkList, LinkListValue* data){
    linkList_addNode(linkList_getLastNode(linkList), data);
}
/*************************************
*@desc: 删除链表的某个节点
*@param: linkList->链表入口地址
*@param: deleteIndex->待删除的节点地址
*@return: 删除状态
*************************************
*/
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
/*************************************
*@desc: 栈操作——入栈
*@param: linkList->链表入口地址
*@param: data->待处理的节点地址
*@return: 增加的节点地址
*************************************
*/
LinkListEntry* linkList_push(LinkListEntry* linkList, LinkListValue* data){
    //此处建立的链表包含头结点
    if (linkList_prependNode(linkList, data) == NULL){
        printf("stack PUSH operation failed!\n");
        return NULL;
    };
}
/*************************************
*@desc: 栈操作——出栈
*@param: linkList->链表入口地址
*@return: 栈顶数据指针
*************************************
*/
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
/*************************************
*@desc: 栈操作——看栈顶元素
*@param: linkList->链表入口地址
*@return: 栈顶数据指针
*************************************
*/
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

LinkListEntry* linkList_sort(LinkListEntry* linkList, int type, LinkListEqualFunc compare){
    LinkListEntry *polyCache1, *polyCache2;
    if(linkList_getLength(linkList) == 0) {
        return NULL;
    } else {
        for (polyCache1 = linkList->next; polyCache1 != NULL; polyCache1 = polyCache1 -> next){
            for (polyCache2 = polyCache1 -> next; polyCache2 != NULL; polyCache2 = polyCache2 -> next){
                if (type == 0){
                    if  (compare(polyCache1->data,polyCache2->data)>0){
                        linkList_swapNode(polyCache1, polyCache2);
                    }
                }else{
                    if  (compare(polyCache1->data,polyCache2->data)<0){
                        linkList_swapNode(polyCache1, polyCache2);
                    }
                }
            }
        }
        return linkList;
    }
}
