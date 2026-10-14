#include <iostream>
#include <cstdlib>
#include <cmath>
#include "GLinkList.h"

GLinkList* InitGLinkList() {
    GLinkList *L = (GLinkList*)malloc(sizeof(struct GLinkList));
    if (!L) {
        std::cerr << "Memory allocation failed!" << std::endl;
        exit(EXIT_FAILURE);
    }
    (*L)->tag = LIST;
    (*L)->list = NULL;
    (*L)->next = NULL;
    return L;
}

GLinkList NewGLinkList(SqString *S) {
    GLinkList L = InitGLinkList();
}
