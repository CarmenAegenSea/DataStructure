#include "BiTree.h"

#include <new>

BiTree MakeBiTree(ElemType e, BiTree L, BiTree R) {
    BiTree T = new (std::nothrow) BitNode;
    if (!T) {
        return nullptr;
    }

    T->date = e;
    T->lchild = L;
    T->rchild = R;
    return T;
}

BiTree FreeBiTree(BiTree T) {
    if (!T) {
        return nullptr;
    }

    FreeBiTree(T->lchild);
    FreeBiTree(T->rchild);
    delete T;
    return nullptr;
}

Status BiTreeEmpty(BiTree T) {
    return T == nullptr ? TRUE : FALSE;
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
