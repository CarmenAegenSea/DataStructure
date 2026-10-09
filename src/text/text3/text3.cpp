#include <stdio.h>
#include "Queue.h"

/**
 * text3.cpp
 * 上机作业3
 * 使用队列实现输出杨辉三角
 */

#define ROWS 13

/* 构建下一行 */
int BuildNextRow(LinkQueue current, LinkQueue next) {
    int previous;
    int value;
    ClearQueueL(next);
    if (QueueRmptyL(current)) return ERROR;

    previous = DeQueueL(current);
    if (previous == WARNING || EnQueueL(next, 1) != OK) return ERROR;

    while (!QueueRmptyL(current)) {
        value = DeQueueL(current);
        if (value == WARNING || EnQueueL(next, previous + value) != OK) return ERROR;
        previous = value;
    }
    return EnQueueL(next, 1);
}

int PrintValue(int value) {
    printf("%-4d", value);
    return OK;
}

/* 输出row行 */
void PrintRow(LinkQueue row, int level) {
    int i;
    for (i = 0; i < (ROWS - level) * 2; i++) printf(" ");
    QueueTrav(row, PrintValue);
    printf("\n");
}

int main() {
    LinkQueue current = InitQueueL();
    LinkQueue next = InitQueueL();
    LinkQueue temp;
    if (EnQueueL(current, 1) != OK) {
        FreeQueueL(current);
        FreeQueueL(next);
        return 1;
    }

    for (int level = 1; level <= ROWS; level++) {
        PrintRow(current, level);
        if (level < ROWS) {
            if (BuildNextRow(current, next) != OK) {
                FreeQueueL(current);
                FreeQueueL(next);
                return 1;
            }
            temp = current;
            current = next;
            next = temp;
        }
    }

    FreeQueueL(current);
    FreeQueueL(next);
    return 0;
}
