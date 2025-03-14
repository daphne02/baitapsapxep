#include <iostream>
#include <algorithm>

using namespace std;

// Định nghĩa cấu trúc dữ liệu
struct Term {
    double coefficient; // Hệ số
    int exponent;       // Bậc
};

// Hàm so sánh để sắp xếp theo bậc tăng dần
bool compareTerms(const Term &a, const Term &b) {
    return a.exponent < b.exponent;
}

// Hàm hiển thị danh sách các số hạng
void printTerms(const Term terms[], int size) {
    for (int i = 0; i < size; i++) {
        cout << terms[i].coefficient << "x^" << terms[i].exponent;
        if (i < size - 1) cout << " + ";
    }
    cout << endl;
}

int main() {
    // Khai báo mảng số hạng
    Term terms[] = {
        {3.2, 5}, {1.5, 2}, {4.1, 3}, {2.0, 4}, {5.0, 0}
    };

    int size = sizeof(terms) / sizeof(terms[0]);  // Xác định số phần tử trong mảng

    cout << "Dãy thức ban đầu:" << endl;
    printTerms(terms, size);

    // Sắp xếp dãy thức theo bậc tăng dần
    sort(terms, terms + size, compareTerms);

    cout << "Dãy thức sau khi sắp xếp:" << endl;
    printTerms(terms, size);

    return 0;
}
