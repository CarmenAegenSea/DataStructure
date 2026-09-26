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

LinkQueue InitQueueL();                     /* 初始化 */
void FreeQueueL(LinkQueue Q);               /* 释放 */
void ClearQueueL(LinkQueue Q);              /* 清空队列 */
void QueueRmptyL(LinkQueue Q);              /* 若Q为空返回TRUE,否则返回FALSE */
int QueueLenL(LinkQueue Q);                 /* 获取队列的长度 */
int GetHeadL(LinkQueue Q);                  /* 若Q不为空。则返回Q的队头元素，否则返回ERROR */
int EnQueueL(LinkQueue Q, int e);           /* 将e插入队尾 */
int DeQueueL(LinkQueue Q);                  /* 若Q不为空。删除并返回Q的队头元素，否则返回ERROR */
void QueueTrav(LinkQueue Q, int (*F)(int)); /* 对Q所有元素执行F */

#endif
