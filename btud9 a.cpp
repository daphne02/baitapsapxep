#include <iostream>
#include <fstream>
#include <set>
using namespace std;

struct SinhVien {
    int ma;
    char ho_dem[21];
    char ten[41];
    int ngay, thang, nam;
    char phai[4];
    float diem;
};

void nhapDanhSach(SinhVien danh_sach[], int &n) {
    set<int> ma_da_co;
    
    cout << "Nhập số lượng sinh viên (tối thiểu 10, tối đa 100): ";
    cin >> n;
    cin.ignore();
    
    while (n < 10 || n > 100) {
        cout << "Số lượng không hợp lệ! Nhập lại (10 - 100): ";
        cin >> n;
        cin.ignore();
    }

    for (int i = 0; i < n; i++) {
        SinhVien sv;
        do {
            cout << "Nhập mã số sinh viên " << i + 1 << ": ";
            cin >> sv.ma;
            cin.ignore();
            if (ma_da_co.count(sv.ma)) {
                cout << "Mã số đã tồn tại! Vui lòng nhập lại.\n";
            }
        } while (ma_da_co.count(sv.ma));
        ma_da_co.insert(sv.ma);
        
        cout << "Nhập họ và đệm: ";
        cin.getline(sv.ho_dem, 21);
        
        cout << "Nhập tên sinh viên: ";
        cin.getline(sv.ten, 41);
        
        cout << "Nhập ngày sinh: ";
        cin >> sv.ngay;
        cout << "Nhập tháng sinh: ";
        cin >> sv.thang;
        cout << "Nhập năm sinh: ";
        cin >> sv.nam;
        cin.ignore();
        
        cout << "Nhập phái (Nam/Nữ): ";
        cin.getline(sv.phai, 4);
        
        cout << "Nhập điểm trung bình: ";
        cin >> sv.diem;
        cin.ignore();
        
        danh_sach[i] = sv; // Lưu vào mảng
    }
    
    ofstream file("SINHVIEN.DAT", ios::binary);
    for (int i = 0; i < n; i++) {
        file.write(reinterpret_cast<const char*>(&danh_sach[i]), sizeof(SinhVien));
    }
    file.close();
    cout << "Danh sách đã được lưu vào tệp SINHVIEN.DAT.\n";
}

int main() {
    SinhVien danh_sach[100]; // Mảng tối đa 100 sinh viên
    int n;
    nhapDanhSach(danh_sach, n);
    return 0;
}
