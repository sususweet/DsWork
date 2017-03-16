#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structure/arrayList.h"
#include "structure/linkList.h"
#include "./functions/polyCalculation.h"
#include "functions/expressionCalculation.h"
#include "structure/orthogonalList.h"

int operationArrayList();
int operationLinkList();
int operationStack();

OList* OList_get(int index);

int linkList_compare(LinkListValue value1, LinkListValue value2);

int main(){
    //polyCalculation();
    //operationStack();

    //expCalculation();

    //稀疏矩阵初始化
    OList* oList1  = OList_get(1);
    OList* oList2  = OList_get(2);

    printf("矩阵初始化完成！\n");
    printf("你输入的第一个稀疏矩阵为:\n");
    OList_showOList(oList1);

    printf("你输入的第二个稀疏矩阵为:\n");
    OList_showOList(oList2);

    printf("矩阵1的转置为：\n");
    OList* oListInverse = OList_inverseOList(oList1);
    OList_showOList(oListInverse);

    printf("矩阵2的转置为：\n");
    oListInverse = OList_inverseOList(oList2);
    OList_showOList(oListInverse);

    printf("矩阵之和为：\n");
    OList* oListPlus = OList_plusOList(oList1,oList2);
    OList_showOList(oListPlus);

    printf("矩阵之积为：\n");
    OList* oListMulti = OList_multiOList(oList1,oList2);
    OList_showOList(oListMulti);
    system("pause");
    return 0;
}

OList* OList_get(int index){
    int rowCount,colCount,scanResult;
    char confirm;
    OList *oList = NULL;

    while(1){
        int temp = 0;
        printf("请输入第%d个稀疏矩阵的行数，列数：\n",index);
        scanResult = scanf("%d,%d,%d",&rowCount, &colCount, &temp);
        if (scanResult != 2 || rowCount == 0 || colCount == 0 || temp != 0) {
            fflush (stdin);
            printf("输入格式错误，请检查后再次输入！\n");
            continue;
        }else {
            oList = OList_createOList(rowCount, colCount);
            //非零元素输入
            while (1) {
                int row,col;
                MatrixValue value;
                printf("请输入行号，列号，数值：（输入行号，列号为0终止输入）\n");
                scanResult = scanf("%d,%d,%lf", &row, &col, &value);
                if (scanResult != 3) {
                    fflush (stdin);
                    printf("输入格式错误，请检查后再次输入！\n");
                    continue;
                }
                if (row == 0 || col == 0) break;
                if (row > rowCount || col > colCount) {
                    printf("数据行列索引越界，将不会保存此数据！\n");
                    continue;
                }
                OList_addNode(oList, row, col, value);
            }

            printf("你输入的第%d个稀疏矩阵为: \n",index);
            OList_showOList(oList);
            printf("确认请输入y，否则请输入任意其他字符！\n");
            fflush(stdin);
            scanf("%c",&confirm);
            if (confirm == 'y') break;
        }
    }
    return oList;
}


int linkList_compare(LinkListValue value1, LinkListValue value2){
    if (value1 == value2){
        return 0;
    }else if (value1 > value2) return 1;
    else if (value1 < value2) return -1;
}

int operationStack(){
    LinkListEntry* linkList = linkList_initList();
    linkList_pop(linkList);
    linkList_pop(linkList);
    linkList_pop(linkList);

    linkList_push(linkList, 2);
    linkList_push(linkList, 5);
    linkList_push(linkList, 6);
    linkList_push(linkList, 2);
    linkList_show(linkList);

    linkList_pop(linkList);
    linkList_show(linkList);

    printf("The top value of the stack is : %d\n", linkList_peek(linkList));;
    linkList_show(linkList);

    printf("The length of the stack is : %d\n",linkList_getLength(linkList));
    linkList_destroy(linkList);
}


int operationLinkList(){
    LinkListEntry* linkList = linkList_initList();
    linkList_appendNode(linkList, 1);
    linkList_appendNode(linkList, 2);
    linkList_appendNode(linkList, 5);
    linkList_appendNode(linkList, 6);
    linkList_appendNode(linkList, 2);
    linkList_prependNode(linkList, 1231321);
    linkList_show(linkList);
    linkList_deleteNode(linkList,linkList_getIndexEntryByIndex(linkList,0));
    linkList_show(linkList);
    linkList_getIndexEntryByData(linkList, 2 ,linkList_compare);
    printf("The length of the linkList is : %d\n",linkList_getLength(linkList));
    linkList_destroy(linkList);
}

int operationArrayList() {
    ArrayList *arrayList;
    arrayList = arrayList_init();
    arrayList_append(arrayList,1);
    arrayList_append(arrayList,5);
    arrayList_append(arrayList,2);
    arrayList_append(arrayList,7);
    arrayList_append(arrayList,3);
    arrayList_show(arrayList);
    printf("数组长度为：%d \n",arrayList_getLength(arrayList));
    arrayList_insert(arrayList,2,201);
    arrayList_show(arrayList);
    arrayList_remove(arrayList,4);
    arrayList_show(arrayList);
    printf("201 的数组索引为：%d \n",arrayList_getIndexByValue(arrayList,201));
    printf("数组索引为1的值为：%d \n",(int)arrayList_getValueByIndex(arrayList,1));
    arrayList_destroy(arrayList);

    return 0;
}