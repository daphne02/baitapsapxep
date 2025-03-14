
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

const int MAX_SV = 100;

struct SinhVien {
    int maSo;
    char hoDem[21];
    char ten[41];
    int ngay, thang, nam;
    char phai[4];
    float diemTB;
};

void nhapSinhVien(SinhVien sv[], int &n) {
    for (int i = 0; i < n; i++) {
        cout << "Nhap sinh vien thu " << i + 1 << endl;
        bool trungMa;

        do {
            trungMa = false;

            cout << "Ma so: ";
            cin >> sv[i].maSo;

            for (int j = 0; j < i; j++) {
                if (sv[i].maSo == sv[j].maSo) {
                    cout << "Ma so bi trung! Nhap lai." << endl;
                    trungMa = true;
                    break;
                }
            }
        } while (trungMa);

        cin.ignore();
        cout << "Ho va dem: ";
        cin.getline(sv[i].hoDem, 21);
        cout << "Ten: ";
        cin.getline(sv[i].ten, 41);
        cout << "Ngay sinh (ngay thang nam): ";
        cin >> sv[i].ngay >> sv[i].thang >> sv[i].nam;
        cin.ignore();
        cout << "Phai (Nam/Nu): ";
        cin.getline(sv[i].phai, 4);
        cout << "Diem trung binh: ";
        cin >> sv[i].diemTB;
    }
}

void luuFile(SinhVien sv[], int n) {
    ofstream file("SINHVIEN.DAT", ios::binary);
    file.write((char*)sv, sizeof(SinhVien) * n);
    file.close();
}

void docFile(SinhVien sv[], int &n) {
    ifstream file("SINHVIEN.DAT", ios::binary);
    n = 0;
    while (file.read((char*)&sv[n], sizeof(SinhVien))) {
        n++;
    }
    file.close();
}

void inDanhSach(SinhVien sv[], int n) {
    cout << setw(10) << "Ma so" << setw(20) << "Ho va dem" << setw(20) << "Ten"
         << setw(10) << "Ngay sinh" << setw(10) << "Phai" << setw(10) << "Diem TB" << endl;

    for (int i = 0; i < n; i++) {
        cout << setw(10) << sv[i].maSo << setw(20) << sv[i].hoDem << setw(20) << sv[i].ten
             << setw(4) << sv[i].ngay << "/" << sv[i].thang << "/" << sv[i].nam
             << setw(10) << sv[i].phai << setw(10) << sv[i].diemTB << endl;
    }
}

bool soSanhMaSo(SinhVien a, SinhVien b) {
    return a.maSo < b.maSo;
}

bool soSanhTen(SinhVien a, SinhVien b) {
    int cmpTen = strcmp(a.ten, b.ten);
    if (cmpTen == 0) {
        return strcmp(a.hoDem, b.hoDem) < 0;
    }
    return cmpTen < 0;
}

bool soSanhDiemTB(SinhVien a, SinhVien b) {
    return a.diemTB > b.diemTB;
}

void luuChiMuc(const char* fileName, SinhVien sv[], int n, bool (*cmp)(SinhVien, SinhVien)) {
    SinhVien temp[MAX_SV];
    memcpy(temp, sv, sizeof(SinhVien) * n);
    sort(temp, temp + n, cmp);

    ofstream file(fileName, ios::binary);
    file.write((char*)temp, sizeof(SinhVien) * n);
    file.close();
}

void docTheoChiMuc(const char* fileName) {
    SinhVien sv[MAX_SV];
    int n = 0;

    ifstream file(fileName, ios::binary);
    while (file.read((char*)&sv[n], sizeof(SinhVien))) {
        n++;
    }
    file.close();

    inDanhSach(sv, n);
}

int main() {
    SinhVien sv[MAX_SV];
    int n = 10;

    nhapSinhVien(sv, n);
    luuFile(sv, n);

    cout << "\nDanh sach sinh vien tu file SINHVIEN.DAT:" << endl;
    docFile(sv, n);
    inDanhSach(sv, n);

    luuChiMuc("SVMASO.IDX", sv, n, soSanhMaSo);
    luuChiMuc("SVTH.IDX", sv, n, soSanhTen);
    luuChiMuc("SVDTB.IDX", sv, n, soSanhDiemTB);

    cout << "\nDanh sach theo chi muc Ma So:" << endl;
    docTheoChiMuc("SVMASO.IDX");

    cout << "\nDanh sach theo chi muc Ten:" << endl;
    docTheoChiMuc("SVTH.IDX");

    cout << "\nDanh sach theo chi muc Diem TB:" << endl;
    docTheoChiMuc("SVDTB.IDX");

    return 0;
}
