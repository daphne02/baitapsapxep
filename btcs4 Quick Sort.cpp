#include <bits/stdc++.h>
#include <fstream>
#include <sstream>

#define MAX_SIZE 10000  // Giới hạn kích thước mảng

// Đọc dữ liệu từ file văn bản
int readData(const std::string &filename, int arr[]) {
    std::ifstream file(filename);
    std::string line;
    int count = 0;
    if (file.is_open()) {
        while (std::getline(file, line) && count < MAX_SIZE) {
            std::stringstream ss(line);
            while (ss >> arr[count] && count < MAX_SIZE) {
                count++;
            }
        }
        file.close();
    }
    return count;
}

// Ghi kết quả vào file
void writeData(const std::string &filename, int arr[], int size, double time) {
    std::ofstream file(filename);
    file << "Time: " << time << " ms\n";
    for (int i = 0; i < size; i++) file << arr[i] << " ";
}

// Quick Sort
void quickSort(int arr[], int left, int right) {
    if (left >= right) return;
    int pivot = arr[right];
    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (arr[j] < pivot) std::swap(arr[++i], arr[j]);
    }
    std::swap(arr[++i], arr[right]);
    quickSort(arr, left, i - 1);
    quickSort(arr, i + 1, right);
}

// Đo thời gian chạy Quick Sort
void measureSortTime(int arr[], int size) {
    auto start = std::chrono::high_resolution_clock::now();
    quickSort(arr, 0, size - 1);
    auto end = std::chrono::high_resolution_clock::now();
    double time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    writeData("output.txt", arr, size, time_taken);
}

int main() {
    int data[MAX_SIZE];
    int size = readData("test.docx", data);
    if (size == 0) {
        std::cout << "Error: Input file is empty!\n";
        return 1;
    }
    measureSortTime(data, size);
    std::cout << "Sorting completed! Check output.txt\n";
    return 0;
}