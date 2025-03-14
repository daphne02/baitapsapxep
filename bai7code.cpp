
#include <iostream>

using namespace std;

const int MAX_N = 100;

// Hàm in mảng
void printArray(int a[], int n) {
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

// Hàm sắp xếp chẵn lên đầu, lẻ xuống cuối
void sortEvenOdd(int a[], int n) {
    int left = 0, right = 0;

    while (right < n) {
        if (a[right] % 2 == 0) {
            // Đổi chỗ số chẵn về vị trí `left`
            int temp = a[left];
            a[left] = a[right];
            a[right] = temp;
            left++;
        }
        right++;
    }
}

int main() {
    int a[MAX_N] = {1, 2, 4, 5, 3, 8, 6, 9, 12, 7, 10};
    int n = 11;

    cout << "Mang ban dau: ";
    printArray(a, n);

    // Sắp xếp chẵn lên đầu, lẻ xuống cuối
    sortEvenOdd(a, n);

    cout << "Mang sau khi sap xep: ";
    printArray(a, n);

    return 0;
}
