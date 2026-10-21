#include <stdio.h>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "BiTree.h"

namespace {

BiTree BuildPreorderTree(const std::vector<int> &values, size_t *index,
                         Status *inputOk, Status *allocationFailed) {
    if (*index >= values.size()) {
        *inputOk = ERROR;
        return nullptr;
    }

    const int value = values[(*index)++];
    if (value == -1) {
        return nullptr;
    }

    BiTree left = BuildPreorderTree(values, index, inputOk, allocationFailed);
    if (*inputOk != OK) {
        FreeBiTree(left);
        return nullptr;
    }

    BiTree right = BuildPreorderTree(values, index, inputOk, allocationFailed);
    if (*inputOk != OK) {
        FreeBiTree(left);
        FreeBiTree(right);
        return nullptr;
    }

    BiTree tree = MakeBiTree(value, left, right);
    if (!tree) {
        FreeBiTree(left);
        FreeBiTree(right);
        *inputOk = ERROR;
        *allocationFailed = TRUE;
    }
    return tree;
}

BiTree ReadPreorderTree(Status *inputOk, Status *allocationFailed) {
    std::string expression;
    printf("输入先序表达式（空子树用-1表示，例如：1 2 -1 -1 3 -1 -1）：\n");
    if (!std::getline(std::cin >> std::ws, expression)) {
        *inputOk = ERROR;
        return nullptr;
    }

    std::istringstream input(expression);
    std::vector<int> values;
    int value;
    while (input >> value) {
        values.push_back(value);
    }
    if (!input.eof() || values.empty()) {
        *inputOk = ERROR;
        return nullptr;
    }

    size_t index = 0;
    BiTree tree = BuildPreorderTree(values, &index, inputOk, allocationFailed);
    if (*inputOk == OK && index != values.size()) {
        *inputOk = ERROR;
    }
    if (*inputOk != OK) {
        FreeBiTree(tree);
        return nullptr;
    }
    return tree;
}

BiTree BuildArrayTree(const std::vector<int> &values, size_t index,
                      Status *allocationFailed) {
    if (index >= values.size() || values[index] == -1) {
        return nullptr;
    }

    BiTree left = BuildArrayTree(values, index * 2 + 1, allocationFailed);
    BiTree right = BuildArrayTree(values, index * 2 + 2, allocationFailed);
    if (*allocationFailed == TRUE) {
        FreeBiTree(left);
        FreeBiTree(right);
        return nullptr;
    }

    BiTree tree = MakeBiTree(values[index], left, right);
    if (!tree) {
        FreeBiTree(left);
        FreeBiTree(right);
        *allocationFailed = TRUE;
    }
    return tree;
}

Status PrintValue(ElemType value) {
    printf("%d ", value);
    return OK;
}

void ShowMenu() {
    printf("1. 输出二叉树\n");
    printf("2. 从数组创建二叉树\n");
    printf("3. 判断二叉树是否为空\n");
    printf("4. 获取二叉树深度\n");
    printf("5. 替换左子树并返回原左子树\n");
    printf("6. 替换右子树并返回原右子树\n");
    printf("7. 先序遍历二叉树的所有节点并对每个节点调用F\n");
    printf("8. 中序遍历二叉树的所有节点并对每个节点调用F\n");
    printf("9. 后序遍历二叉树的所有节点并对每个节点调用F\n");
    printf("10. 层序遍历二叉树的所有节点并对每个节点调用F\n");
    printf("0. 退出\n");
}

}  // namespace

int main() {
    BiTree tree = InitBiTree();

    while (TRUE) {
        int operation;
        printf("========================================\n");
        ShowMenu();
        printf("输入操作代码：");
        if (scanf("%d", &operation) != 1) {
            break;
        }

        switch (operation) {
        case 1:
            if (BiTreeEmpty(tree) == TRUE) {
                printf("二叉树为空\n");
            } else {
                printf("二叉树先序遍历：");
                PreOrderTrav(tree, PrintValue);
                printf("\n");
            }
            break;
        case 2: {
            int count;
            printf("输入数组元素个数：");
            if (scanf("%d", &count) != 1 || count < 0) {
                printf("输入无效\n");
                break;
            }

            std::vector<int> values(static_cast<size_t>(count));
            printf("按层序输入%d个结点值（-1表示空结点）：\n", count);
            Status inputOk = OK;
            for (int i = 0; i < count; ++i) {
                if (scanf("%d", &values[static_cast<size_t>(i)]) != 1) {
                    inputOk = ERROR;
                    break;
                }
            }
            if (inputOk != OK) {
                tree = FreeBiTree(tree);
                return 1;
            }

            for (size_t i = 1; i < values.size(); ++i) {
                if (values[i] != -1 && values[(i - 1) / 2] == -1) {
                    inputOk = ERROR;
                    break;
                }
            }
            if (inputOk != OK) {
                printf("输入无效：非空结点的父结点不能是空结点\n");
                break;
            }

            Status allocationFailed = FALSE;
            BiTree newTree = BuildArrayTree(values, 0, &allocationFailed);
            if (allocationFailed == TRUE) {
                printf("内存分配失败，原二叉树未修改\n");
            } else {
                tree = FreeBiTree(tree);
                tree = newTree;
                printf("二叉树创建成功\n");
            }
            break;
        }
        case 3:
            printf(BiTreeEmpty(tree) == TRUE ? "二叉树为空\n" : "二叉树不为空\n");
            break;
        case 4:
            printf("二叉树深度为：%d\n", BiTreeDepth(tree));
            break;
        case 5:
        case 6: {
            if (BiTreeEmpty(tree) == TRUE) {
                printf("二叉树为空，无法替换子树\n");
                break;
            }

            Status inputOk = OK;
            Status allocationFailed = FALSE;
            BiTree replacement = ReadPreorderTree(&inputOk, &allocationFailed);
            if (inputOk != OK) {
                FreeBiTree(replacement);
                printf(allocationFailed == TRUE ? "内存分配失败，原子树未修改\n"
                                                : "先序表达式无效，原子树未修改\n");
                if (allocationFailed != TRUE) {
                    tree = FreeBiTree(tree);
                    return 1;
                }
                break;
            }

            BiTree oldSubtree = operation == 5 ? ReplaceLeft(tree, replacement)
                                               : ReplaceRight(tree, replacement);
            FreeBiTree(oldSubtree);
            printf("子树替换成功\n");
            break;
        }
        case 7:
        case 8:
        case 9:
        case 10: {
            Status result = operation == 7 ? PreOrderTrav(tree, PrintValue)
                            : operation == 8 ? InOrderTrav(tree, PrintValue)
                            : operation == 9 ? PostOrderTrav(tree, PrintValue)
                                             : LevelOrderTrav(tree, PrintValue);
            if (result == OK) {
                printf("\n");
            } else {
                printf("遍历失败\n");
            }
            break;
        }
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
