#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <chrono>

// Đọc dữ liệu từ file .txt (file .docx không thể đọc trực tiếp theo cách này)
int* readData(const std::string &filename, int &size) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Lỗi: Không thể mở tệp " << filename << "!\n";
        size = 0;
        return nullptr;
    }

    std::vector<int> temp;  // Dùng tạm thời để đếm số lượng phần tử
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        int num;
        while (ss >> num) {
            temp.push_back(num);
        }
    }
    file.close();

    size = temp.size();
    if (size == 0) return nullptr;

    // Cấp phát mảng động
    int* arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = temp[i];
    }
    return arr;
}

// Ghi kết quả vào file
void writeData(const std::string &filename, int* arr, int size, double time) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Lỗi: Không thể mở tệp đầu ra!\n";
        return;
    }

    file << "Thời gian: " << time << " ms\n";
    for (int i = 0; i < size; i++) {
        file << arr[i] << " ";
    }
    file.close();
}

// Sắp xếp trao đổi (Interchange Sort)
void interchangeSort(int* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] > arr[j]) {
                std::swap(arr[i], arr[j]);
            }
        }
    }
}

// Đo thời gian chạy sắp xếp
void measureSortTime(int* arr, int size) {
    auto start = std::chrono::high_resolution_clock::now();
    interchangeSort(arr, size);
    auto end = std::chrono::high_resolution_clock::now();
    
    double time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    writeData("output.txt", arr, size, time_taken);
}

int main() {
    int size;
    int* data = readData("test.txt", size);  // Đổi tên file để đảm bảo đọc được

    if (data == nullptr || size == 0) {
        std::cout << "Lỗi: Tệp đầu vào trống hoặc không thể đọc!\n";
        return 1;
    }

    measureSortTime(data, size);
    std::cout << "Đã sắp xếp xong! Kiểm tra output.txt\n";

    delete[] data;  // Giải phóng bộ nhớ động
    return 0;
}
