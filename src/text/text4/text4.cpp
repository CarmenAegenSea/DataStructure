#include <stdio.h>
#include <stdlib.h>
/**
 * text4.cpp
 * 上机作业4
 * 查找鞍点
 */

int main(void) {
    int row, col;
    printf("请输入矩阵的行数和列数：");
    if (scanf("%d %d", &row, &col) != 2 || row <= 0 || col <= 0) {
        printf("行数和列数必须是正整数。\n");
        return 1;
    }

    int *minRow = (int *)malloc(sizeof(int) * row);
    int *maxCol = (int *)malloc(sizeof(int) * col);
    int **matrix = (int **)malloc(sizeof(int *) * row);
    if (minRow == NULL || maxCol == NULL || matrix == NULL) {
        printf("内存分配失败。\n");
        free(minRow);
        free(maxCol);
        free(matrix);
        return 1;
    }

    for (int i = 0; i < row; i++) {
        matrix[i] = (int *)malloc(col * sizeof(int));
        if (matrix[i] == NULL) {
            for (int k = 0; k < i; k++) {
                free(matrix[k]);
            }
            free(matrix);
            free(minRow);
            free(maxCol);
            return 1;
        }
    }

    printf("请输入矩阵的元素(行优先)：\n");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                printf("矩阵元素输入无效。\n");
                for (int k = 0; k < row; k++) {
                    free(matrix[k]);
                }
                free(matrix);
                free(minRow);
                free(maxCol);
                return 1;
            }
        }
    }

    for (int i = 0; i < row; i++) {
        minRow[i] = matrix[i][0];
        for (int j = 1; j < col; j++) {
            if (matrix[i][j] < minRow[i]) {
                minRow[i] = matrix[i][j];
            }
        }
    }

    for (int j = 0; j < col; j++) {
        maxCol[j] = matrix[0][j];
        for (int i = 1; i < row; i++) {
            if (matrix[i][j] > maxCol[j]) {
                maxCol[j] = matrix[i][j];
            }
        }
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (matrix[i][j] == minRow[i] && matrix[i][j] == maxCol[j]) {
                printf("(%d)", matrix[i][j]);
            } else {
                printf("%d", matrix[i][j]);
            }
            if (j < col - 1) {
                printf("\t");
            }
        }
        printf("\n");
    }

    for (int i = 0; i < row; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(minRow);
    free(maxCol);

    return 0;
}