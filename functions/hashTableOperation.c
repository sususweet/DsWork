//
// Created by tangyq on 2017/3/23.
//

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "hashTableOperation.h"

/*检查是否成功申请内存*/
#define Asert(par) if(par==NULL) {\
                printf("%s,%d 请求内存失败！\n",__FILE__,__LINE__);\
                return NULL;}

int getPrimeNumber(int number){
    for (int i = number; i >= 1; i--) {
        for (int j = 2; j <= i; j++){
            if (j == i) return i;
            if(i % j == 0) break;
        }
    }
    return -1;
}

unsigned int hashTableHash(int size, LinkListKey key){
    int prime;
    prime = getPrimeNumber(size);
    if (prime == -1) return 0;
    unsigned int position = (unsigned int) key % prime % size;
    return position;
}

bool hashTableEqual(LinkListKey key1,LinkListKey key2){
    return key1 == key2;
}

int hashTableCalculation(){
    HashTable* hashTable;
    hashTable = hash_table_new(MAX_SIZE, hashTableHash, hashTableEqual);
    Asert(hashTable);
    hash_table_insert(hashTable, 1, 13);
    hash_table_insert(hashTable, 12, 283);
    hash_table_insert(hashTable, 111, 723);
    hash_table_insert(hashTable, 311, 523);
    hash_table_insert(hashTable, 141, 213);

    HashTableValue value = hash_table_lookup(hashTable, 143);
    if (value == NULL){
        printf("找不到key对应的value\n");
    }else{
        printf("value:%d\n",(int) value);
    }
    hash_table_show(hashTable);
    printf("data:%d\n",hashTable->table_size);
    hash_table_clear(hashTable);
}