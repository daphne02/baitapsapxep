#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;
//Cấu trúc sinh viên
struct SinhVien {
    int MaSo;
    string HoVaDem;
    string Ten;
    int NgaySinh;
    int ThangSinh;
    int NamSinh;
    string Phai;
    float DiemTrungBinh;
};
//Ghi thông tin sinh viên vào tập tin
void GhiVaoFile(SinhVien ds[], int n, const string& TenFile) {
    ofstream file(TenFile);
    if(!file) {
        cerr<<"Khong the mo file!"<<endl;
        return;
    }
    for(int i = 0; i < n; i++) {
        file<<ds[i].MaSo<<" "<<ds[i].HoVaDem<<" "<<ds[i].Ten<<" "<<ds[i].NgaySinh<<" "<<ds[i].ThangSinh<<" "<<ds[i].NamSinh<<" "<<ds[i].Phai<<" "<<fixed<<setprecision(2)<<ds[i].DiemTrungBinh<<endl;
    }
    file.close();
}
//Chia và hợp nhất mảng cho Merge Sort
void Merge(SinhVien a[], int left, int right, int (*cmp)(const SinhVien&, const SinhVien&)) {
    if(left >= right) return;
    int mid = left + (right - left) / 2;
    Merge(a, left, mid, cmp);
    Merge(a, mid + 1, right, cmp);
    SinhVien temp[right - left + 1];
    int i = left, j = mid + 1, k = 0;
    while(i <= mid && j <= right) {
        if(cmp(a[i], a[j])) {
            temp[k++] = a[i++];
        } else {
            temp[k++] = a[j++];
        }
    }
    while(i <= mid) {
        temp[k++] = a[i++];
    }
    while(j <= right) {
        temp[k++] = a[j++];
    }
    for(i = left, k = 0; i <= right; i++, k++) {
        a[i] = temp[k];
    }
}
//Sắp xếp theo mã sinh viên
bool SapXepTheoMaSinhVien(const SinhVien &sv1, const SinhVien &sv2) {
    return sv1.MaSo < sv2.MaSo;
}
//Sắp xếp theo tên sinh viên và họ đệm
bool SapXepTheoTenSinhVien(const SinhVien &sv1, const SinhVien &sv2) {
    if(sv1.Ten == sv2.Ten) {
        return sv1.HoVaDem < sv2.HoVaDem;
    }
    return sv1.Ten < sv2.Ten;
}
//Sắp xếp theo điểm trung bình
bool SapXepTheoDiemTrungBinh(const SinhVien &sv1, const SinhVien &sv2) {
    return sv1.DiemTrungBinh > sv2.DiemTrungBinh;
}
//Sử dụng thuật toán Merge Sort
void MergeSort(SinhVien a[], int left, int right, int (*cmp)(const SinhVien&, const SinhVien&)) {
    Merge(a, left, right, cmp);
}
int main() {
    SinhVien DanhSachSinhVien[3] = {
        {101, "Nguyen Van", "A", 1, 1, 2000, "Nam", 9},
        {102, "Le Thi", "B", 2, 2, 2002, "Nu", 8},
        {103, "Tran Van", "C", 3, 5, 2001, "Nam", 7.5}
    };
    int n = 3;
    MergeSort(DanhSachSinhVien, 0, n - 1, SapXepTheoMaSinhVien);
    GhiVaoFile(DanhSachSinhVien, n, "SVMASO.IDX");
    MergeSort(DanhSachSinhVien, 0, n - 1, SapXepTheoTenSinhVien);
    GhiVaoFile(DanhSachSinhVien, n, "SVTH.IDX");
    MergeSort(DanhSachSinhVien, 0, n - 1, SapXepTheoDiemTrungBinh);
    GhiVaoFile(DanhSachSinhVien, n, "SVDTB.IDX");
    cout<<"Da tao cac tap tin chi muc: SVMASO.IDX, SVTH.IDX, SVDTB.IDX"<<endl;
    return 0;
}
