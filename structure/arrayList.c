//
// Created by tangyq on 2017/3/2.
//
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "arrayList.h"
#include "string.h"
#include "../test/alloc-testing.h"

/*����Ƿ�ɹ������ڴ�*/
#define Asert(par) if(par==NULL) {\
                printf("%s,%d �����ڴ�ʧ�ܣ�\n",__FILE__,__LINE__);\
                return NULL;}

ArrayList * arrayList_init(){
    //����ṹ����ڴ�
    ArrayList *arrayList = (ArrayList *)malloc(sizeof(ArrayList));
    Asert(arrayList);
    //����������ڴ�
    ArrayListValueEntry *data = (ArrayListValueEntry *)malloc(MAX_SIZE * sizeof(ArrayListValueEntry));
    if (!data) {
        free(arrayList);
        return NULL;
    }
    Asert(data);
    arrayList->data = data;
    arrayList->length = 0;
    arrayList->_alloced = MAX_SIZE;
    return arrayList;
}

void arrayList_destroy(ArrayList *arrayList){
    if(arrayList!=NULL) {
        free(arrayList->data); //�ͷ�����ռ�õ��ڴ�
        free(arrayList);       //�ͷŽṹ��ռ�õ��ڴ�
    }
    assert(alloc_test_get_allocated() == 0);
}

void arrayList_show(ArrayList *arrayList){
    if(arrayList_getLength(arrayList) == 0) {
        printf("�������ǿյ�\n");
    } else {
        for(int i = 0;i < arrayList->length;i++)
            printf("%d \t", (int) arrayList->data[i]);
        printf("\n");
    }
}

int arrayList_enlarge(ArrayList *arrayList){
    ArrayListValueEntry *newEntry;
    unsigned int newSize;
    /* ���ѷ���������ڴ�ռ���չΪԭ����2�� */
    newSize = arrayList->_alloced * 2;
    /* ���������·����µ��ڴ�ռ� */
    newEntry = realloc(arrayList->data, sizeof(ArrayListValueEntry) * newSize);
    if (newEntry == NULL) return -1;
    else {
        arrayList->data = newEntry;
        arrayList->_alloced = newSize;
        return 0;
    }
}

int arrayList_insert(ArrayList *arrayList, unsigned int index, ArrayListValueEntry data){
    /*����±��Ƿ�Խ��*/
    if (index > arrayList->length) return -1;
    if (arrayList->length + 1 > arrayList->_alloced) {
        if (arrayList_enlarge(arrayList)) return -1;
    }
    /* �Ѵ�����λ�ü�֮����������ݺ���һλ
     * memmove(void *_Dst,const void *_Src,size_t _Size);
     * Dst: Ŀ���ַ
     * Src: ��ʼ��ַ
     * _Size: ��ַ��
     * */
    if (memmove(&arrayList->data[index + 1], &arrayList->data[index],
                (arrayList->length - index) * sizeof(ArrayListValueEntry)) != NULL){
        /*���±�Ϊindex��λ�ò������� */
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

ArrayList* arrayList_sort(ArrayList* arrayList, int type){
    return arrayList_quick_sort(arrayList, 0, arrayList-> length - 1, type);
}

ArrayList* arrayList_quick_sort(ArrayList* arrayList, int low, int high, int type){
    if (low < high){
        int position = arrayList_quick_sort_partition(arrayList, low, high, type);
        arrayList_quick_sort(arrayList, position + 1, high, type);
        arrayList_quick_sort(arrayList, low, position - 1, type);
    }
    return arrayList;
}

int arrayList_quick_sort_partition(ArrayList* arrayList, int low, int high, int type){
    ArrayListValueEntry temp = arrayList->data[low];
    while (low < high){
        if (type == 0){
            while (low < high && arrayList->data[high] >= temp){
                high--;
            }
        }else {
            while (low < high && arrayList->data[high] <= temp){
                high--;
            }
        }
        arrayList->data[low] = arrayList->data[high];

        if (type == 0){
            while (low < high && arrayList->data[low] <= temp){
                low++;
            }
        }else{
            while (low < high && arrayList->data[low] >= temp){
                low++;
            }
        }
        arrayList->data[high] = arrayList->data[low];
    }
    arrayList->data[low] = temp;
    return low;
}