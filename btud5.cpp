#include <iostream>
#include <algorithm>

using namespace std;

const int MAX = 100; // Giới hạn kích thước ma trận

int main() {
    int m, n;
    int a[MAX][MAX]; // Ma trận
    int sum[MAX];    // Mảng lưu tổng của từng dòng

    // Nhập kích thước ma trận
    cout << "Nhập số dòng m và số cột n: ";
    cin >> m >> n;

    // Nhập các phần tử của ma trận
    cout << "Nhập ma trận:\n";
    for (int i = 0; i < m; i++) {
        sum[i] = 0; // Khởi tạo tổng của từng dòng
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
            sum[i] += a[i][j]; // Tính tổng của dòng i
        }
    }

    // Tìm dòng có tổng lớn nhất
    int maxSum = sum[0], maxRowIndex = 0;
    for (int i = 1; i < m; i++) {
        if (sum[i] > maxSum) {
            maxSum = sum[i];
            maxRowIndex = i;
        }
    }
    cout << "Dòng có tổng lớn nhất là dòng " << maxRowIndex + 1 << " với tổng = " << maxSum << endl;

    // Sắp xếp các dòng theo tổng giảm dần
    for (int i = 0; i < m - 1; i++) {
        for (int j = i + 1; j < m; j++) {
            if (sum[i] < sum[j]) {
                // Đổi vị trí tổng của dòng
                swap(sum[i], sum[j]);
                // Đổi vị trí dòng trong ma trận
                for (int k = 0; k < n; k++) {
                    swap(a[i][k], a[j][k]);
                }
            }
        }
    }

    // In ma trận sau khi sắp xếp
    cout << "Ma trận sau khi sắp xếp các dòng theo tổng giảm dần:\n";
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
