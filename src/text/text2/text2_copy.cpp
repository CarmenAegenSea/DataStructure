#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include "Stack/Stack.h"

/**
 * text2.cpp
 * 上机作业2
 * 使用栈实现计算器
 */

static int priority(int op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

static int apply_operator(SqStack numbers, SqStack operators) {
    long long result;
    int right;
    int left;
    int op;

    if (StackEmpty(numbers) || StackEmpty(operators)) {
        return ERROR;
    }

    right = Pop(numbers);
    left = Pop(numbers);
    op = Pop(operators);

    switch (op) {
        case '+':
            result = (long long)left + right;
            break;
        case '-':
            result = (long long)left - right;
            break;
        case '*':
            result = (long long)left * right;
            break;
        case '/':
            if (right == 0 || (left == INT_MIN && right == -1)) {
                return ERROR;
            }
            result = left / right;
            break;
        default:
            return ERROR;
    }

    if (result < INT_MIN || result > INT_MAX) {
        return ERROR;
    }
    return Push(numbers, (int)result) == OK ? OK : ERROR;
}

static int calculate(const char *expression, int *answer) {
    SqStack numbers = InitStack();
    SqStack operators = InitStack();
    const char *current = expression;
    int expect_number = TRUE;
    int valid = TRUE;

    if (!numbers || !operators) {
        FreeStack(&numbers);
        FreeStack(&operators);
        return ERROR;
    }

    while (*current && valid) {
        while (isspace((unsigned char)*current)) {
            current++;
        }
        if (!*current) {
            break;
        }

        if (expect_number) {
            if (*current == '(') {
                valid = Push(operators, *current) == OK;
                current++;
                continue;
            } else {
                char *end;
                long value;
                int sign = 1;

                if (*current == '+' || *current == '-') {
                    sign = *current == '-' ? -1 : 1;
                    current++;
                    while (isspace((unsigned char)*current)) {
                        current++;
                    }
                }
                if (!isdigit((unsigned char)*current)) {
                    valid = FALSE;
                    break;
                }

                errno = 0;
                value = strtol(current, &end, 10);
                if (errno == ERANGE || value > INT_MAX || value < INT_MIN) {
                    valid = FALSE;
                    break;
                }
                value *= sign;
                if (value < INT_MIN || value > INT_MAX) {
                    valid = FALSE;
                    break;
                }
                valid = Push(numbers, (int)value) == OK;
                current = end;
            }
            expect_number = FALSE;
        } else if (*current == ')') {
            while (valid && !StackEmpty(operators) && GetTop(operators) != '(') {
                valid = apply_operator(numbers, operators);
            }
            if (StackEmpty(operators)) {
                valid = FALSE;
            } else {
                Pop(operators);
                current++;
            }
        } else if (*current == '+' || *current == '-' ||
                   *current == '*' || *current == '/') {
            while (valid && !StackEmpty(operators) &&
                   GetTop(operators) != '(' &&
                   priority(GetTop(operators)) >= priority(*current)) {
                valid = apply_operator(numbers, operators);
            }
            if (valid) {
                valid = Push(operators, *current) == OK;
                current++;
                expect_number = TRUE;
            }
        } else {
            valid = FALSE;
        }
    }

    while (valid && !StackEmpty(operators)) {
        if (GetTop(operators) == '(') {
            valid = FALSE;
        } else {
            valid = apply_operator(numbers, operators);
        }
    }

    if (valid && expect_number) {
        valid = FALSE;
    }
    if (valid && StackLen(numbers) == 1) {
        *answer = Pop(numbers);
    } else {
        valid = FALSE;
    }

    FreeStack(&numbers);
    FreeStack(&operators);
    return valid ? OK : ERROR;
}

int main() {
    char expression[1024];
    int answer;

    while (fgets(expression, sizeof(expression), stdin)) {
        if (calculate(expression, &answer)) {
            printf("%d\n", answer);
        } else {
            printf("表达式错误\n");
        }
    }
    return 0;
}