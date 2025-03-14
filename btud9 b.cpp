#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

struct SinhVien {
    int maSo;
    char hoVaDem[21]; 
    char ten[41]; 
    int ngaySinh;
    int thangSinh;
    int namSinh;
    char phai[4];
    float diemTB;
};

// Nhập thông tin sinh viên vào mảng
void nhapSinhVien(SinhVien &sv, SinhVien danhSach[], int n) {
    while (true) {
        cout << "Nhập mã số sinh viên: ";
        cin >> sv.maSo;
        bool trungMa = false;
        for (int i = 0; i < n; i++) {
            if (danhSach[i].maSo == sv.maSo) {
                trungMa = true;
                break;
            }
        }
        if (!trungMa) break;
        cout << "Mã số sinh viên đã tồn tại, vui lòng nhập lại!\n";
    }
    cin.ignore();
    cout << "Nhập họ và đệm (tối đa 20 ký tự): ";
    cin.getline(sv.hoVaDem, 21);
    
    cout << "Nhập tên sinh viên (tối đa 40 ký tự): ";
    cin.getline(sv.ten, 41);
    
    cout << "Nhập ngày sinh: "; cin >> sv.ngaySinh;
    cout << "Nhập tháng sinh: "; cin >> sv.thangSinh;
    cout << "Nhập năm sinh: "; cin >> sv.namSinh;
    
    do {
        cout << "Nhập phái (Nam/Nữ): ";
        cin >> sv.phai;
    } while (string(sv.phai) != "Nam" && string(sv.phai) != "Nữ");
    
    do {
        cout << "Nhập điểm trung bình (0.00 - 10.00): ";
        cin >> sv.diemTB;
    } while (sv.diemTB < 0.00 || sv.diemTB > 10.00);
}

// Lưu dữ liệu vào file
void luuSinhVien(const string &tenFile, SinhVien danhSach[], int n) {
    ofstream file(tenFile, ios::binary);
    if (!file) {
        cout << "Không thể mở file để ghi dữ liệu!\n";
        return;
    }
    file.write(reinterpret_cast<const char*>(danhSach), sizeof(SinhVien) * n);
    file.close();
    cout << "Dữ liệu sinh viên đã được lưu vào tập tin " << tenFile << "\n";
}

// Đọc dữ liệu từ file
int docSinhVien(const string &tenFile, SinhVien danhSach[]) {
    ifstream file(tenFile, ios::binary);
    if (!file) {
        cout << "Không thể mở file để đọc dữ liệu!\n";
        return 0;
    }
    int n = 0;
    while (file.read(reinterpret_cast<char*>(&danhSach[n]), sizeof(SinhVien))) {
        n++;
    }
    file.close();
    return n;
}

// In danh sách sinh viên
void inDanhSach(SinhVien danhSach[], int n) {
    cout << "\nDanh sách sinh viên:\n";
    cout << left << setw(10) << "Mã số" << setw(25) << "Họ và đệm" << setw(15) << "Tên"
         << setw(10) << "Ngày sinh" << setw(10) << "Phái" << setw(10) << "Điểm TB" << endl;
    cout << string(80, '-') << endl;
    for (int i = 0; i < n; i++) {
        cout << left << setw(10) << danhSach[i].maSo << setw(25) << danhSach[i].hoVaDem << setw(15) << danhSach[i].ten
             << setw(2) << danhSach[i].ngaySinh << "/" << setw(2) << danhSach[i].thangSinh << "/" << setw(4) << danhSach[i].namSinh
             << setw(10) << danhSach[i].phai << setw(10) << danhSach[i].diemTB << endl;
    }
}

// Sắp xếp danh sách sinh viên theo mã số tăng dần
void sapXepDanhSach(SinhVien danhSach[], int n) {
    sort(danhSach, danhSach + n, [](const SinhVien &a, const SinhVien &b) {
        return a.maSo < b.maSo;
    });
}

int main() {
    SinhVien danhSach[100]; // Mảng tối đa 100 sinh viên
    int soLuong = 10;
    
    cout << "Nhập danh sách " << soLuong << " sinh viên:\n";
    for (int i = 0; i < soLuong; ++i) {
        nhapSinhVien(danhSach[i], danhSach, i);
    }
    
    luuSinhVien("SINHVIEN.DAT", danhSach, soLuong);
    
    // Đọc dữ liệu từ file
    soLuong = docSinhVien("SINHVIEN.DAT", danhSach);
    
    // Sắp xếp và in danh sách
    sapXepDanhSach(danhSach, soLuong);
    inDanhSach(danhSach, soLuong);
    
    return 0;
}
