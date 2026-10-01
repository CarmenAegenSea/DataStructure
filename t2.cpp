#include <stdlib.h>
#include <stdio.h>

int main() {
    int n, m, seed;
    scanf("%d %d %d", &n, &m, &seed);
    int* map = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        map[i] = (int*)malloc(sizeof(int) * m);
    }

    return 0;
}
