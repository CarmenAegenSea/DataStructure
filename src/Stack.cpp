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