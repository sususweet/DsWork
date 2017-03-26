//
// Created by tangyq on 2017/3/23.
//

#include <stdbool.h>
#include <stdio.h>
#include <profileapi.h>
#include <assert.h>
#include "hashTableOperation.h"
#include "../test/alloc-testing.h"

/*����Ƿ�ɹ������ڴ�*/
#define Asert(par) if(par==NULL) {\
                printf("%s,%d �����ڴ�ʧ�ܣ�\n",__FILE__,__LINE__);\
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
    hashTable = hash_table_insert(hashTable, 1, 13);
    hashTable = hash_table_insert(hashTable, 12, 283);
    hashTable = hash_table_insert(hashTable, 111, 723);
    hashTable = hash_table_insert(hashTable, 311, 523);
    hashTable = hash_table_insert(hashTable, 141, 213);
    hash_table_remove(hashTable, 143);
    for (int i =0 ;i<1200;i++){
        hashTable = hash_table_insert(hashTable, i, rand());
    }

    /*ɢ�б�������ܲ��Կ�ʼ*/
    LARGE_INTEGER nFreq;
    LARGE_INTEGER nBeginTime;
    LARGE_INTEGER nEndTime;
    double time;
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime);

    HashTableValue value = hash_table_lookup(hashTable, 1223);
    if (value == NULL){
        printf("�Ҳ���key��Ӧ��value\n");
    }else{
        printf("value:%d\n",(int) value);
    }
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;
    printf("�������ܲ��Ժ�ʱ��%f\n",time);
    /*ɢ�б�������ܲ��Խ���*/

    hash_table_show(hashTable);
    printf("tableSize:%d\n",hashTable->table_size);
    hash_table_clear(hashTable);

    /*ɢ�б���ز����ڴ�й©���*/
    assert(alloc_test_get_allocated() == 0);
    return 0;
}