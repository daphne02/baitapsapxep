
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

// 1. Sắp xếp đổi chỗ trực tiếp
void interchangeSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] > a[j]) {
                // Đổi chỗ a[i] và a[j]
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}

// 2. Sắp xếp chọn trực tiếp
void selectionSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[minIndex]) {
                minIndex = j;
            }
        }
        // Đổi chỗ phần tử nhỏ nhất với a[i]
        int temp = a[i];
        a[i] = a[minIndex];
        a[minIndex] = temp;
    }
}

// 3. Sắp xếp chèn trực tiếp
void insertionSort(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        // Dịch các phần tử lớn hơn key sang phải
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        // Chèn key vào đúng vị trí
        a[j + 1] = key;
    }
}

// 4. Sắp xếp nổi bọt
void bubbleSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (a[j] > a[j + 1]) {
                // Đổi chỗ a[j] và a[j+1]
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

int main() {
    int a[MAX_N] = {39, 8, 5, 1, 3, 6, 9, 12, 4, 7, 10};
    int n = 11;

    int b[MAX_N], c[MAX_N], d[MAX_N], e[MAX_N];

    // Sao chép mảng ban đầu cho các thuật toán
    for (int i = 0; i < n; i++) {
        b[i] = c[i] = d[i] = e[i] = a[i];
    }

    cout << "Mang ban dau: ";
    printArray(a, n);

    // Sắp xếp đổi chỗ trực tiếp
    interchangeSort(b, n);
    cout << "Sap xep doi cho truc tiep: ";
    printArray(b, n);

    // Sắp xếp chọn trực tiếp
    selectionSort(c, n);
    cout << "Sap xep chon truc tiep: ";
    printArray(c, n);

    // Sắp xếp chèn trực tiếp
    insertionSort(d, n);
    cout << "Sap xep chen truc tiep: ";
    printArray(d, n);

    // Sắp xếp nổi bọt
    bubbleSort(e, n);
    cout << "Sap xep noi bot: ";
    printArray(e, n);

    return 0;
}
