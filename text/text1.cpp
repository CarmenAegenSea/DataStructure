#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "List.h"

int six(int a, int b) {
    if (a * b == 12) {
        return TRUE;
    }
    return FALSE;
}

int printSquare(int value) {
    printf("[ListTraverse]:%.0f", pow(value, 2));
    return OK;
}

int main() {
    SqList textL = InitList();
    ListInsert(textL, 1, 3);
    printf("[ListDelete]:%d\n", ListDelete(textL, 1));
    ClearList(textL);
    printf("[ListEmpty]:%d\n", ListEmpty(textL));

    for (int i = 1; i <= 6; i++) {
        ListInsert(textL, i, (3 + (3 * i)));
    }
    
    for (int i = 1; i <= ListLen(textL); i++) {
        printf("[GetElem]:%d", GetElem(textL, i));
    }
    printf("\n");

    printf("[LocateElem]:%d\n", LocateElem(textL, 1, six));
    printf("[NextElem]:%d\n", NextElem(textL, 15));
    printf("[PrevElem]:%d\n", PrevElem(textL, 9));
    
    ListTraverse(textL, printSquare);
    printf("\n");

    FreeList(&textL);
    return 0;
}