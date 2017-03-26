//
// Created by tangyq on 2017/3/23.
//

#ifndef PROJECT1_HASHTABLE_H
#define PROJECT1_HASHTABLE_H

#include <stdbool.h>
#include "linkList.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 散列表的最大长度，一般设置较大以减少程序运行过程中再散列的次数
 */
#define MAX_SIZE 999

typedef struct _HashTable HashTable;
typedef int HashTableKey;
typedef void* HashTableValue;

/**
 * 散列冲突链表结构
 * @desc:LinkListEntry->链表入口
 */
typedef LinkListEntry HashTableEntry;

/**
 * 散列插入位置计算函数，用户定义
 * @param: size->散列表大小
 * @param: key->关键字
 * @return: 计算得到的插入位置索引
 */
typedef unsigned int (*HashTableHashFunc)(int size, HashTableKey key);
/**
 * 散列key判相等函数，用户定义
 * @param: key1->关键字1
 * @param: key2->关键字2
 * @return: true: 相等, false: 不相等
 */
typedef bool (*HashTableEqualFunc)(HashTableKey key1, HashTableKey key2);
/**
 * 链表key内存释放函数，用户定义
 * @param: key->关键字
 */
typedef int (*HashTableKeyFreeFunc)(HashTableKey key);
/**
 * 链表value内存释放函数，用户定义
 * @param: value-> value地址
 */
typedef int (*HashTableValueFreeFunc)(void* value);

/**
 * 散列表总体结构
 * @desc:tableList->链表入口
 * @desc:table_size->散列表大小
 * @desc:hash_func->散列地址计算hash函数
 * @desc:equal_func->链表判key相等函数
 * @desc:key_free_func->链表key内存释放函数
 * @desc:value_free_func->链表value内存释放函数
 * @desc:entries->散列表元素数目
 */
struct _HashTable {
    LinkListEntry** tableList;
    unsigned int table_size;
    HashTableHashFunc hash_func;
    HashTableEqualFunc equal_func;
    HashTableKeyFreeFunc key_free_func;
    HashTableValueFreeFunc value_free_func;
    unsigned int entries;
};

HashTableEntry* hashLinkList_addNode(HashTableEntry *insertIndex, HashTableKey key, HashTableValue *data);

HashTable* hash_table_new(unsigned int size,HashTableHashFunc hash_func, HashTableEqualFunc equal_func);

HashTable* hash_table_list_new(HashTable* hashTable);

HashTable* hash_table_insert(HashTable *hashTable, LinkListKey key, HashTableValue value);

int hash_table_remove(HashTable *hashTable, HashTableKey key);

HashTableValue hash_table_lookup(HashTable *hashTable, HashTableKey key);

void hash_table_show(HashTable *hashTable);

void hash_table_clear(HashTable* hashTable);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //PROJECT1_HASHTABLE_H
