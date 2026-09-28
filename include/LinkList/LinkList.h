#ifndef LINKLIST_H
#define LINKLIST_H

#include "Def.h"

typedef struct LNode
{
    int data;                  /* 数据域 */
    struct LNode *next;        /* 指针域，指向后继结点 */
} LNode, *LinkList;

LinkList InitList();                                            /* 初始化 */
void FreeList(LinkList *L);                                     /* 释放整条链表 */
void ClearList(LinkList L);                                     /* 清空 */
int ListEmpty(LinkList L);                                      /* 空返回TRUE，否则FALSE */
int ListLen(LinkList L);                                        /* 返回长度 */
int GetElem(LinkList L, int i);                                 /* 返回第i个元素值 */
int PutElem(LinkList L, int i, int e);                          /* 把第i个元素设为e */
int LocateElem(LinkList L, int e, int (*F)(int, int));          /* 返回第一个满足关系的元素位置 */
int PrevElem(LinkList L, int e);                                /* 返回e的前驱值 */
int NextElem(LinkList L, int e);                                /* 返回e的后继值 */
int ListInsert(LinkList L, int i, int e);                       /* 在第i个位置插入e */
int ListDelete(LinkList L, int i);                              /* 删除第i个元素并返回其值 */
void ListTraverse(LinkList L, int (*F)(int, int));              /* 遍历执行F */

#endif
