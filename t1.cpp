#include <stdio.h>

int main() {
    int x, y;
    scanf("%d", &x);
    scanf("%d", &y);

    int sum = x + y;
    printf("%d", (sum % 10) + ((sum % 100) - (sum % 10))/10 + (sum - (sum % 100))/100);
    return 0;
}
