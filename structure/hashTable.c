//
// Created by tangyq on 2017/3/23.
//

#include <stdlib.h>
#include <stdio.h>
#include "hashTable.h"

/*检查是否成功申请内存*/
#define Asert(par) if(par==NULL) {\
                printf("%s,%d 请求内存失败！\n",__FILE__,__LINE__);\
                return NULL;}

LinkListEntry* hashLinkList_addNode(LinkListEntry *insertIndex, HashTableKey key, HashTableValue *data){
    if (insertIndex == NULL) return NULL;
    LinkListEntry* newLinkListEntry;
    newLinkListEntry = (LinkListEntry*) malloc(sizeof(LinkListEntry));
    if (newLinkListEntry == NULL) return NULL;
    newLinkListEntry -> data = data;
    newLinkListEntry -> key = key;
    newLinkListEntry -> next = insertIndex -> next;
    insertIndex ->next = newLinkListEntry;
    return newLinkListEntry;
}

HashTable* hash_table_new(unsigned int size,HashTableHashFunc hash_func, HashTableEqualFunc equal_func){
    HashTable* hashTable;

    /* 分配一个内存空间 */
    hashTable = (HashTable *) malloc(sizeof(HashTable));
    Asert(hashTable);
    hashTable->hash_func = hash_func;
    hashTable->equal_func = equal_func;
    hashTable->key_free_func = NULL;
    hashTable->value_free_func = NULL;
    hashTable->entries = 0;
    hashTable->table_size = size;

    /* 给每个结点分配内存空间，结点数量为table_size */
    if (!hash_table_list_new(hashTable)) {
        free(hashTable);
        return NULL;
    }
    return hashTable;
}

HashTable* hash_table_list_new(HashTable* hashTable){
    hashTable->tableList = (HashTableEntry**) malloc(hashTable->table_size * sizeof(HashTableEntry**));
    Asert(hashTable->tableList);

    for (int i = 0; i < hashTable -> table_size; i++){
        HashTableEntry* linkListCache = linkList_initList();
        if (linkListCache == NULL) {
            return NULL;
        }else {
            hashTable->tableList[i] = linkListCache;
        }
    }
    return hashTable;
}

//TODO:Test this Part NO enlarge.
HashTable* hash_table_enlarge(HashTable* hashTable){
    HashTable* newTable;
    newTable = hash_table_new((hashTable->table_size) * 3, hashTable->hash_func, hashTable->equal_func);
    if (newTable == NULL) return NULL;
    HashTableEntry *rover;
    for (int index = 0; index < hashTable -> table_size; index++){
        rover = hashTable -> tableList[index] -> next;
        while (rover != NULL && rover-> key != NULL && rover-> key >=0 ) {
            if (!hash_table_insert(newTable, rover->key, rover->data)){
                printf("Enlarge error!");
                return NULL;
            }
            rover = rover->next;
        }
    }

    return newTable;
}

HashTable* hash_table_insert(HashTable* hashTable, HashTableKey key, HashTableValue value){
    HashTableEntry *rover;
    unsigned int index;

    /* 如果表中的结点过多，冲突的可能性增大，散列表的查找效率下降，此时扩大表的大小 */
    /* 当已使用的结点数量超过散列表大小的1/3 */
    if ((hashTable->entries * 3) / hashTable->table_size > 0){
        if (!hash_table_enlarge(hashTable)) return hashTable;
        else hashTable = hash_table_enlarge(hashTable);
    }

    /* 根据关键词找到对应链表头结点的下标 */
    index = hashTable->hash_func(hashTable->table_size, key);

    /* 遍历整个链表来查找是否有相同关键词的结点，有则覆写，否则添加 */
    rover = hashTable->tableList[index]->next;
    while (rover != NULL) {
        if (hashTable->equal_func(rover->key, key)) {
            /* 若找到相同关键词，用新数据覆写结点 */
            /* 如果有释放数值和关键词内存的函数，那么释放旧内存，没有则跳过 */
            if (hashTable->value_free_func != NULL)
                hashTable->value_free_func(rover->data);
            if (hashTable->key_free_func != NULL)
                hashTable->key_free_func(rover->key);
            rover->key = key;
            rover->data = value;

            /* 覆写完成 */
            return hashTable;
        }
        rover = rover->next;
    }

    /* 没有关键词为key的结点，那么在新建一个并加入链表头部 */
    hashLinkList_addNode(hashTable->tableList[index], key, value);

    /* 链表中结点的数量增加1 */
    hashTable->entries++;

    /* 添加完成 */
    return hashTable;
}

int hash_table_remove(HashTable *hashTable, HashTableKey key){
    HashTableEntry *rover;
    unsigned int index;
    int result;

    /* 根据关键词找到对应链表头结点的下标 */
    index = hashTable->hash_func(hashTable->table_size, key);
    result = -1;

    /* 遍历下标为index的链表直到找到关键词为key的结点 */
    rover = hashTable->tableList[index]->next;
    while (rover != NULL) {
        if (hashTable->equal_func(key, rover->key)){
            linkList_deleteNode(hashTable->tableList[index],rover);
            hashTable->entries--;
            result = 0;
            break;
        }
        rover = rover->next;
    }

    return result;
}

HashTableValue hash_table_lookup(HashTable *hashTable, HashTableKey key){
    HashTableEntry *rover;
    unsigned int index;

    /* 根据关键词找到对应链表头结点的下标 */
    index = hashTable->hash_func(hashTable->table_size, key);

    /* 遍历下标为index的链表直到找到关键词为key的结点 */
    rover = hashTable->tableList[index]->next;
    while (rover != NULL) {
        if (hashTable->equal_func(key, rover->key))
            return rover->data;
        rover = rover->next;
    }

    /* 未找到结点 */
    return NULL;
}

void hash_table_show(HashTable *hashTable){
    HashTableEntry *rover;
    printf("key\t||\tvalue\n");
    for (int index = 0; index < hashTable -> table_size; index++){
        rover = hashTable -> tableList[index] -> next;
        while (rover != NULL && rover->key != NULL && rover->key >=0 ) {
            printf("index:%d  %d\t||\t%d\n",index,rover->key,(int) rover->data);
            rover = rover->next;
        }
    }
}

//清空hash表
void hash_table_clear(HashTable* hashTable) {
    HashTableEntry *linkListNode;
    for(int i = 0; i < hashTable -> table_size; i++) {
        linkListNode = hashTable -> tableList[i];
        linkList_destroy (linkListNode);
    }
    free(hashTable);
}