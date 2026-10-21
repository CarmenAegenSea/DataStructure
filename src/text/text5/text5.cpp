#include <stdio.h>

#include "BiTree.h"

static BiTree CreateTree(Status *result) {
    int value;
    BiTree left;
    BiTree right;
    BiTree tree;

    if (scanf("%d", &value) != 1) {
        *result = ERROR;
        return NULL;
    }
    if (value == -1) {
        return NULL;
    }

    left = CreateTree(result);
    if (*result != OK) {
        FreeBiTree(left);
        return NULL;
    }

    right = CreateTree(result);
    if (*result != OK) {
        FreeBiTree(left);
        FreeBiTree(right);
        return NULL;
    }

    tree = MakeBiTree(value, left, right);
    if (!tree) {
        FreeBiTree(left);
        FreeBiTree(right);
        *result = ERROR;
    }
    return tree;
}

static Status PrintValue(ElemType value) {
    printf("%d ", value);
    return OK;
}

static void UI(void) {
    printf("1. 从先序表达式创建二叉树\n");
    printf("2. 判断二叉树是否为空\n");
    printf("3. 获取二叉树深度\n");
    printf("4. 替换左子树并返回原左子树\n");
    printf("5. 替换右子树并返回原右子树\n");
    printf("6. 先序遍历\n");
    printf("7. 中序遍历\n");
    printf("8. 后序遍历\n");
    printf("9. 层序遍历\n");
    printf("0. 退出\n");
}

int main(void) {
    BiTree tree = InitBiTree();
    int operation;

    while (TRUE) {
        printf("========================================\n");
        UI();
        printf("输入操作代码：");
        if (scanf("%d", &operation) != 1) {
            break;
        }

        switch (operation) {
        case 1: {
            Status result = OK;
            BiTree newTree;
            printf("输入先序表达式：\n");
            newTree = CreateTree(&result);
            if (result == OK) {
                tree = FreeBiTree(tree);
                tree = newTree;
                printf("二叉树创建成功\n");
            } else {
                FreeBiTree(newTree);
                printf("创建失败，原二叉树未修改\n");
                if (feof(stdin)) {
                    tree = FreeBiTree(tree);
                    return 1;
                }
            }
            break;
        }
        case 2:
            printf(BiTreeEmpty(tree) == TRUE ? "二叉树为空\n" : "二叉树不为空\n");
            break;
        case 3:
            printf("二叉树深度为：%d\n", BiTreeDepth(tree));
            break;
        case 4:
        case 5: {
            Status result = OK;
            BiTree newSubtree;
            BiTree oldSubtree;
            if (BiTreeEmpty(tree) == TRUE) {
                printf("二叉树为空\n");
                break;
            }

            printf("输入先序表达式：\n");
            newSubtree = CreateTree(&result);
            if (result != OK) {
                FreeBiTree(newSubtree);
                printf("创建失败，原子树未修改\n");
                if (feof(stdin)) {
                    tree = FreeBiTree(tree);
                    return 1;
                }
                break;
            }

            oldSubtree = operation == 4 ? ReplaceLeft(tree, newSubtree)
                                        : ReplaceRight(tree, newSubtree);
            FreeBiTree(oldSubtree);
            printf("子树替换成功\n");
            break;
        }
        case 6:
            PreOrderTrav(tree, PrintValue);
            printf("\n");
            break;
        case 7:
            InOrderTrav(tree, PrintValue);
            printf("\n");
            break;
        case 8:
            PostOrderTrav(tree, PrintValue);
            printf("\n");
            break;
        case 9:
            LevelOrderTrav(tree, PrintValue);
            printf("\n");
            break;
        case 0:
            tree = FreeBiTree(tree);
            printf("退出程序\n");
            return 0;
        default:
            printf("无效的操作代码\n");
            break;
        }
    }

    tree = FreeBiTree(tree);
    printf("\n输入结束，程序退出\n");
    return 0;
}
