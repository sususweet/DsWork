//
// Created by tangyq on 2017/3/16.
//
#include <stdio.h>
#include "matrixCalculation.h"

//�������������
int matrixCalculation(){
    OList* oList1  = OList_get(1);
    OList* oList2  = OList_get(2);

    printf("�����ʼ����ɣ�\n");
    printf("������ĵ�һ��ϡ�����Ϊ:\n");
    OList_showOList(oList1);

    printf("������ĵڶ���ϡ�����Ϊ:\n");
    OList_showOList(oList2);

    printf("����1��ת��Ϊ��\n");
    OList* oListInverse = OList_inverseOList(oList1);
    OList_showOList(oListInverse);

    printf("����2��ת��Ϊ��\n");
    oListInverse = OList_inverseOList(oList2);
    OList_showOList(oListInverse);

    printf("����֮��Ϊ��\n");
    OList* oListPlus = OList_plusOList(oList1,oList2);
    OList_showOList(oListPlus);

    printf("����֮��Ϊ��\n");
    OList* oListMulti = OList_multiOList(oList1,oList2);
    OList_showOList(oListMulti);
    return 0;
}

//����Ļ��ȡ����ķ�������װΪ�������ڸ���
OList* OList_get(int index){
    int rowCount,colCount,scanResult;
    char confirm;
    OList *oList = NULL;

    while(1){
        int temp = 0;
        printf("�������%d��ϡ������������������\n",index);
        scanResult = scanf("%d,%d,%d",&rowCount, &colCount, &temp);
        //��ֹ�Ƿ�������ɳ������
        if (scanResult != 2 || rowCount == 0 || colCount == 0 || temp != 0) {
            fflush (stdin);
            printf("�����ʽ����������ٴ����룡\n");
            continue;
        }else {
            oList = OList_createOList(rowCount, colCount);
            //����Ԫ������
            while (1) {
                int row,col;
                MatrixValue value;
                printf("�������кţ��кţ���ֵ���������кţ��к�Ϊ0��ֹ���룩\n");
                scanResult = scanf("%d,%d,%lf", &row, &col, &value);
                //��ֹ�Ƿ�������ɳ������
                if (scanResult != 3) {
                    fflush (stdin);
                    printf("�����ʽ����������ٴ����룡\n");
                    continue;
                }
                //�����кŻ����к�Ϊ0��ֹ����
                if (row == 0 || col == 0) break;
                //��ֹ�Ƿ�������ɳ������
                if (row > rowCount || col > colCount) {
                    printf("������������Խ�磬�����ᱣ������ݣ�\n");
                    continue;
                }
                OList_addNode(oList, row, col, value);
            }

            printf("������ĵ�%d��ϡ�����Ϊ: \n",index);
            OList_showOList(oList);
            printf("ȷ��������y���������������������ַ���\n");
            fflush(stdin);
            scanf("%c",&confirm);
            if (confirm == 'y') break;
        }
    }
    return oList;
}
