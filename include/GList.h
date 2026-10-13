#ifndef GLIST_H
#define GLIST_H

#include "Def.h"

typedef enum {ATOM, LIST} ElemTag; /* 结点类型标志 */
typedef struct GNode {
    ElemTag tag;
    union {
        ElemType atom;
        GList list;
    } data;
} *GList;

#endif
