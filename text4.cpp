#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// 寻找矩阵中的鞍点：第i行的最小值且第j列的最大值
// 输出所有满足条件的元素的坐标（行号、列号，从1开始）
void findSaddlePoints(const vector<vector<int>>& matrix) {
    int rows = matrix.size();
    if (rows == 0) return;
    int cols = matrix[0].size();
    if (cols == 0) return;

    // 找每行的最小值
    vector<int> rowMin(rows);
    for (int i = 0; i < rows; ++i) {
        rowMin[i] = matrix[i][0];
        for (int j = 1; j < cols; ++j) {
            if (matrix[i][j] < rowMin[i]) {
                rowMin[i] = matrix[i][j];
            }
        }
    }

    // 找每列的最大值
    vector<int> colMax(cols);
    for (int j = 0; j < cols; ++j) {
        colMax[j] = matrix[0][j];
        for (int i = 1; i < rows; ++i) {
            if (matrix[i][j] > colMax[j]) {
                colMax[j] = matrix[i][j];
            }
        }
    }

    // 找鞍点
    bool found = false;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j] == rowMin[i] && matrix[i][j] == colMax[j]) {
                cout << "鞍点: a[" << i+1 << "," << j+1 << "] = " << matrix[i][j] << endl;
                found = true;
            }
        }
    }

    if (!found) {
        cout << "该矩阵不存在满足条件的鞍点。" << endl;
    }
}

int main() {
    // 示例：手动输入矩阵
    int rows, cols;
    cout << "请输入矩阵的行数和列数: ";
    cin >> rows >> cols;

    vector<vector<int>> matrix(rows, vector<int>(cols));
    cout << "请输入矩阵元素：" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cin >> matrix[i][j];
        }
    }

    cout << "原矩阵：" << endl;
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << "\t";
        }
        cout << endl;
    }

    cout << "\n鞍点结果：" << endl;
    findSaddlePoints(matrix);

    return 0;
}
