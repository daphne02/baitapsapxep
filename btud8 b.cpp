#include <iostream>
using namespace std;

void timHoanViTuNghichThe(int B[], int A[], int N) {
    int unused[N]; // Các số tự nhiên chưa được sử dụng
    for (int i = 0; i < N; i++) {
        unused[i] = i + 1;
    }
    
    for (int i = N - 1; i >= 0; i--) {
        A[i] = unused[B[i]];
        for (int j = B[i]; j < N - 1; j++) {
            unused[j] = unused[j + 1];
        }
    }
}

int main() {
    int B[] = {2, 3, 6, 4, 0, 2, 2, 1, 0};
    int N = sizeof(B) / sizeof(B[0]);
    int A[N];

    timHoanViTuNghichThe(B, A, N);

    cout << "Hoan vi tuong ung: ";
    for (int i = 0; i < N; i++) {
        cout << A[i] << " ";
    }
    return 0;
}
