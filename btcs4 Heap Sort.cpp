#include <bits/stdc++.h>
#include <fstream>
#include <sstream>

const int MAX_SIZE = 10000; // Giới hạn kích thước mảng

// Đọc dữ liệu từ file văn bản
int readData(const std::string &filename, int arr[], int &size) {
    std::ifstream file(filename);
    if (!file.is_open()) return 0;
    size = 0;
    while (file >> arr[size] && size < MAX_SIZE) {
        size++;
    }
    file.close();
    return size;
}

// Ghi kết quả vào file
void writeData(const std::string &filename, int arr[], int size, double time) {
    std::ofstream file(filename);
    file << "Time: " << time << " ms\n";
    for (int i = 0; i < size; i++) file << arr[i] << " ";
}

// Heapify một nút
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// Heap Sort
void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// Đo thời gian chạy Heap Sort
void measureSortTime(int arr[], int size) {
    auto start = std::chrono::high_resolution_clock::now();
    heapSort(arr, size);
    auto end = std::chrono::high_resolution_clock::now();
    double time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    writeData("output.txt", arr, size, time_taken);
}

int main() {
    int data[MAX_SIZE];
    int size;
    if (!readData("test.docx", data, size) || size == 0) {
        std::cout << "Error: Input file is empty!\n";
        return 1;
    }
    measureSortTime(data, size);
    std::cout << "Sorting completed! Check output.txt\n";
    return 0;
}