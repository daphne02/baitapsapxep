#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

const int MAX_SV = 100; // Giả sử tối đa 100 sinh viên

struct SinhVien {
    int maSo;
    string hoVaDem;
    string ten;
    int ngaySinh;
    int thangSinh;
    int namSinh;
    string phai;
    float diemTB;
};

void nhapSinhVien(SinhVien &sv, SinhVien danhSach[], int &soLuong) {
    while (true) {
        cout << "Nhập mã số sinh viên: ";
        cin >> sv.maSo;
        bool trungMa = false;
        for (int i = 0; i < soLuong; i++) {
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
    getline(cin, sv.hoVaDem);
    if (sv.hoVaDem.length() > 20) sv.hoVaDem = sv.hoVaDem.substr(0, 20);
    
    cout << "Nhập tên sinh viên (tối đa 40 ký tự): ";
    getline(cin, sv.ten);
    if (sv.ten.length() > 40) sv.ten = sv.ten.substr(0, 40);
    
    cout << "Nhập ngày sinh: "; cin >> sv.ngaySinh;
    cout << "Nhập tháng sinh: "; cin >> sv.thangSinh;
    cout << "Nhập năm sinh: "; cin >> sv.namSinh;
    
    do {
        cout << "Nhập phái (Nam/Nữ): ";
        cin >> sv.phai;
    } while (sv.phai != "Nam" && sv.phai != "Nữ");
    
    do {
        cout << "Nhập điểm trung bình (0.00 - 10.00): ";
        cin >> sv.diemTB;
    } while (sv.diemTB < 0.00 || sv.diemTB > 10.00);
}

void luuSinhVien(const string &tenFile, SinhVien danhSach[], int soLuong) {
    ofstream file(tenFile, ios::binary);
    if (!file) {
        cout << "Không thể mở file để ghi dữ liệu!\n";
        return;
    }
    file.write(reinterpret_cast<const char*>(danhSach), soLuong * sizeof(SinhVien));
    file.close();
    cout << "Dữ liệu sinh viên đã được lưu vào tập tin " << tenFile << "\n";
}

int docSinhVien(const string &tenFile, SinhVien danhSach[]) {
    ifstream file(tenFile, ios::binary);
    if (!file) {
        cout << "Không thể mở file để đọc dữ liệu!\n";
        return 0;
    }
    int soLuong = 0;
    while (file.read(reinterpret_cast<char*>(&danhSach[soLuong]), sizeof(SinhVien))) {
        soLuong++;
    }
    file.close();
    return soLuong;
}

void inDanhSach(SinhVien danhSach[], int soLuong) {
    cout << "\nDanh sách sinh viên:\n";
    cout << left << setw(10) << "Mã số" << setw(25) << "Họ và đệm" << setw(15) << "Tên"
         << setw(10) << "Ngày sinh" << setw(10) << "Phái" << setw(10) << "Điểm TB" << endl;
    cout << string(80, '-') << endl;
    for (int i = 0; i < soLuong; i++) {
        cout << left << setw(10) << danhSach[i].maSo << setw(25) << danhSach[i].hoVaDem << setw(15) << danhSach[i].ten
             << setw(2) << danhSach[i].ngaySinh << "/" << setw(2) << danhSach[i].thangSinh << "/" << setw(4) << danhSach[i].namSinh
             << setw(10) << danhSach[i].phai << setw(10) << danhSach[i].diemTB << endl;
    }
}

int main() {
    SinhVien danhSach[MAX_SV];
    int soLuong = 10;
    
    cout << "Nhập danh sách " << soLuong << " sinh viên:\n";
    for (int i = 0; i < soLuong; ++i) {
        nhapSinhVien(danhSach[i], danhSach, soLuong);
    }
    
    luuSinhVien("SINHVIEN.DAT", danhSach, soLuong);
    
    // Đọc dữ liệu từ tập tin
    soLuong = docSinhVien("SINHVIEN.DAT", danhSach);
    
    // Sắp xếp danh sách theo mã số sinh viên tăng dần
    sort(danhSach, danhSach + soLuong, [](const SinhVien &a, const SinhVien &b) {
        return a.maSo < b.maSo;
    });
    
    // In danh sách đã sắp xếp
    inDanhSach(danhSach, soLuong);
    
    return 0;
}
