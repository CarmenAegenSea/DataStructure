#ifndef SQSTRING_H
#define SQSTRING_H

#include "Def.h"

typedef struct SqString
{
    char *ch;       /* 字符存储空间，以'\0'结尾 */
    int len;        /* 字符串长度（字节数，不含'\0'） */
    int capacity;   /* 当前分配的存储容量（字节数，含'\0'） */
} SqString;

int InitString(SqString *S);                                             /* 初始化为空串 */
void DestroyString(SqString *S);                                         /* 释放字符串 */
int ClearString(SqString *S);                                            /* 清空字符串 */
int StrAssign(SqString *S, const char *chars);                           /* 用C字符串赋值 */
int StrCopy(SqString *T, const SqString *S);                             /* 复制字符串 */
int StrEmpty(const SqString *S);                                         /* 空串返回TRUE，否则FALSE */
int StrLength(const SqString *S);                                        /* 返回长度（字节数） */
int StrCompare(const SqString *S, const SqString *T);                    /* 字典序比较：小于0、等于0、大于0 */
int Concat(SqString *T, const SqString *S1, const SqString *S2);         /* T = S1 + S2 */
int SubString(SqString *Sub, const SqString *S, int pos, int len);       /* 从第pos个字节起截取len个字节 */
int Index(const SqString *S, const SqString *T, int pos);                /* 从第pos个字节起查找，位置从1开始，未找到返回0 */
int StrInsert(SqString *S, int pos, const SqString *T);                  /* 在第pos个字节前插入T */
int StrDelete(SqString *S, int pos, int len);                            /* 从第pos个字节起删除len个字节 */
int Replace(SqString *S, const SqString *T, const SqString *V);          /* 将S中所有非重叠的T替换为V */

#endif
