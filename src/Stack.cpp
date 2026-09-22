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

    S->top = 0;
    S->size = STACK_INIT_SIZE;
    S->inc = STACK_INIT_SIZE;
    return S;
}

void FreeStack(SqStack *S) {
    if (S || *S) {
        free((*S)->elem);
        (*S)->elem = NULL;
        free(*S);
        *S = NULL;
    }
}

void ClearStack(SqStack *S) {
    if (S) {
        (*S)->top = 0;
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
    if (!S) {
        return WARNING;
    }
    return S->elem[S->top - 1];
}

int Push(SqStack S, int e) {
    if (!S) {
        return WARNING;
    }

    if (S->top >= S->size) {
        int newSize = S->size + S->inc;
        int* newElem = (int*)malloc(sizeof(int) * newSize);
        if (!newSize) {
            return ERROR;
        }

        for (int i = 0; i < S->top; i++) {
            newElem[i] = S->elem[i];
        }

        S->size = newSize;
        free(S->elem);
        S->elem = newElem;
    }
    S->elem[S->top++] = e;
    return OK;
}
