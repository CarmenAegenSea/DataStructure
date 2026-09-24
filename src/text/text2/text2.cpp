#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../../../include/Stack/Stack.h"

/**
 * text2.cpp
 * 上机作业2
 * 基于栈的表达式计算器
 */

/* 判断字符是否为运算符 */
int IsOperator(int ch) {
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')') {
        return TRUE;
    }
    return FALSE;
}

/* 返回运算符优先级（栈内优先级） */
int Precedence(int op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '(':
            return 0;
        default:
            return -1;
    }
}

/* 执行一次二元运算，结果压入操作数栈 */
int CalcOnce(SqStack opnd, SqStack optr) {
    if (StackLen(opnd) < 2 || StackLen(optr) < 1) {
        return ERROR;
    }

    int b = Pop(opnd);
    int a = Pop(opnd);
    int op = Pop(optr);
    int res;

    switch (op) {
        case '+': res = a + b; break;
        case '-': res = a - b; break;
        case '*': res = a * b; break;
        case '/':
            if (b == 0) {
                printf("错误：除数为 0\n");
                return ERROR;
            }
            res = a / b;
            break;
        default:
            return ERROR;
    }

    if (!Push(opnd, res)) {
        return ERROR;
    }
    return OK;
}

/* 对表达式字符串求值，成功返回 OK，结果存入 *result */
int Evaluate(const char *expr, int *result) {
    SqStack opnd = InitStack();   /* 操作数栈 */
    SqStack optr = InitStack();   /* 运算符栈 */

    if (!opnd || !optr) {
        printf("栈初始化失败\n");
        FreeStack(&opnd);
        FreeStack(&optr);
        return ERROR;
    }

    int i = 0;
    while (expr[i] != '\0') {
        if (isspace(expr[i])) {
            i++;
            continue;
        }

        /* 数字：读取多位整数 */
        if (isdigit(expr[i])) {
            int num = 0;
            while (isdigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            if (!Push(opnd, num)) {
                printf("入栈失败\n");
                FreeStack(&opnd);
                FreeStack(&optr);
                return ERROR;
            }
            continue;
        }

        /* 运算符 */
        if (IsOperator(expr[i])) {
            int ch = expr[i];
            if (ch == '(') {
                Push(optr, ch);
            } else if (ch == ')') {
                while (!StackEmpty(optr) && GetTop(optr) != '(') {
                    if (!CalcOnce(opnd, optr)) {
                        FreeStack(&opnd);
                        FreeStack(&optr);
                        return ERROR;
                    }
                }
                if (StackEmpty(optr)) {
                    printf("错误：括号不匹配\n");
                    FreeStack(&opnd);
                    FreeStack(&optr);
                    return ERROR;
                }
                Pop(optr);   /* 弹出 '(' */
            } else {
                /* 处理负号：表达式开头或 '(' 后的 '-' 视为负号 */
                if (ch == '-' && (i == 0 || expr[i - 1] == '(')) {
                    Push(opnd, 0);
                }
                while (!StackEmpty(optr) &&
                       Precedence(GetTop(optr)) >= Precedence(ch)) {
                    if (!CalcOnce(opnd, optr)) {
                        FreeStack(&opnd);
                        FreeStack(&optr);
                        return ERROR;
                    }
                }
                Push(optr, ch);
            }
            i++;
            continue;
        }

        printf("错误：非法字符 '%c'\n", expr[i]);
        FreeStack(&opnd);
        FreeStack(&optr);
        return ERROR;
    }

    /* 处理栈中剩余运算符 */
    while (!StackEmpty(optr)) {
        if (GetTop(optr) == '(') {
            printf("错误：括号不匹配\n");
            FreeStack(&opnd);
            FreeStack(&optr);
            return ERROR;
        }
        if (!CalcOnce(opnd, optr)) {
            FreeStack(&opnd);
            FreeStack(&optr);
            return ERROR;
        }
    }

    if (StackLen(opnd) != 1) {
        printf("错误：表达式不合法\n");
        FreeStack(&opnd);
        FreeStack(&optr);
        return ERROR;
    }

    *result = Pop(opnd);
    FreeStack(&opnd);
    FreeStack(&optr);
    return OK;
}

int main() {
    char expr[256];

    printf("请输入表达式（支持 + - * / 和括号）：");
    if (!fgets(expr, sizeof(expr), stdin)) {
        printf("输入读取失败\n");
        return 1;
    }

    /* 去除末尾换行 */
    int len = 0;
    while (expr[len] != '\0') {
        len++;
    }
    if (len > 0 && expr[len - 1] == '\n') {
        expr[len - 1] = '\0';
    }

    int result;
    if (Evaluate(expr, &result)) {
        printf("[Result]:%d\n", result);
    } else {
        printf("[Result]:计算失败\n");
        return 1;
    }

    return 0;
}
