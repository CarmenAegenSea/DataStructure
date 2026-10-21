#include "BiTree.h"

#include <new>
#include <queue>

namespace {

void DestroyTree(BiTree tree) {
    if (!tree) {
        return;
    }

    DestroyTree(tree->lchild);
    DestroyTree(tree->rchild);
    delete tree;
}

BiTree CreateTreeFromPreorder(const ElemType values[], int count, int *index,
                              Status *result) {
    if (*index >= count) {
        *result = ERROR;
        return nullptr;
    }

    const ElemType value = values[(*index)++];
    if (value == -1) {
        return nullptr;
    }

    BiTree left = CreateTreeFromPreorder(values, count, index, result);
    if (*result != OK) {
        FreeBiTree(left);
        return nullptr;
    }

    BiTree right = CreateTreeFromPreorder(values, count, index, result);
    if (*result != OK) {
        FreeBiTree(left);
        FreeBiTree(right);
        return nullptr;
    }

    BiTree tree = MakeBiTree(value, left, right);
    if (!tree) {
        FreeBiTree(left);
        FreeBiTree(right);
        *result = ERROR;
    }
    return tree;
}

int Depth(BiTree tree) {
    if (!tree) {
        return 0;
    }

    const int leftDepth = Depth(tree->lchild);
    const int rightDepth = Depth(tree->rchild);
    return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
}

BiTree FindNode(BiTree tree, int value) {
    if (!tree || tree->date == value) {
        return tree;
    }

    BiTree found = FindNode(tree->lchild, value);
    return found ? found : FindNode(tree->rchild, value);
}

BiTree FindParent(BiTree tree, BiTree child) {
    if (!tree || !child) {
        return nullptr;
    }
    if (tree->lchild == child || tree->rchild == child) {
        return tree;
    }

    BiTree parent = FindParent(tree->lchild, child);
    return parent ? parent : FindParent(tree->rchild, child);
}

Status PreOrder(BiTree tree, Status (*F)(ElemType)) {
    if (!tree) {
        return OK;
    }
    if (F(tree->date) != OK ||
        PreOrder(tree->lchild, F) != OK ||
        PreOrder(tree->rchild, F) != OK) {
        return ERROR;
    }
    return OK;
}

Status InOrder(BiTree tree, Status (*F)(ElemType)) {
    if (!tree) {
        return OK;
    }
    if (InOrder(tree->lchild, F) != OK ||
        F(tree->date) != OK ||
        InOrder(tree->rchild, F) != OK) {
        return ERROR;
    }
    return OK;
}

Status PostOrder(BiTree tree, Status (*F)(ElemType)) {
    if (!tree) {
        return OK;
    }
    if (PostOrder(tree->lchild, F) != OK ||
        PostOrder(tree->rchild, F) != OK ||
        F(tree->date) != OK) {
        return ERROR;
    }
    return OK;
}

}  // namespace

BiTree InitBiTree() {
    return nullptr;
}

BiTree MakeBiTree(ElemType e, BiTree L, BiTree R) {
    return new (std::nothrow) BitNode{e, L, R};
}

BiTree CreateTree(const ElemType values[], int count, Status *result) {
    if (!result) {
        return nullptr;
    }
    *result = ERROR;
    if (!values || count <= 0) {
        return nullptr;
    }

    *result = OK;
    int index = 0;
    BiTree tree = CreateTreeFromPreorder(values, count, &index, result);
    if (*result == OK && index != count) {
        *result = ERROR;
    }
    if (*result != OK) {
        FreeBiTree(tree);
        return nullptr;
    }
    return tree;
}

BiTree FreeBiTree(BiTree T) {
    DestroyTree(T);
    return nullptr;
}

Status BiTreeEmpty(BiTree T) {
    return T == nullptr ? TRUE : FALSE;
}

int BiTreeDepth(BiTree T) {
    return Depth(T);
}

ElemType Root(BiTree T) {
    return T ? T->date : WARNING;
}

ElemType Value(BiTree T, int node) {
    BiTree found = FindNode(T, node);
    return found ? found->date : WARNING;
}

void Assign(BiTree T, int node, ElemType e) {
    BiTree found = FindNode(T, node);
    if (found) {
        found->date = e;
    }
}

BiTree Parent(BiTree T, int node) {
    BiTree found = FindNode(T, node);
    return FindParent(T, found);
}

BiTree LeftChild(BiTree T, int node) {
    BiTree found = FindNode(T, node);
    return found ? found->lchild : nullptr;
}

BiTree RightChild(BiTree T, int node) {
    BiTree found = FindNode(T, node);
    return found ? found->rchild : nullptr;
}

BiTree ReplaceLeft(BiTree T, BiTree LT) {
    if (!T) {
        return nullptr;
    }

    BiTree oldLeft = T->lchild;
    T->lchild = LT;
    return oldLeft;
}

BiTree ReplaceRight(BiTree T, BiTree RT) {
    if (!T) {
        return nullptr;
    }

    BiTree oldRight = T->rchild;
    T->rchild = RT;
    return oldRight;
}

Status PreOrderTrav(BiTree T, Status (*F)(ElemType)) {
    return F ? PreOrder(T, F) : ERROR;
}

Status InOrderTrav(BiTree T, Status (*F)(ElemType)) {
    return F ? InOrder(T, F) : ERROR;
}

Status PostOrderTrav(BiTree T, Status (*F)(ElemType)) {
    return F ? PostOrder(T, F) : ERROR;
}

Status LevelOrderTrav(BiTree T, Status (*F)(ElemType)) {
    if (!F) {
        return ERROR;
    }
    if (!T) {
        return OK;
    }

    std::queue<BiTree> nodes;
    nodes.push(T);
    while (!nodes.empty()) {
        BiTree node = nodes.front();
        nodes.pop();

        if (F(node->date) != OK) {
            return ERROR;
        }
        if (node->lchild) {
            nodes.push(node->lchild);
        }
        if (node->rchild) {
            nodes.push(node->rchild);
        }
    }
    return OK;
}
