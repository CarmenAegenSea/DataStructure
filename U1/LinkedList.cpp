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
    if (!L) {
        return WARNING;
    }
}