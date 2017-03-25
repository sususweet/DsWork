//
// Created by tangyq on 2017/3/7.
//
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "linkList.h"
#include "../test/alloc-testing.h"

/*����Ƿ�ɹ������ڴ�*/
#define Asert(par) if(par==NULL) {\
                printf("%s,%d �����ڴ�ʧ�ܣ�\n",__FILE__,__LINE__);\
                return NULL;}

/*************************************
*@desc: ����һ��������ͷ��������ͷ�������Ϊ��
*@return: ������ͷ����������ʼ��ַ
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
*@desc: ������������
*@param: linkList->������ڵ�ַ
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
*@desc: ��ӡ���������
*@param: linkList->������ڵ�ַ
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
*@desc: �������������ڵ�
*@param: node1->�ڵ�1��ַ
*@param: node2->�ڵ�2��ַ
*@return: �����Ƿ�ɹ�
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
*@desc: �ҵ�����ĳ���ڵ��ǰһ���ڵ�
*@param: linkList->������ڵ�ַ
*@param: index->������Ľڵ��ַ
*@return: ǰһ���ڵ��ַ
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
*@desc: �ҵ�����ĳ���ڵ�ĺ�һ���ڵ�
*@param: index->������Ľڵ��ַ
*@return: ��һ���ڵ��ַ
*************************************
*/
LinkListEntry* linkList_getAfter(LinkListEntry* index){
    return index->next;
}
/*************************************
*@desc: �ҵ�����ĵ�һ���ڵ�
*@note: ��Ϊ�����ݽṹ������������ͷ��㣬�����Ҫ������ڽڵ����һ���ڵ�
*@param: linkList->������ڵ�ַ
*@return: ����ĵ�һ���ڵ��ַ
*************************************
*/
LinkListEntry* linkList_getFirstNode(LinkListEntry* linkList){
    return linkList->next;
}
/*************************************
*@desc:  �ҵ���������һ���ڵ�
*@param: linkList->������ڵ�ַ
*@return: ��������һ���ڵ��ַ
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
*@desc: ����������
*@param: linkList->������ڵ�ַ
*@return: ������
*@note: �����а���ͷ��㣬�˴�������Ҫ�ر�ע�⣬ͬʱ���صĳ��Ȳ���ͷ���
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
*@desc: �ҵ�ĳ������������ڵ��ַ
*@param: linkList->������ڵ�ַ
*@param: index->��������Ϊ��Ȼ��
*@return: ����ڵ��ַ
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
*@desc: �ҵ�ĳ���ض����ݵ�����ڵ��ַ
*@param: linkList->������ڵ�ַ
*@param: linkListValue->�����ҵ�����
*@param: callback->���ݱȽϺ���
*@return: ����ڵ��ַ
*@note: �˴�ֻ�ܲ��ҵ�ƥ��ĵ�һ������
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
*@desc: �������ض��ڵ�����ӽڵ�
*@param: insertIndex->��������ض��ڵ�
*@param: data->�����ӵĽڵ�����ָ��
*@return: ���ӵĽڵ��ַ
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
*@desc: ������ͷ���ӽڵ�
*@param: linkList->������ڵ�ַ
*@param: data->������Ľڵ��ַ
*@return: ���ӵĽڵ��ַ
*************************************
*/
LinkListEntry* linkList_prependNode(LinkListEntry* linkList, LinkListValue* data){
    linkList_addNode(linkList, data);
}
/*************************************
*@desc: ������ĩβ���ӽڵ�
*@param: linkList->������ڵ�ַ
*@param: data->������Ľڵ��ַ
*@return: ���ӵĽڵ��ַ
*************************************
*/
LinkListEntry* linkList_appendNode(LinkListEntry* linkList, LinkListValue* data){
    linkList_addNode(linkList_getLastNode(linkList), data);
}
/*************************************
*@desc: ɾ�������ĳ���ڵ�
*@param: linkList->������ڵ�ַ
*@param: deleteIndex->��ɾ���Ľڵ��ַ
*@return: ɾ��״̬
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
*@desc: ջ����������ջ
*@param: linkList->������ڵ�ַ
*@param: data->������Ľڵ��ַ
*@return: ���ӵĽڵ��ַ
*************************************
*/
LinkListEntry* linkList_push(LinkListEntry* linkList, LinkListValue* data){
    //�˴��������������ͷ���
    if (linkList_prependNode(linkList, data) == NULL){
        printf("stack PUSH operation failed!\n");
        return NULL;
    };
}
/*************************************
*@desc: ջ����������ջ
*@param: linkList->������ڵ�ַ
*@return: ջ������ָ��
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
*@desc: ջ����������ջ��Ԫ��
*@param: linkList->������ڵ�ַ
*@return: ջ������ָ��
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
