#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "List.h"

/**
 * text1.cpp
 * 上机作业1
 * 实现顺序表并测试
 */

int six(int a, int b) {
    if (a * b == 12) {
        return TRUE;
    }
    return FALSE;
}

int printSquare(int value) {
    printf("%d ", pow(value, 2));
    return OK;
}

void printList(SqList L) {
    for (int i = 1; i <= ListLen(L); i++) {
        printf("%d ", GetElem(L, i));
    }
    printf("\n");
}

void ui(){
    printf("1. 输出顺序表\n");
    printf("2. 清空顺序表\n");
    printf("3. 判断顺序表是否为空\n");
    printf("4. 获取顺序表长度\n");
    printf("5. 获取顺序表第i个元素\n");
    printf("6. 对顺序表第i个元素设为e\n");
    printf("7. 返回顺序表中第一个与e满足F关系的元素的下标\n");
    printf("8. 返回顺序表中第一个与e满足F关系的元素的前驱值\n");
    printf("9. 返回顺序表中第一个与e满足F关系的元素的后继值\n");
    printf("10. 在顺序表第i个位置插入元素e\n");
    printf("11. 删除顺序表第i个位置的元素\n");
    printf("12. 对顺序表的所有元素执行F函数\n");
    printf("0. 退出\n");
}

int main() {
    SqList textL = InitList();

    while(TRUE) {
        printf("========================================\n");
        ui();
        int turn;
        printf("输入操作代码");
        scanf("%d", &turn);
        switch(turn) {
            case 1:
                printf("顺序表元素为: ");
                printList(textL);
                break;
            case 2:
                printf("表已清空\n");
                ClearList(textL);
                break;
            case 3:
                if (ListEmpty(textL)) {
                    printf("顺序表为空\n");
                } else {
                    printf("顺序表不为空\n");
                }
                break;
            case 4:
                printf("顺序表长度为: %d\n", ListLen(textL));
                break;
            case 5: {
                int i;
                printf("输入i: ");
                scanf("%d", &i);
                int elem = GetElem(textL, i);
                if (elem == WARNING) {
                    printf("输入位置无效\n");
                } else {
                    printf("第%d个元素为: %d\n", i, elem);
                }
            }
                break;
            case 6: {
                int i, e;
                printf("输入i和e: ");
                scanf("%d %d", &i, &e);
                if (PutElem(textL, i, e) == OK) {
                    printf("设置成功\n");
                } else {
                    printf("设置失败\n");
                }
            }
                break;
            case 7: {
                int e;
                printf("输入e: ");
                scanf("%d", &e);
                int index = LocateElem(textL, e, six);
                if (index == 0) {
                    printf("未找到\n");
                } else {
                    printf("下标为: %d\n", index);    
                }
            }
                break;
            case 8: {
                int e;
                printf("输入e: ");
                scanf("%d", &e);
                int prev = PrevElem(textL, e);
                if (prev == WARNING) {
                    printf("未找到\n");
                } else {
                    printf("前驱为: %d\n", prev);
                }
            }
                break;
            case 9: {
                int e;
                printf("输入e: ");
                scanf("%d", &e);
                int next = NextElem(textL, e);
                if (next == WARNING) {
                    printf("未找到\n");
                } else {
                    printf("后继为: %d\n", next);
                }
            }
                break;
            case 10: {
                int i, e;
                printf("输入i和e: ");
                scanf("%d %d", &i, &e);
                if (ListInsert(textL, i, e) == OK) {
                    printf("插入成功\n");
                } else {
                    printf("插入失败\n");
                }
            }
                break;
            case 11: {
                int i;
                printf("输入i: ");
                scanf("%d", &i);
                int deleted = ListDelete(textL, i);
                if (deleted == WARNING) {
                    printf("删除失败\n");
                } else {
                    printf("删除成功, 删除的元素为: %d\n", deleted);
                }
            }
                break;
            case 12:
                printf("顺序表元素的平方为: ");
                ListTraverse(textL, printSquare);
                printf("\n");
                break;
            case 0:
                FreeList(&textL);
                printf("退出程序\n");
                return 0;
            default:
                printf("无效的操作代码\n");
                break;
        }
    }
    return 0;
}