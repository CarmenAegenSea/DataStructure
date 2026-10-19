#ifndef BITTREE_H
#define BITTRTEE_H

#include "Def.h"
typedef ElemType int;

typedef struct BitNode
{
    ElemType date;
    struct BitNode *lchild, *rchild;
} BitNode, *BitTree;

#endif
