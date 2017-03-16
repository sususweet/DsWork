//
// Created by tangyq on 2017/3/2.
//
#include <stdlib.h>
#include <stdio.h>
#include "arrayList.h"
#include "string.h"

/*检查是否成功申请内存*/
#define Asert(par) if(par==NULL) {\
                printf("%s,%d 请求内存失败！\n",__FILE__,__LINE__);\
                return NULL;}

ArrayList * arrayList_init(){
    //申请结构体的内存
    ArrayList *arrayList = (ArrayList *)malloc(sizeof(ArrayList));
    Asert(arrayList);
    //申请数组的内存
    ArrayListValueEntry *data = (ArrayListValueEntry *)malloc(MAX_SIZE * sizeof(ArrayListValueEntry));
    Asert(data);
    arrayList->data = data;
    arrayList->length = 0;
    arrayList->_alloced = MAX_SIZE;
    return arrayList;
}

void arrayList_destroy(ArrayList *arrayList){
    if(arrayList!=NULL) {
        free(arrayList->data); //释放数组占用的内存
        free(arrayList);       //释放结构体占用的内存
    }
}

void arrayList_show(ArrayList *arrayList){
    if(arrayList_getLength(arrayList) == 0) {
        printf("该数组是空的\n");
    } else {
        for(int i = 0;i < arrayList->length;i++)
            printf("%d \t", (int) arrayList->data[i]);
        printf("\n");
    }
}

int arrayList_enlarge(ArrayList *arrayList){
    ArrayListValueEntry *newEntry;
    unsigned int newSize;
    /* 将已分配的数组内存空间扩展为原来的2倍 */
    newSize = arrayList->_alloced * 2;
    /* 给数组重新分配新的内存空间 */
    newEntry = realloc(arrayList->data, sizeof(ArrayListValueEntry) * newSize);
    if (newEntry == NULL) return -1;
    else {
        arrayList->data = newEntry;
        arrayList->_alloced = newSize;
        return 0;
    }
}

int arrayList_insert(ArrayList *arrayList, unsigned int index, ArrayListValueEntry data){
    /*检查下标是否越界*/
    if (index > arrayList->length) return -1;
    if (arrayList->length + 1 > arrayList->_alloced) {
        if (arrayList_enlarge(arrayList)) return -1;
    }
    /* 把待插入位置及之后的数组内容后移一位
     * memmove(void *_Dst,const void *_Src,size_t _Size);
     * Dst: 目标地址
     * Src: 初始地址
     * _Size: 地址数
     * */
    if (memmove(&arrayList->data[index + 1], &arrayList->data[index],
            (arrayList->length - index) * sizeof(ArrayListValueEntry)) != NULL){
        /*在下标为index的位置插入数据 */
        arrayList->data[index] = data;
        arrayList->length++;
        return 0;
    }else return -1;

}

int arrayList_prepend(ArrayList *arrayList, ArrayListValueEntry data){
    return arrayList_insert(arrayList, 0, data);
}

int arrayList_append(ArrayList *arrayList, ArrayListValueEntry data){
    return arrayList_insert(arrayList, arrayList->length, data);
}

int arrayList_removeRange(ArrayList *arrayList, unsigned int index, unsigned int removeLength){
    if (index > arrayList->length || index + removeLength > arrayList->length || removeLength == 0) return -1;
    if (memmove(&arrayList->data[index], &arrayList->data[index + removeLength],
                (arrayList->length - index - removeLength) * sizeof(ArrayListValueEntry)) != NULL){
        arrayList->length -= removeLength;
        return 0;
    }
    else return -1;
}

int arrayList_remove(ArrayList *arrayList, unsigned int index){
    return arrayList_removeRange(arrayList, index, 1);
}

int arrayList_getLength(ArrayList *arrayList){
    return arrayList->length;
}

ArrayListValueEntry arrayList_getValueByIndex(ArrayList *arrayList, unsigned int index){
    return arrayList->data[index];
}

int arrayList_getIndexByValue(ArrayList *arrayList, ArrayListValueEntry data){
    for (int i = 0; i < arrayList->length; i++){
        if (arrayList->data[i] == data) return i;
    }
    return -1;
}