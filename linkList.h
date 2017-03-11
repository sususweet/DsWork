//
// Created by tangyq on 2017/3/7.
//

#ifndef PROJECT1_LINKLIST_H
#define PROJECT1_LINKLIST_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _LinkListEntry LinkListEntry;

typedef void* LinkListValue;

typedef int (*LinkListEqualFunc)(LinkListValue value1, LinkListValue value2);

typedef struct _LinkListEntry{
    LinkListValue data;
    LinkListEntry* next;
};

LinkListEntry* linkList_initList();

void linkList_destroy(LinkListEntry *linkList);

void linkList_show(LinkListEntry* linkList);

int linkList_swapNode(LinkListEntry* node1, LinkListEntry* node2);

LinkListEntry* linkList_getBefore(LinkListEntry* linkList, LinkListEntry* index);

LinkListEntry* linkList_getAfter(LinkListEntry* index);

LinkListEntry* linkList_getFirstNode(LinkListEntry* linkList);

LinkListEntry* linkList_getLastNode(LinkListEntry* linkList);

unsigned int linkList_getLength(LinkListEntry* linkList);

LinkListEntry* linkList_getIndexEntryByIndex(LinkListEntry* linkList, unsigned int index);

LinkListEntry* linkList_getIndexEntryByData(LinkListEntry* linkList, LinkListValue* linkListValue, LinkListEqualFunc callback);

LinkListEntry* linkList_addNode(LinkListEntry* insertIndex, LinkListValue* data);

LinkListEntry* linkList_prependNode(LinkListEntry* linkList, LinkListValue* data);

LinkListEntry* linkList_appendNode(LinkListEntry* linkList, LinkListValue* data);

int linkList_deleteNode(LinkListEntry* linkList,LinkListEntry* deleteIndex);


LinkListEntry* linkList_push(LinkListEntry* linkList, LinkListValue* data);

LinkListValue linkList_pop(LinkListEntry* linkList);

LinkListValue linkList_peek(LinkListEntry* linkList);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //PROJECT1_ARRAYLIST_H
