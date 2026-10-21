#ifndef BITTREE_H
#define BITTREE_H

#include "Def.h"

typedef struct BitNode
{
    ElemType date;
    struct BitNode *lchild, *rchild;
} BitNode, *BiTree;

BiTree InitBiTree();                                        /* 构造并返回一个空二叉树 */
BiTree MakeBiTree(ElemType e, BiTree L, BiTree R);          /* 创建根节点值为e、左右子树分别为L和R的二叉树 */
BiTree FreeBiTree(BiTree T);                                /* 回收T的所有节点，返回null */
Status BiTreeEmpty(BiTree T);                               /* 若T为空返回TRUE，否则返回FALSE */
int BiTreeDepth(BiTree T);                                  /* 返回T的深度 */
ElemType Root(BiTree T);                                    /* 返回T的根 */
ElemType Value(BiTree T, int node);                         /* 若e为T元素则返回node的值 */
void Assign(BiTree T, int node, ElemType e);                /* 将T中node的值设为e */
BiTree Parent(BiTree T, int node);                          /* 返回node的双亲，若node是root返回null */
BiTree LeftChild(BiTree T, int node);                       /* 返回node的左子，没有返回null */
BiTree RightChild(BiTree T, int node);                      /* 返回node的右子，没有返回null */
BiTree ReplaceLeft(BiTree T, BiTree LT);                    /* 替换左子树并返回原左子树 */
BiTree ReplaceRight(BiTree T, BiTree RT);                   /* 替换右子树并返回原右子树 */
Status PreOrderTrav(BiTree T, Status (*F)(ElemType e));     /* 先序遍历T的所有节点并对每个节点调用F, 一旦F失败则返回ERROR */
Status InOrderTrav(BiTree T, Status (*F)(ElemType e));      /* 中序遍历T的所有节点并对每个节点调用F, 一旦F失败则返回ERROR */
Status PostOrderTrav(BiTree T, Status (*F)(ElemType e));    /* 后序遍历T的所有节点并对每个节点调用F, 一旦F失败则返回ERROR */
Status LevelOrderTrav(BiTree T, Status (*F)(ElemType e));   /* 层序遍历T的所有节点并对每个节点调用F. 一旦F失败则返回ERROR */

#endif
