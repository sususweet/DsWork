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

    //ϡ������ʼ��
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
    system("pause");
    return 0;
}

OList* OList_get(int index){
    int rowCount,colCount,scanResult;
    char confirm;
    OList *oList = NULL;

    while(1){
        int temp = 0;
        printf("�������%d��ϡ������������������\n",index);
        scanResult = scanf("%d,%d,%d",&rowCount, &colCount, &temp);
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
                if (scanResult != 3) {
                    fflush (stdin);
                    printf("�����ʽ����������ٴ����룡\n");
                    continue;
                }
                if (row == 0 || col == 0) break;
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
    printf("���鳤��Ϊ��%d \n",arrayList_getLength(arrayList));
    arrayList_insert(arrayList,2,201);
    arrayList_show(arrayList);
    arrayList_remove(arrayList,4);
    arrayList_show(arrayList);
    printf("201 ����������Ϊ��%d \n",arrayList_getIndexByValue(arrayList,201));
    printf("��������Ϊ1��ֵΪ��%d \n",(int)arrayList_getValueByIndex(arrayList,1));
    arrayList_destroy(arrayList);

    return 0;
}