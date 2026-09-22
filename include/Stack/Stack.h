#ifndef STACK_H
#define STACK_H

#include "Def.h"

#define STACK_INIT_SIZE 5      /* 栈初始容量 */

typedef struct SqStack
{
    int *elem;                 /* 存储空间基址 */
    int top;                   /* 栈顶指针（指向栈顶元素的下一个位置） */
    int size;                  /* 当前分配的容量 */
    int inc;                   /* 扩容增量 */
} SqStackNode, *SqStack;

SqStack InitStack();                            /* 初始化空栈 */
void FreeStack(SqStack *S);                     /* 释放栈 */
void ClearStack(SqStack *S);                    /* 清空栈 */
int StackEmpty(SqStack S);                      /* 空返回TRUE，否则FALSE */
int StackLen(SqStack S);                        /* 返回栈中元素个数 */
int GetTop(SqStack S);                          /* 返回栈顶元素值，栈空返回0 */
int Push(SqStack S, int e);                     /* 入栈：将e压入栈顶，成功返回OK，失败返回ERROR */
int Pop(SqStack S);                             /* 出栈：弹出并返回栈顶元素，栈空返回0 */
void StackTraverse(SqStack S, int (*F)(int));   /* 自栈底到栈顶对每个元素执行F */

#endif
