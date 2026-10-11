#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <vector>
#include "Def.h"

#define OPSetSize 7

/**
 * text2_2.cpp
 * 上机作业2_2
 * 算术表达式求值
 */

char OPSet[OPSetSize] = {'+', '-', '*', '/', '(', ')', '#'};

// 算符之间的优先关系表
char Prior[7][7] = {
    {'>', '>', '<', '<', '<', '>', '>'},
    {'>', '>', '<', '<', '<', '>', '>'},
    {'>', '>', '>', '>', '<', '>', '>'},
    {'>', '>', '>', '>', '<', '>', '>'},
    {'<', '<', '<', '<', '<', '=', ' '},
    {'>', '>', '>', '>', ' ', '>', '>'},
    {'<', '<', '<', '<', '<', ' ', '='}
};

// 执行四则运算，并返回结果
float Operate(float a, char theta, float b) {
    switch (theta) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default : return 0.0f;
    }
}

/* 检测 c 是否为算符 */
bool InOPset(char c) {
    for (int i = 0; i < OPSetSize; i++) if (c == OPSet[i]) return TRUE;
    return FALSE;
}

/* 查算符 op 的序号 */
int OpOrd(char op) {
    for (int i = 0; i < OPSetSize; i++) if (op == OPSet[i]) return i;
    return 0;
}

/* 查两个算符的优先关系 */
char precede(char Aop, char Bop) {
    return Prior[OpOrd(Aop)][OpOrd(Bop)];
}

// 将算术表达式 Expr 转换为后缀表达式
int InfixToPostfix(char *Expr) {
    std::vector<char> operators(1, '#');
    char *cursor = Expr;
    int hasOutput = 0;

    while (*cursor != '\0') {
        while (isspace(static_cast<unsigned char>(*cursor))) cursor++;
        if (isdigit(static_cast<unsigned char>(*cursor)) || *cursor == '.') {
            char *end = nullptr;
            strtof(cursor, &end);
            if (end == cursor) return 0;
            if (hasOutput) putchar(' ');
            printf("%.*s", (int)(end - cursor), cursor);
            hasOutput = 1;
            cursor = end;
            continue;
        }

        char current = *cursor;
        if (!InOPset(current)) return 0;
        char relation = precede(operators.back(), current);
        if (relation == '<') {
            operators.push_back(current);
            if (current != '#') cursor++;
        } else if (relation == '=') {
            operators.pop_back();
            if (current != '#') cursor++;
            else break;
        } else if (relation == '>') {
            char op = operators.back();
            operators.pop_back();
            if (op != '(' && op != '#') {
                if (hasOutput) putchar(' ');
                putchar(op);
                hasOutput = 1;
            }
        } else {
            return 0;
        }
    }

    return 1;
}

int main() {
    char expression[512];
    if (!fgets(expression, sizeof(expression), stdin)) return 1;

    size_t length = strlen(expression);
    while (length > 0 && isspace(static_cast<unsigned char>(expression[length - 1]))) {
        expression[--length] = '\0';
    }
    if (length == 0) {
        printf("表达式不能为空\n");
        return 1;
    }
    if (expression[length - 1] != '#') {
        expression[length++] = '#';
        expression[length] = '\0';
    }

    if (!InfixToPostfix(expression)) {
        printf("表达式格式无效\n");
        return 1;
    }
    putchar('\n');
    return 0;
}