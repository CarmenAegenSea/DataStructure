#include "List.h"
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
    L->inc = TIME_SIZE;
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
    L->len = 0;
}

int ListEmpty(SqList L) {
    if (L == NULL) {
        return WARNING;
        if (L->len == 0) {
        return TRUE;
        }
    }
    return FALSE;
}

int ListLen(SqList L) {
    if (L) {
        return L->len;
    }
    return WARNING;
}

int GetElem(SqList L, int i) {
    if (L == NULL || i < 1 || i > L->len) {
        return WARNING;
    }
    return L->elem[i - 1];
}

int PutElem(SqList L, int i, int e) {
    if (L == NULL || i < 1 || i > L->len) {
        return WARNING;
    }
    L->elem[i - 1] = e;
    return OK;
}

int LocateElem(SqList L, int e, int (*F)(int, int)) {
    if (L == NULL || F == NULL) {
        return 0;
    }

    for (int i = 0; i < L->len; i++) {
        if (F(L->elem[i], e)) {
            return i + 1;
        }
    }
    return 0;
}

int PrevElem(SqList L, int e) {
    if (L == NULL) {
        return WARNING;
    }

    for (int i = 0; i < L->len; i++) {
        if (L->elem[i] == e) {
            if (i == 0) {
                return WARNING;
            }
            return L->elem[i - 1];
        }
    }
    return WARNING;
}

int NextElem(SqList L, int e) {
    if (L == NULL) {
        return WARNING;
    }

    for (int i = 0; i < L->len; i++) {
        if (L->elem[i] == e) {
            if (i == L->len - 1) {
                return WARNING;
            }
            return L->elem[i + 1];
        }
    }
    return WARNING;
}

int ListInsert(SqList L, int i, int e) {
    if (L == NULL || i < 1 || i > L->len + 1) {
        return WARNING;
    }

    if (L->len >= L->size) {
        int newSize = L->size + (L->inc > 0 ? L->inc : TIME_SIZE);
        int *newElem = (int*)malloc(newSize * sizeof(int));
        if (!newElem) {
            return WARNING;
        }

        for (int j = 0; j < L->len; j++) {
            newElem[j] = L->elem[j];
        }

        free(L->elem);
        L->elem = newElem;
        L->size = newSize;
    }

    /* 将i位置及之后的元素后移 */
    for (int j = L->len; j >= i; j--) {
        L->elem[j] = L->elem[j - 1];
    }

    L->elem[i - 1] = e;
    L->len++;
    return OK;
}

int ListDelete(SqList L, int i) {
    if (L == NULL || (i < 1 || i > L->len)) {
        return 0;
    }

    int e = L->elem[i - 1];

    for (int j = i; j < L->len; j++) {
        L->elem[j - 1] = L->elem[j];
    }

    L->len--;
    return e;
}

void ListTraverse(SqList L, int (*F)(int, int)) {
    if (L == NULL || F == NULL) {
        return;
    }

    for (int i = 0; i < L->len; i++) {
        (void)F(L->elem[i], i + 1);
    }
}
