#include <iostream>
using namespace std;
//Chia và hợp nhất từng mảng cho Merge Sort
void Merge(int a[], int left, int mid, int right, bool (*cmp)(int, int)) {
    int n1 = mid - left +1;
    int n2 = right - mid;
    int L[n1], R[n2];
    for(int i = 0; i < n1; i++) {
        L[i] = a[left + i];
    }
    for(int i = 0; i < n2; i++) {
        R[i] = a[mid + 1 + i];
    }
    int i = 0, j = 0, k = left;
    while(i < n1 && j < n2) {
        if(cmp(L[i], R[j])) {
            a[k++] = L[i++];
        } else {
            a[k++] = R[j++];
        }
    }
    while(i < n1) {
        a[k++] = L[i++];
    }
    while(j < n2) {
        a[k++] = R[j++];
    }
}
//Sử dụng thuật toán Merge Sort
void MergeSort(int a[], int left, int right, bool (*cmp)(int, int)) {
    if(left < right) {
        int mid = left + (right - left) / 2;
        MergeSort(a, left, mid, cmp);
        MergeSort(a, mid + 1, right, cmp);
        Merge(a, left, mid, right, cmp);
    }
}
//Sắp Xếp các số chẵn
bool SapXepChan(int a, int b) {
    return a < b;
}
//Sắp xếp các số lẻ
bool SapXepLe(int a, int b) {
    return a > b;
}
//Sắp xếp mảng theo yêu cầu
void SapXepMang(int a[], int n) {
    int AChan[n], ALe[n];
    int DemChan = 0, DemLe = 0;
    for(int i = 0; i < n; i++) {
        if(a[i] != 0) {
            if(a[i] % 2 == 0) {
                AChan[DemChan++] = a[i];
            } else {
                ALe[DemLe++] = a[i];
            }
        }
    }
    MergeSort(AChan, 0, DemChan - 1, SapXepChan);
    MergeSort(ALe, 0, DemLe - 1, SapXepLe);
    int SoChan = 0, SoLe = 0;
    for(int i = 0; i < n; i++) {
        if (a[i] == 0) {
            continue;
        }
        if(a[i] % 2 == 0) {
            a[i] = AChan[SoChan++];
        } else {
            a[i] = ALe[SoLe++];
        }
    }
}
//In mảng ra
void InMang(int a[], int n) {
    for(int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}
int main() {
    int n;
    cout<<"Moi ban nhap so luong phan tu: ";
    cin>>n;
    if(n < 1) {
        cout<<"Ban da nhap sai, moi nhap lai: ";
        cin>>n;
    }
    int a[n];
    for(int i = 0; i < n; i++) {
        cout<<"Phan tu thu "<<i<<": ";
        cin>>a[i];
    }
    SapXepMang(a, n);
    cout<<"Mang sau khi sap xep: ";
    InMang(a, n);
    return 0;
}