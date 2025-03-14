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

// Heapify một nút
void heapify(int* arr, int n, int i) {
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
void heapSort(int* arr, int n) {
    // Xây dựng max heap
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);

    // Trích xuất từng phần tử khỏi heap
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);  // Đưa phần tử lớn nhất ra cuối
        heapify(arr, i, 0);
    }
}

// Đo thời gian chạy Heap Sort
void measureSortTime(int* arr, int size) {
    auto start = std::chrono::high_resolution_clock::now();
    heapSort(arr, size);
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
