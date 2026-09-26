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
