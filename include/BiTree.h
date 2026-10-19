#ifndef BITTREE_H
#define BITTRTEE_H

#include "Def.h"
typedef int ElemType;

typedef struct BitNode
{
    ElemType date;
    struct BitNode *lchild, *rchild;
} BitNode, *BiTree;

BiTree MakeBiTree(ElemType e, BiTree L, BiTree R);     /* 组建一个二叉树，头结点值为e, 左右字数为LR */
BiTree FreeBiTree(BiTree T);
BiTree BiTreeEmpty(BiTree T);
BiTree ReplaceLeft(BiTree T, BiTree LT);
BiTree ReplaceRight(BiTree T, BiTree RT);

#endif
