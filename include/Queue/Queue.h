#ifndef QUEUE_H
#define QUEUE_H

typedef struct QNode
{
    int data;
    QNode* next;
} QNode, *QueuePtr;

typedef struct
{
    QueuePtr front;
    QueuePtr rear;
} *LinkQueue;

LinkQueue InitQueueL();
void FreeQueueL(LinkQueue Q);
void Clear(LinkQueue Q);
void QueueRmptyL(LinkQueue Q);
int QueueLenL(LinkQueue Q);
int GetHeadL(LinkQueue Q);
int EnQueueL(LinkQueue Q, int e);
int DeQueueL(LinkQueue Q);
void QueueTrav(LinkQueue Q, int (*F)(int));

#endif
