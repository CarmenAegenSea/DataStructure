#include <stdio.h>
#include <stdlib.h>
#include "Stack/Stack.h"

/**
 * text3.cpp
 * 上机作业3
 * 使用栈实现输出杨辉三角（层数 13）
 *
 * 算法思想（利用栈的后进先出特性）：
 *   1. 杨辉三角第 n 行恰好有 n 个系数，且第 n+1 行的第 k 个数
 *      = 第 n 行第 k-1 个数 + 第 n 行第 k 个数（越界的按 0 计）。
 *   2. 栈中保存一行的系数，约定 elem[0]（最左的 1）压在栈顶，
 *      即从左到右依次压栈。
 *   3. 由第 n 行推第 n+1 行：先压入行首的 1；然后从栈顶依次弹出
 *      系数 v，此时栈顶正好是它的右邻 r，于是压入 v + r。
 *      弹完第 n 行就得到第 n+1 行（此时它保存在另一个栈里）。
 *   4. 每输出完一行就把它弹空，正好留给下一行使用；
 *      求下一行时先输出本行（只读不弹），再在另一个栈中生成下一行，
 *      最后交换两个栈。
 */

#define TRIANGLE_ROWS 13   /* 杨辉三角的层数 */

/* 由 cur 行推出下一行，结果放在 next 中（next 需为空栈，cur 会被弹空） */
int BuildNextRow(SqStack cur, SqStack next) {
    Push(next, 1);                       /* 行首的 1 */

    while (!StackEmpty(cur)) {
        int v = Pop(cur);                /* 当前系数 */
        int r = GetTop(cur);             /* 右邻系数（cur 已弹空时为 0） */
        if (!Push(next, v + r)) {
            return ERROR;
        }
    }
    return OK;
}

/* 输出一行：level 从 1 开始，只读取不弹出，保持 cur 供求下一行使用 */
void PrintRow(SqStack cur, int level) {
    for (int i = 0; i < (TRIANGLE_ROWS - level) * 2; i++) {
        printf(" ");
    }
    for (int i = 0; i < StackLen(cur); i++) {
        printf("%-4d", cur->elem[i]);
    }
    printf("\n");
}

int main() {
    SqStack cur = InitStack();    /* 当前行，栈顶为最左元素 */
    SqStack next = InitStack();   /* 下一行 */
    SqStack tmp;

    if (!cur || !next) {
        printf("栈初始化失败\n");
        FreeStack(&cur);
        FreeStack(&next);
        return ERROR;
    }

    Push(cur, 1);                 /* 第 1 行：1 */

    for (int level = 1; level <= TRIANGLE_ROWS; level++) {
        PrintRow(cur, level);     /* 输出第 level 行（只读不弹） */

        if (level == TRIANGLE_ROWS) {
            break;                /* 最后一行不用再算下一行 */
        }

        if (!BuildNextRow(cur, next)) {
            printf("入栈失败\n");
            FreeStack(&cur);
            FreeStack(&next);
            return ERROR;
        }

        tmp = cur;                /* 换行：next 中是新的一行，cur 已被弹空 */
        cur = next;
        next = tmp;
    }

    FreeStack(&cur);
    FreeStack(&next);
    return OK;
}
