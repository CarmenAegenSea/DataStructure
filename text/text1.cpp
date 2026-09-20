#include <stdio.h>
#include <stdlib.h>
#include "List.h"

int main() {
    SqList textList = InitList();
    ListInsert(textList, 1, 3);
    printf("%d", ListDelete(textList, 1));
    printf("111");
    return 0;
}