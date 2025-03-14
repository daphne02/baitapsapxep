#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 100;

// Hàm kiểm tra số nguyên tố
// Kiểm tra nếu x < 2 thì không phải số nguyên tố
bool isPrime(int x) {
    if (x < 2) return false;
    for (int i = 2; i < x; i++)
        if (x % i == 0) // Nếu x chia hết cho i thì không phải số nguyên tố
          return false;
    return true; // Nếu không chia hết cho số nào từ 2 đến x-1 thì là số nguyên tố
}

// Hàm tính tổng các chữ số của một số nguyên
// Ví dụ: 123 -> 1 + 2 + 3 = 6
int sumOfDigits(int x) {
    x = abs(x); // Lấy giá trị tuyệt đối để xử lý số âm
    int sum = 0;
    while (x > 0) {
        sum += x % 10; // Cộng chữ số cuối cùng vào tổng
        x /= 10; // Loại bỏ chữ số cuối cùng
    }
    return sum;
}

// Hàm tìm vị trí của k phần tử lớn nhất
// Sắp xếp mảng giảm dần và lấy k phần tử đầu tiên
void findTopKElements(int a[], int n, int k, int result[]) {
    for (int i=0; i<n; i++)
      for (int j=i+1; j<n; j++)
        if (a[i] < a[j])
          swap(a[i], a[j]);
    for (int i = 0; i < k; i++) {
        result[i] = a[i]; // Lưu vị trí của k phần tử lớn nhất
    }
}

// Hàm so sánh theo tổng chữ số
// Sắp xếp mảng theo tổng các chữ số của từng phần tử
bool compareByDigitSum(int a, int b) {
    return sumOfDigits(a) < sumOfDigits(b);
}

// Hàm sắp xếp theo tổng chữ số
void SortDigital(int a[], int n, int result[]) {
    for (int i=0; i<n; i++)
      for (int j=i+1; j<n; j++)
        if (compareByDigitSum(a[i], a[j]))
          swap(a[i], a[j]); // Đổi chỗ nếu tổng chữ số của a[i] nhỏ hơn a[j]
    for (int i = 0; i < n; i++) {
        result[i] = a[i]; // Lưu kết quả vào mảng kết quả
    }
}

// Hàm xóa các số nguyên tố
// Giữ lại các phần tử không phải số nguyên tố
int removePrimes(int arr[], int n) {
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (!isPrime(arr[i])) { // Nếu không phải số nguyên tố thì giữ lại
            arr[j++] = arr[i];
        }
    }
    return j; // Trả về kích thước mới của mảng
}

int main() {
    int a[MAXN] = {12, 5, 23, 7, 45, 29, 11, 101};
    int n = 8;
    int k = 3;

    // (a) Tìm vị trí k phần tử lớn nhất
    int topK[MAXN];
    findTopKElements(a, n, k, topK);
    cout << "Vị trí của " << k << " phần tử lớn nhất: ";
    for (int i = 0; i < k; i++) cout << topK[i] << " ";
    cout << endl;

    // (b) Sắp xếp theo tổng các chữ số
    int s[MAXN];
    SortDigital(a, n, s);
    cout << "Mảng sau khi sắp xếp theo tổng chữ số: ";
    for (int i = 0; i < n; i++) cout << s[i] << " ";
    cout << endl;

    // (c) Xóa các số nguyên tố
    n = removePrimes(a, n);
    cout << "Mảng sau khi xóa số nguyên tố: ";
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << endl;

    return 0;
}
