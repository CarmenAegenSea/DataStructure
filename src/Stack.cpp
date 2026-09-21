#include "Stack.h"
#include <stdlib.h>

SqStack InitStack() {
    SqStack S = (SqStack)malloc(sizeof(SqStackNode));
    if (!S) {
        return NULL;
    }

    S->elem = (int*)malloc(STACK_INIT_SIZE * sizeof(int));
    if (!S->elem) {
        free(S);
        return NULL;
    }

    S->top  = 0;
    S->size = STACK_INIT_SIZE;
    S->inc  = STACK_INC;
    return S;
}

void FreeStack(SqStack *S) {
    if (S && *S) {
        if ((*S)->elem) {
            free((*S)->elem);
            (*S)->elem = NULL;
        }
        free(*S);
        *S = NULL;
    }
}

void ClearStack(SqStack S) {
    if (S) {
        S->top = 0;
    }
}

int StackEmpty(SqStack S) {
    if (!S) {
        return WARNING;
    }
    return S->top == 0 ? TRUE : FALSE;
}

int StackLen(SqStack S) {
    if (!S) {
        return WARNING;
    }
    return S->top;
}

int GetTop(SqStack S) {
    if (!S || S->top == 0) {
        return 0;
    }
    return S->elem[S->top - 1];
}

int Push(SqStack S, int e) {
    if (!S) {
        return ERROR;
    }

    /* 容量不足时扩容 */
    if (S->top >= S->size) {
        int newSize = S->size + (S->inc > 0 ? S->inc : STACK_INC);
        int *newElem = (int*)malloc(newSize * sizeof(int));
        if (!newElem) {
            return ERROR;
        }

        for (int i = 0; i < S->top; i++) {
            newElem[i] = S->elem[i];
        }

        free(S->elem);
        S->elem = newElem;
        S->size = newSize;
    }

    S->elem[S->top++] = e;
    return OK;
}

int Pop(SqStack S) {
    if (!S || S->top == 0) {
        return 0;
    }
    return S->elem[--S->top];
}

void StackTraverse(SqStack S, int (*F)(int)) {
    if (!S || !F) {
        return;
    }

    /* 自栈底到栈顶遍历 */
    for (int i = 0; i < S->top; i++) {
        (void)F(S->elem[i]);
    }
}
