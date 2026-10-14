#ifndef GLINKLIST_H
#define GLINKLIST_H

#include "Def.h"
#include "SqString.h"

typedef enum {ATOM, LIST} ElemTag;  /* 结点类型标志 */
typedef int AtomType;               /* 原子类型 */
typedef struct GLinkList            /* 广义表结点 */
{
    ElemTag tag;                    /* 类型标志 */
    union {  
        AtomType atom;              /* 原子数据 */
        GLinkList list;             /* 链表数据 */
    };
    GLinkList *next;                /* 指向下一个结点的指针 */
} *GLinkList;

GLinkList InitGLinkList();  /* 初始化广义表 */
GLinkList NewGLinkList(SqString *S);  /* 根据字符串创建广义表 */
void FreeGLinkList(GLinkList *L);  /* 释放广义表 */
GLinkList CopyGLinkList(const GLinkList L);  /* 复制广义表 */
int GlinkListLen(const GLinkList L);  /* 获取广义表长度 */
int GlinkListDepth(const GLinkList L);  /* 获取广义表深度 */
int GlinkListEmpty(const GLinkList L);  /* 判断广义表是否为空 */
AtomType GetGLinkListHead(const GLinkList L);  /* 获取广义表的头 */
GLinkList GetGLinkListTail(const GLinkList L);  /* 获取广义表的尾 */
void InsertFirst_GLinkList(GLinkList *L, AtomType e);  /* 在广义表的头部插入原子元素 */
void DeleteFirst_GLinkList(GLinkList *L, AtomType *e);  /* 删除广义表的头部元素并返回 */
void TraverseGLinkList(const GLinkList L, void (*f)(AtomType));  /* 遍历广义表 */

#endif
