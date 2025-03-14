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

// Bubble Sort
void bubbleSort(int* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Đo thời gian chạy Bubble Sort
void measureSortTime(int* arr, int size) {
    auto start = std::chrono::high_resolution_clock::now();
    bubbleSort(arr, size);
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
