#include <stdio.h>
#include <stdlib.h>
#include "Stack/Stack.h"

#define LAYERSIZE 13

int main() {
    SqStack last = InitStack();
    SqStack next = InitStack();
    if (!last || !next) {
        FreeStack(&last);
        FreeStack(&next);
        return WARNING;
    }

    Push(last, 1);
    Push(next, 1);
    Push(next, 1);

    for (int i = 0; i < LAYERSIZE; i++) {

    }

    return 0;
}
