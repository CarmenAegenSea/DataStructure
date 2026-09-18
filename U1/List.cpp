#include "List.h"
#include "TIME.h"
#include <stdlib.h>

SqList InitList() {
    SqList L = (SqList)malloc(sizeof(SqListNode));
    if (!L) {
        return NULL;
    }
    L->elem = (int*)malloc(TIME_SIZE * sizeof(int));
    if (!L->elem) {
        free(L);
        return NULL;
    }
    L->len = 0;
    L->size = TIME_SIZE;
    L->inc = 0;
    return L;
}

void FreeList(SqList *L) {
    if (L && *L) {
        if ((*L)->elem) {
            free((*L)->elem);
            (*L)->elem = NULL;
        }
        free(*L);
        *L = NULL;
    }
}

void ClearList(SqList L) {
    if (L) {
        L->len = 0;
    }
}

int ListEmpty(SqList L) {
    if (L->len != 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

int ListLen(SqList L) {
    if (L) {
        return L->len;
    } else {
        return WORNING;
    }
}

int GetElem(SqList L, int i) {
    if (L) {
        return L->elem[i];
    } else {
        return WORNING;
    }
    return OK;
}

int PutElem(SqList L, int i, int e) {
    if (L) {
        L->elem[i] = e;
    } else {
        return WORNING;
    }
    return OK;
}

int LocateElem(SqList L, int e, ) {
    if (L) {
        for(int i = 0; i < L->len; i++) {
            if ()
        }
    }
}

int PrevElem(SqList L, int e) {
    if ()
}