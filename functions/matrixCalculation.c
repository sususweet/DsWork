//
// Created by tangyq on 2017/3/16.
//
#include <stdio.h>
#include "matrixCalculation.h"

//矩阵计算主函数
int matrixCalculation(){
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
    return 0;
}

//从屏幕获取矩阵的方法，封装为函数便于复用
OList* OList_get(int index){
    int rowCount,colCount,scanResult;
    char confirm;
    OList *oList = NULL;

    while(1){
        int temp = 0;
        printf("请输入第%d个稀疏矩阵的行数，列数：\n",index);
        scanResult = scanf("%d,%d,%d",&rowCount, &colCount, &temp);
        //防止非法输入造成程序崩溃
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
                //防止非法输入造成程序崩溃
                if (scanResult != 3) {
                    fflush (stdin);
                    printf("输入格式错误，请检查后再次输入！\n");
                    continue;
                }
                //输入行号或者列号为0终止输入
                if (row == 0 || col == 0) break;
                //防止非法输入造成程序崩溃
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
