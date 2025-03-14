#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <chrono>

// Đọc dữ liệu từ file văn bản và lưu vào mảng động
int* readData(const std::string &filename, int &size) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Cannot open file " << filename << "!\n";
        size = 0;
        return nullptr;
    }

    std::vector<int> temp;  // Dùng vector tạm để xác định kích thước mảng
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
        std::cout << "Error: Cannot open output file!\n";
        return;
    }

    file << "Time: " << time << " ms\n";
    for (int i = 0; i < size; i++) {
        file << arr[i] << " ";
    }
    file.close();
}

// Quick Sort
void quickSort(int* arr, int left, int right) {
    if (left >= right) return;
    int pivot = arr[right];  // Chọn phần tử cuối làm chốt
    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (arr[j] < pivot) {
            std::swap(arr[++i], arr[j]);
        }
    }
    std::swap(arr[++i], arr[right]);

    quickSort(arr, left, i - 1);
    quickSort(arr, i + 1, right);
}

// Đo thời gian chạy Quick Sort
void measureSortTime(int* arr, int size) {
    auto start = std::chrono::high_resolution_clock::now();
    quickSort(arr, 0, size - 1);
    auto end = std::chrono::high_resolution_clock::now();

    double time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    writeData("output.txt", arr, size, time_taken);
}

int main() {
    int size;
    int* data = readData("test.txt", size);  // Đổi tên file để đảm bảo đọc được

    if (data == nullptr || size == 0) {
        std::cout << "Error: Input file is empty or cannot be read!\n";
        return 1;
    }

    measureSortTime(data, size);
    std::cout << "Sorting completed! Check output.txt\n";

    delete[] data;  // Giải phóng bộ nhớ động
    return 0;
}
