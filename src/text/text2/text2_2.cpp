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

// 对算术表达式 Expr 求值的算符优先算法
float CalculateExpr(char * Expr) {
    std::vector<char> operators(1, '#');
    std::vector<float> operands;
    char *cursor = Expr;

    while (*cursor != '\0') {
        while (isspace(static_cast<unsigned char>(*cursor))) cursor++;
        if (isdigit(static_cast<unsigned char>(*cursor)) || *cursor == '.') {
            char *end = nullptr;
            float value = strtof(cursor, &end);
            if (end == cursor) return 0.0f;
            operands.push_back(value);
            cursor = end;
            continue;
        }

        char current = *cursor;
        if (!InOPset(current)) return 0.0f;
        char relation = precede(operators.back(), current);
        if (relation == '<') {
            operators.push_back(current);
            if (current != '#') cursor++;
        } else if (relation == '=') {
            operators.pop_back();
            if (current != '#') cursor++;
            else break;
        } else if (relation == '>') {
            if (operands.size() < 2) return 0.0f;
            char op = operators.back();
            operators.pop_back();
            float right = operands.back();
            operands.pop_back();
            float left = operands.back();
            operands.pop_back();
            operands.push_back(Operate(left, op, right));
        } else {
            return 0.0f;
        }
    }

    return operands.empty() ? 0.0f : operands.back();
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

    printf("%g\n", CalculateExpr(expression));
    return 0;
}