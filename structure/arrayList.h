//
// Created by tangyq on 2017/3/2.
//

#ifndef PROJECT1_ARRAYLIST_H
#define PROJECT1_ARRAYLIST_H

#ifdef __cplusplus
extern "C" {
#endif

/* 指向数组中数据类型的指针. */
typedef void * ArrayListValueEntry;

/* 动态数组结构，使用arrayList_new函数来创建新的动态数组. */
typedef struct _ArrayList ArrayList;

/* 定义动态数组结构. */
struct _ArrayList {
    ArrayListValueEntry *data;   /* 数组的访问入口. */
    unsigned int length;    /* 数组中已存储的数据数. */
    unsigned int _alloced;  /* 数组的最大长度 */
};

#define MAX_SIZE 1024

/*************************************
*@desc: 初始化arrayList
*************************************
*/
ArrayList* arrayList_init();

/*************************************
*@desc: 释放arrayList占用的内存空间
*@param: arrayList->操作的arrayList
*************************************
*/
void arrayList_destroy(ArrayList *arrayList);

/*************************************
*@desc: 扩充arrayList的内存空间
*@param: arrayList->操作的arrayList
*************************************
*/

void arrayList_show(ArrayList *arrayList);

int arrayList_enlarge(ArrayList *arrayList);

/*************************************
*@desc: 插入新元素
*@param: arrayList->操作的arrayList
*@param: index->插入元素位置
*@param: data-> 插入的元素
*************************************
*/
int arrayList_insert(ArrayList *arrayList, unsigned int index, ArrayListValueEntry data);

/*************************************
*@desc: 在arrayList开始处插入新元素
*@param: arrayList->操作的arrayList
*@param: data-> 插入的元素
*************************************
*/
int arrayList_prepend(ArrayList *arrayList, ArrayListValueEntry data);


/*************************************
*@desc: 在arrayList结束处插入新元素
*@param: arrayList->操作的arrayList
*@param: data-> 插入的元素
*************************************
*/
int arrayList_append(ArrayList *arrayList, ArrayListValueEntry data);

/*************************************
*@desc: 移除arrayList元素
*@param: arrayList->操作的arrayList
*@param: index-> 移除元素位置
*@param: removeLength-> 移除长度
*************************************
*/
int arrayList_removeRange(ArrayList *arrayList, unsigned int index, unsigned int removeLength);

/*************************************
*@desc: 移除单个arrayList元素
*@param: arrayList->操作的arrayList
*@param: index-> 移除元素位置
*************************************
*/
int arrayList_remove(ArrayList *arrayList, unsigned int index);

/*************************************
*@desc: 获取arrayList元素个数
*@param: arrayList->操作的arrayList
*************************************
*/
int arrayList_getLength(ArrayList *arrayList);

/*************************************
*@desc: 根据位置查找arrayList元素值
*@param: arrayList->操作的arrayList
*@param: index->元素位置
*************************************
*/
ArrayListValueEntry arrayList_getValueByIndex(ArrayList *arrayList, unsigned int index);

/*************************************
*@desc: 查找arrayList中指定元素位置
*@param: arrayList->操作的arrayList
*@param: data->待检测元素
*************************************
*/
int arrayList_getIndexByValue(ArrayList *arrayList, ArrayListValueEntry data);

/*************************************
*@desc: arrayList排序
*@param: arrayList->操作的arrayList
*@param: type->排序类型，0为升序，1为降序
*@return: 排序后的arrayList
*************************************
*/
ArrayList* arrayList_sort(ArrayList* arrayList, int type);

ArrayList* arrayList_quick_sort(ArrayList* arrayList, int low, int high, int type);

int arrayList_quick_sort_partition(ArrayList* arrayList, int low, int high, int type);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //PROJECT1_ARRAYLIST_H
