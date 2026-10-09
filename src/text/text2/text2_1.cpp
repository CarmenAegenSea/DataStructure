#include <stdio.h>

/**
 * text2_1.cpp
 * 上机作业2_1
 * 数制转换
 */

int main() {
	int number;
	int base;
	if (scanf("%d %d", &number, &base) != 2 || base < 2 || base > 16) {
		printf("输入错误：进制范围为 2 到 16\n");
		return 1;
	}

	const char digits[] = "0123456789ABCDEF";
	int value = number;

	char result[64];
	int count = 0;
	do {
		result[count++] = digits[value % base];
		value /= base;
	} while (value > 0);

	while (count > 0) printf("%c", result[--count]);

	return 0;
}
