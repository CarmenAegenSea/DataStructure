#include "LinkList.h"
#include "Def.h"
#include <stdlib.h>

LinkList InitList() {
    LinkList L = (LinkList)malloc(sizeof(LNode));
    if (!L) {
        return NULL;
    }

    L->next = NULL;
    L->data = 0;       /* 整型首节点记录长度 */
    return L;
}

void FreeList(LinkList *L) {
    if (L && *L) {
        LNode *p = (*L)->next;
        while (p) {
            LNode *q = p->next;
            free(p);
            p = q;
        }
        free(*L);
        *L = NULL;
    }
}

void ClearList(LinkList L) {
    L->data = 0;
    LNode *p = L->next;
    while (p) {
        LNode *q = p->next;
        free(p);
        p = q;
    }
    L->next = NULL;
}

int ListEmpty(LinkList L) {
    if (L == NULL || L->data == 0) {
        return TRUE;
    }
    return FALSE;
}

int ListLen(LinkList L) {   /* 首节点记录长度，保留ListLen满足习惯 */
    if (!L) {
        return WARNING;
    }
    return L->data;
}

int GetElem(LinkList L, int i) {
    if (!L || i < 1 || i > L->data) {
        return WARNING;
    }

    LNode *p = L->next;
    for (int j = 1; j < i; j++) {
        p = p->next;
    }
    return p->data;
}

int PutElem(LinkList L, int i, int e) {
    if (!L || i < 1 || i > L->data) {
        return WARNING;
    }

    LNode *p = L->next;
    for (int j = 1; j < i; j++) {
        p = p->next;
    }
    p->data = e;
    return OK;
}

int LocateElem(LinkList L, int e, int (*F)(int, int)) {
    if (!L || !F) {
        return 0;
    }

    LNode *p = L->next;
    int pos = 1;
    while (p) {
        if (F(p->data, e)) {
            return pos;
        }
        p = p->next;
        pos++;
    }
    return 0;
}

int PrevElem(LinkList L, int e) {
    if (!L || !L->next) {
        return WARNING;
    }

    LNode *p = L->next;
    LNode *prev = NULL;
    while (p) {
        if (p->data == e) {
            if (prev == NULL) {
                return WARNING;
            }
            return prev->data;
        }
        prev = p;
        p = p->next;
    }
    return WARNING;
}

int NextElem(LinkList L, int e) {
    if (!L || !L->next) {
        return WARNING;
    }

    LNode *p = L->next;
    while (p) {
        if (p->data == e) {
            if (p->next == NULL) {
                return WARNING;
            }
            return p->next->data;
        }
        p = p->next;
    }
    return WARNING;
}

int ListInsert(LinkList L, int i, int e) {
    if (!L || i < 1 || i > L->data + 1) {
        return WARNING;
    }

    LNode *p = L;
    for (int j = 1; j < i; j++) {
        p = p->next;
    }

    LNode *newNode = (LNode*)malloc(sizeof(LNode));
    if (!newNode) {
        return WARNING;
    }

    newNode->data = e;
    newNode->next = p->next;
    p->next = newNode;
    L->data++;
    return OK;
}

int ListDelete(LinkList L, int i) {
    if (!L || i < 1 || i > L->data) {
        return WARNING;
    }

    LNode *p = L;
    for (int j = 1; j < i; j++) {
        p = p->next;
    }

    LNode *del = p->next;
    int e = del->data;
    p->next = del->next;
    free(del);
    L->data--;
    return e;
}

void ListTraverse(LinkList L, int (*F)(int, int)) {
    if (!L || !F) {
        return;
    }

    LNode *p = L->next;
    int pos = 1;
    while (p) {
        (void)F(p->data, pos);
        p = p->next;
        pos++;
    }
}