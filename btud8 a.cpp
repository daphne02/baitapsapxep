#include <iostream>
using namespace std;

void timMangNghichThe(int A[], int B[], int N) {
    for (int i = 0; i < N; i++) {
        int count = 0;
        for (int j = 0; j < i; j++) {
            if (A[j] > A[i]) {
                count++;
            }
        }
        B[i] = count;
    }
}

int main() {
    int A[] = {5, 9, 1, 8, 2, 6, 4, 7, 3};
    int N = sizeof(A) / sizeof(A[0]);
    int B[N];

    timMangNghichThe(A, B, N);

    cout << "Mang nghich the: ";
    for (int i = 0; i < N; i++) {
        cout << B[i] << " ";
    }

    return 0;
}