#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MASV  10
#define MAX_HOTEN 50

// Cấu trúc lưu thông tin một sinh viên
typedef struct {
    char maSV[MAX_MASV];
    char hoTen[MAX_HOTEN];
    float diemTB;
} SinhVien;

// Node của danh sách liên kết sinh viên
typedef struct NodeSV {
    SinhVien sv;
    struct NodeSV* next;
} NodeSV;

// Node của danh sách liên kết chỉ mục (lưu mã SV)
typedef struct NodeIndex {
    char maSV[MAX_MASV];
    struct NodeIndex* next;
} NodeIndex;

// Hàm thêm 1 sinh viên vào cuối danh sách liên kết sinh viên
void themCuoiDS_SV(NodeSV** pHead, SinhVien sv) {
    NodeSV* p = (NodeSV*)malloc(sizeof(NodeSV));
    if (p == NULL) {
        printf("Loi cap phat bo nho!\n");
        exit(1);
    }
    p->sv = sv;
    p->next = NULL;
    
    if (*pHead == NULL) {
        *pHead = p;
    } else {
        NodeSV* temp = *pHead;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = p;
    }
}

// Hàm đọc danh sách sinh viên từ tệp SINHVIEN.DAT
NodeSV* docFile_SinhVien(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (f == NULL) {
        printf("Khong mo duoc tep %s\n", filename);
        return NULL;
    }
    
    NodeSV* dsSV = NULL;
    char buffer[200];
    
    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        size_t len = strlen(buffer);
        if(len > 0 && buffer[len - 1] == '\n')
            buffer[len - 1] = '\0';
        
        char* pMaSV  = strtok(buffer, "|");
        char* pHoTen = strtok(NULL, "|");
        char* pDiem  = strtok(NULL, "|");
        
        if(pMaSV && pHoTen && pDiem) {
            SinhVien sv;
            strcpy(sv.maSV, pMaSV);
            strcpy(sv.hoTen, pHoTen);
            sv.diemTB = (float)atof(pDiem);
            
            themCuoiDS_SV(&dsSV, sv);
        }
    }
    fclose(f);
    return dsSV;
}

// Hàm in danh sách sinh viên
void inDanhSach(NodeSV* dsSV) {
    NodeSV* p = dsSV;
    while (p != NULL) {
        printf("%-10s | %-30s | %6.2f\n", p->sv.maSV, p->sv.hoTen, p->sv.diemTB);
        p = p->next;
    }
}

// Hàm giải phóng danh sách liên kết sinh viên
void giaiPhongDS_SV(NodeSV* dsSV) {
    NodeSV* p;
    while(dsSV != NULL) {
        p = dsSV;
        dsSV = dsSV->next;
        free(p);
    }
}

int main() {
    NodeSV* dsSV = docFile_SinhVien("SINHVIEN.DAT");
    if(dsSV == NULL) {
        printf("Khong co du lieu sinh vien!\n");
        return 1;
    }
    
    printf("Danh sach sinh vien:\n");
    printf("-----------------------------------------\n");
    inDanhSach(dsSV);
    
    giaiPhongDS_SV(dsSV);
    return 0;
}
