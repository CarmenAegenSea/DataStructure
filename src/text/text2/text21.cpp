#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "Stack.h"

#define POSTFIX_SIZE 512

int Precedence(int op) {
    switch (op) {
        case '~': return 3;
        case '*':
        case '/': return 2;
        case '+':
        case '-': return 1;
        default: return 0;
    }
}

int AppendToken(char *postfix, int *length, const char *token, int tokenLength) {
    if (*length + tokenLength + 1 >= POSTFIX_SIZE) return ERROR;
    memcpy(postfix + *length, token, tokenLength);
    *length += tokenLength;
    postfix[(*length)++] = ' ';
    postfix[*length] = '\0';
    return OK;
}

int ToPostfix(const char *expr, char *postfix) {
    SqStack operators = InitStack();
    int i = 0, length = 0, expectOperand = 1;
    int status = ERROR;
    postfix[0] = '\0';

    if (!operators) return ERROR;

    while (expr[i] != '\0') {
        if (isspace((unsigned char)expr[i])) {
            i++;
            continue;
        }

        if (isdigit((unsigned char)expr[i])) {
            int start = i;
            if (!expectOperand) goto cleanup;
            while (isdigit((unsigned char)expr[i])) i++;
            if (!AppendToken(postfix, &length, expr + start, i - start)) goto cleanup;
            expectOperand = 0;
            continue;
        }

        int ch = expr[i++];
        if (ch == '(') {
            if (!expectOperand || !Push(operators, ch)) goto cleanup;
        } else if (ch == ')') {
            if (expectOperand) goto cleanup;
            while (!StackEmpty(operators) && GetTop(operators) != '(') {
                char op = (char)Pop(operators);
                if (!AppendToken(postfix, &length, &op, 1)) goto cleanup;
            }
            if (StackEmpty(operators)) goto cleanup;
            Pop(operators);
            if (!StackEmpty(operators) && GetTop(operators) == '~') {
                char op = (char)Pop(operators);
                if (!AppendToken(postfix, &length, &op, 1)) goto cleanup;
            }
            expectOperand = 0;
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            if (expectOperand) {
                if (ch != '-') goto cleanup;
                if (!Push(operators, '~')) goto cleanup;
                continue;
            }
            while (!StackEmpty(operators) && GetTop(operators) != '(' &&
                   Precedence(GetTop(operators)) >= Precedence(ch)) {
                char op = (char)Pop(operators);
                if (!AppendToken(postfix, &length, &op, 1)) goto cleanup;
            }
            if (!Push(operators, ch)) goto cleanup;
            expectOperand = 1;
        } else {
            goto cleanup;
        }
    }

    if (expectOperand) goto cleanup;
    while (!StackEmpty(operators)) {
        if (GetTop(operators) == '(') goto cleanup;
        char op = (char)Pop(operators);
        if (!AppendToken(postfix, &length, &op, 1)) goto cleanup;
    }
    status = OK;

cleanup:
    FreeStack(&operators);
    return status;
}

int EvaluatePostfix(const char *postfix, int *result) {
    SqStack values = InitStack();
    int i = 0, status = ERROR;
    if (!values) return ERROR;

    while (postfix[i] != '\0') {
        while (isspace((unsigned char)postfix[i])) i++;
        if (postfix[i] == '\0') break;

        if (isdigit((unsigned char)postfix[i])) {
            int number = 0;
            while (isdigit((unsigned char)postfix[i])) {
                number = number * 10 + (postfix[i++] - '0');
            }
            if (!Push(values, number)) goto cleanup;
            continue;
        }

        int op = postfix[i++];
        if (op == '~') {
            if (StackLen(values) < 1) goto cleanup;
            if (!Push(values, -Pop(values))) goto cleanup;
            continue;
        }
        if (StackLen(values) < 2) goto cleanup;

        int right = Pop(values);
        int left = Pop(values);
        int value;
        switch (op) {
            case '+': value = left + right; break;
            case '-': value = left - right; break;
            case '*': value = left * right; break;
            case '/':
                if (right == 0) {
                    printf("错误：除数为 0\n");
                    goto cleanup;
                }
                value = left / right;
                break;
            default: goto cleanup;
        }
        if (!Push(values, value)) goto cleanup;
    }

    if (StackLen(values) != 1) goto cleanup;
    *result = Pop(values);
    status = OK;

cleanup:
    FreeStack(&values);
    return status;
}

int main() {
    char expr[256];
    char postfix[POSTFIX_SIZE];
    int result;

    printf("请输入中缀表达式：");
    if (!fgets(expr, sizeof(expr), stdin)) {
        printf("输入读取失败\n");
        return 1;
    }

    if (!ToPostfix(expr, postfix)) {
        printf("错误：表达式不合法\n");
        return 1;
    }

    printf("后缀表达式：%s\n", postfix);
    if (!EvaluatePostfix(postfix, &result)) {
        printf("表达式计算失败\n");
        return 1;
    }
    printf("[Result]:%d\n", result);
    return 0;
}
