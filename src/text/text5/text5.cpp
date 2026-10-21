#include <stdio.h>
#include <stdlib.h>

#include "BiTree.h"

static BiTree ReadTree(Status *result) {
    int count;
    int *values;
    BiTree tree;
    int i;

    printf("输入先序序列元素个数：");
    if (scanf("%d", &count) != 1 || count <= 0) {
        *result = ERROR;
        return NULL;
    }

    values = (int *)malloc((size_t)count * sizeof(int));
    if (!values) {
        *result = ERROR;
        return NULL;
    }

    printf("输入%d个先序序列元素：\n", count);
    for (i = 0; i < count; ++i) {
        if (scanf("%d", &values[i]) != 1) {
            free(values);
            *result = ERROR;
            return NULL;
        }
    }

    tree = CreateTree(values, count, result);
    free(values);

    if (*result != OK) {
        FreeBiTree(tree);
        return NULL;
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
            newTree = ReadTree(&result);
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

            newSubtree = ReadTree(&result);
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
