#include <stdio.h>
#include "Stack.h"

/**
 * text3.cpp
 * 上机作业3
 * 使用栈实现输出杨辉三角
 */

#define ROWS 13

/* 构建下一行 */
int BuildNextRow(SqStack current, SqStack next) {
    if (!Push(next, 1)) return ERROR;

    while (!StackEmpty(current)) {
        int value = Pop(current);
        if (!Push(next, value + GetTop(current))) return ERROR;
    }
    return OK;
}

/* 输出row行 */
void PrintRow(SqStack row, int level) {
    for (int i = 0; i < (ROWS - level) * 2; i++) printf(" ");
    for (int i = 0; i < StackLen(row); i++) printf("%-4d", row->elem[i]);
    printf("\n");
}

int main() {
    SqStack current = InitStack();
    SqStack next = InitStack();
    if (!current || !next) {
        FreeStack(&current);
        FreeStack(&next);
        return ERROR;
    }

    if (!Push(current, 1)) {
        FreeStack(&current);
        FreeStack(&next);
        return ERROR;
    }

    for (int level = 1; level <= ROWS; level++) {
        PrintRow(current, level);
        if (level < ROWS) {
            if (!BuildNextRow(current, next)) {
                FreeStack(&current);
                FreeStack(&next);
                return ERROR;
            }
            SqStack temp = current;
            current = next;
            next = temp;
        }
    }

    FreeStack(&current);
    FreeStack(&next);
    return 0;
}
