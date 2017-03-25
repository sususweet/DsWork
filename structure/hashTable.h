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

#define MAX_SIZE 999

typedef struct _HashTable HashTable;
typedef int HashTableKey;
typedef void* HashTableValue;
typedef LinkListEntry HashTableEntry;

typedef unsigned int (*HashTableHashFunc)(int size, int key);
typedef bool (*HashTableEqualFunc)(int key1, int key2);
typedef int (*HashTableKeyFreeFunc)(int key);
typedef int (*HashTableValueFreeFunc)(void* value);

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
