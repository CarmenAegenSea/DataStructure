#include <stdio.h>
#include <stdlib.h>
#include "../../../include/Stack/Stack.h"

/**
 * text2.cpp
 * 上机作业2
 * 数制转换
 */

int main() {
    SqStack OPTR = InitStack();
    SqStack OPND = InitStack();

    if (!OPTR || !OPND) {
        printf("栈初始化失败\n");
        return 1;
    }

    printf("请输入表达式（以 # 结束）：");
    char ch;
    while ((ch = getchar()) != '#' && ch != EOF) {
        if (ch >= '0' && ch <= '9') {
            Push(OPND, ch);
        } else if (ch != '\n' && ch != '\r' && ch != ' ') {
            Push(OPTR, ch);
        }
    }

    return 0;
}