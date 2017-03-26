//
// Created by tangyq on 2017/3/23.
//

#ifndef PROJECT1_HASHTABLEOPERATION_H
#define PROJECT1_HASHTABLEOPERATION_H

#include "../structure/hashTable.h"

#ifdef __cplusplus
extern "C" {
#endif

int getPrimeNumber(int number);

unsigned int hashTableHash(int size, LinkListKey key);

int hashTableCalculation();

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //PROJECT1_HASHTABLEOPERATION_H
