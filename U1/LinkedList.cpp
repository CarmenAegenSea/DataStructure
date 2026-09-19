#include "LinkList.h"
#include "TIME.h"
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
