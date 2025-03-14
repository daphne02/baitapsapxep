#include <iostream>
#include <ctime>

using namespace std;

const int MAX = 10000; // Định nghĩa kích thước tối đa của mảng

int compareCount = 0, swapCount = 0;

// Hàm hoán vị hai phần tử
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
    swapCount++;
}

// Thuật toán Interchange Sort
void interchangeSort(int arr[], int n) {
    compareCount = swapCount = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            compareCount++;
            if (arr[i] > arr[j]) {
                swap(arr[i], arr[j]);
            }
        }
    }
}

// Thuật toán Selection Sort
void selectionSort(int arr[], int n) {
    compareCount = swapCount = 0;
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            compareCount++;
            if (arr[j] < minIndex) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

// Thuật toán Insertion Sort
void insertionSort(int arr[], int n) {
    compareCount = swapCount = 0;
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            compareCount++;
            arr[j + 1] = arr[j];
            swapCount++;
            j--;
        }
        arr[j + 1] = key;
    }
}

// Thuật toán Bubble Sort
void bubbleSort(int arr[], int n) {
    compareCount = swapCount = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            compareCount++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Thuật toán Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        compareCount++;
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortHelper(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortHelper(arr, low, pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}

void quickSort(int arr[], int n) {
    compareCount = swapCount = 0;
    quickSortHelper(arr, 0, n - 1);
}

// Thuật toán Merge Sort
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        compareCount++;
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }
    while (j < n2) {
        arr[k++] = R[j++];
    }
}

void mergeSortHelper(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortHelper(arr, l, m);
        mergeSortHelper(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void mergeSort(int arr[], int n) {
    compareCount = swapCount = 0;
    mergeSortHelper(arr, 0, n - 1);
}

// Thuật toán Heap Sort
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;

    compareCount += 2;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    compareCount = swapCount = 0;
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// Hàm tạo mảng ngẫu nhiên
void generateArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }
}

// Hàm đo thời gian và số lần thực hiện
void measurePerformance(void (*sortFunc)(int[], int), int arr[], int n) {
    clock_t start = clock();
    sortFunc(arr, n);
    clock_t end = clock();

    cout << "Thời gian: " << (double)(end - start) / CLOCKS_PER_SEC << " giây\n";
    cout << "Số lần so sánh: " << compareCount << "\n";
    cout << "Số lần đổi chỗ: " << swapCount << "\n\n";
}

int main() {
    int arr[MAX];

    generateArray(arr, MAX);
    measurePerformance(interchangeSort, arr, MAX);
    generateArray(arr, MAX);
    measurePerformance(selectionSort, arr, MAX);
    generateArray(arr, MAX);
    measurePerformance(insertionSort, arr, MAX);
    generateArray(arr, MAX);
    measurePerformance(bubbleSort, arr, MAX);
    generateArray(arr, MAX);
    measurePerformance(quickSort, arr, MAX);
    generateArray(arr, MAX);
    measurePerformance(mergeSort, arr, MAX);
    generateArray(arr, MAX);
    measurePerformance(heapSort, arr, MAX);

    return 0;
}
