#ifndef LIST_H
#define LIST_H

#include "Def.h"

#define TIME_SIZE 5

typedef struct
{
    int *elem;
    int len;
    int size;
    int inc;
} SqListNode, *SqList;

SqList InitList();                                       /* 初始化 */
void FreeList(SqList *L);                                /* 释放 */
void ClearList(SqList L);                                /* 清空顺序表 */
int ListEmpty(SqList L);                                 /* 若L为空返回TRUE,否则返回FALSE */
int ListLen(SqList L);                                   /* 获取顺序表长度 */
int GetElem(SqList L, int i);                            /* 返回L的第i个值 */
int PutElem(SqList L, int i, int e);                     /* 对L的第i个值设为e */
int LocateElem(SqList L, int e, int (*F)(int, int));     /* 返回L中第一个与e满足F关系的元素的下标，若没有返回0 */
int PrevElem(SqList L, int e);                           /* 若e是L元素且不是第一个，返回其前驱值 */
int NextElem(SqList L, int e);                           /* 若e是L元素且不是最后一个，返回其后继值 */
int ListInsert(SqList L, int i, int e);                  /* 在L的i位置插入元素e,顺序表长度++ */
int ListDelete(SqList L, int i);                         /* 删除L在i位置的元素并返回其值，顺序表长度--，若不存在，返回0 */
void ListTraverse(SqList L, int (*F)(int, int));         /* 对L的所有元素执行F */

#endif