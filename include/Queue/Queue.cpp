#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

LinkQueue InitQueueL() {
    LinkQueue Q;
    if (!(Q = (LinkQueue)malloc(sizeof(*Q)))) {
        exit(OVERFLOW);
    }
    if (!(Q->front=Q->rear=(QueuePtr)malloc(sizeof(QNode)))) {
        exit(OVERFLOW);
    }
    Q->front->next=NULL;
    return Q;
}

LinkQueue FreeQueueL(LinkQueue Q) {
    if (!Q) {
        return NULL;
    }

    QueuePtr p = Q->front;
    while (p) {
        QueuePtr q = p;
        p = p->next;
        free(q);
    }

    free(Q);
    return NULL;
}

void ClearQueueL(LinkQueue Q) {

}

int EnQueueL(LinkQueue Q, int e) {
    if (!Q) {
        return ERROR;
    }

    QueuePtr p;
    if (!(p = (QueuePtr)malloc(sizeof(QNode)))) {
        return ERROR;
    }

    p->data = e;
    p->next = NULL;
    Q->rear->next = p;
    Q->rear = p;
    return OK;
}

int DeQueueL(LinkQueue Q) {
    if (!Q || Q->front == Q->front) {
        return WARNING;
    }

    QueuePtr p = Q->front->next;
    int e = p->data;
    if (Q->rear == p) {
        Q->rear = Q->front;
    }
    free(p);
    return e;
}
