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

// Merge Sort
void merge(int arr[], int left, int mid, int right) {
    int temp[right - left + 1];
    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    for (int t = 0; t < k; t++) arr[left + t] = temp[t];
}

void mergeSort(int arr[], int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// Đo thời gian chạy Merge Sort
void measureSortTime(int arr[], int size) {
    auto start = std::chrono::high_resolution_clock::now();
    mergeSort(arr, 0, size - 1);
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
