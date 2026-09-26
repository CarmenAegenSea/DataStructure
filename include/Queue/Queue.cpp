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
