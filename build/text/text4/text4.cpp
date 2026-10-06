#include <stdio.h>
#include <stdlib.h>
#include "Def.h"

int main() {
    int rows, cols;
    printf("请输入矩阵的行数和列数: ");
    scanf("%d %d", &rows, &cols);

    /* 储存可能的答案 */
    int* rowMin = (int*)malloc(rows * sizeof(int));
    int* colMax = (int*)malloc(cols * sizeof(int));
    if (rowMin == NULL || colMax == NULL) {
        return WARNING;
    }

    for (int i = 0; i < rows; i++) {
        int* timeCol = (int*)malloc(cols * sizeof(int));    
        for (int j = 0; j < cols; j++) {
            printf("请输入矩阵元素 a[%d][%d]: ", i + 1, j + 1);
            int t;
            scanf("%d", &t);
            timeCol[j] = t;
            if (j == 0 || t < rowMin[i]) {
                rowMin[i] = t;
            }
        }
        for (int j = 0; j < cols; j++) {
            if (i == 0 || timeCol[j] > colMax[j]) {
                colMax[j] = timeCol[j];
            }
        }
        free(timeCol);
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (rowMin[i] == colMax[j]) {
                printf("鞍点为: %d\n", rowMin[i]);
                free(rowMin);
                free(colMax);
                return 0;
            }
        }
    }

    free(rowMin);
    free(colMax);
    return 0;
}
