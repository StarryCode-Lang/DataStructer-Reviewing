#include <cmath>
#include <iostream>
using namespace std;

// =============================
// 插入排序算法
// 1. 直接插入排序
void InsertSort(int A[], int n) {
    int j;
    for (int i = 2; i <= n; i++) {
        if (A[i] < A[i - 1]) {
            A[0] = A[i];
            for (j = i - 1; A[0] < A[j]; j--) {
                A[j + 1] = A[j];
            }
            A[j + 1] = A[0];
        }
    }
}

// 2. 折半插入排序
void BinaryInsertSort(int A[], int n) {
    for (int i = 2; i <= n; i++) {
        A[0] = A[i];
        int low = 1;
        int high = i - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (A[0] < A[mid]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        for (int j = i - 1; j >= high + 1; j--) {
            A[j + 1] = A[j];
        }
        A[high + 1] = A[0];
    }
}

// 3. 希尔排序
void ShellSort(int A[], int n) {
    int j;
    for (int dk = n / 2; dk >= 1; dk = dk / 2) {
        for (int i = dk + 1; i <= n; i++) {
            if (A[i] < A[i - dk]) {
                A[0] = A[i];
                for (j = i - dk; j > 0 && A[0] < A[j]; j -= dk) {
                    A[j + dk] = A[j];
                }
                A[j + dk] = A[0];
            }
        }
    }
}
// =============================


// =============================
// 交换排序算法
// 1. 冒泡排序
void BubbleSort(int A[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        bool flag = false;
        for (int j = n - 1; j > i; --j) {
            if (A[j] < A[j - 1]) {
                swap(A[j], A[j - 1]);
                flag = true;
            }
        }
        if (!flag) {
            return;
        }
    }
}

// 2. 快速排序
int Partition(int A[], int low, int high) {
    int pivot = A[low];
    while (low < high) {
        while (low < high && A[high] >= pivot) {
            --high;
        }
        A[low] = A[high];
        while (low < high && A[low] <= pivot) {
            ++low;
        }
        A[high] = A[low];
    }
    A[low] = pivot;
    return low;
}

void QuickSort(int A[], int low, int high) {
    if (low < high) {
        int pivotpos = Partition(A, low, high);
        QuickSort(A, low, pivotpos - 1);
        QuickSort(A, pivotpos + 1, high);
    }
}
// =============================


// =============================
// 选择排序算法
// 1. 简单选择排序
void SelectSort(int A[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        int min = i;
        for (int j = i + 1; j < n; ++j) {
            if (A[j] < A[min]) {
                min = j;
            }
        }
        if (min != i) {
            swap(A[i], A[min]);
        }
    }
}

// 2. 堆排序
void HeapAdjust(int A[], int k, int len) {
    A[0] = A[k];
    for (int i = 2 * k; i <= len; i *= 2) {
        if (i < len && A[i] < A[i + 1]) {
            ++i;
        }
        if (A[0] >= A[i]) {
            break;
        } else {
            A[k] = A[i];
            k = i;
        }
    }
    A[k] = A[0];
}

void BuildMaxHeap(int A[], int len) {
    for (int i = len / 2; i > 0; --i) {
        HeapAdjust(A, i, len);
    }
}

void HeapSort(int A[], int len) {
    BuildMaxHeap(A, len);
    for (int i = len; i > 1; --i) {
        swap(A[1], A[i]);
        HeapAdjust(A, 1, i - 1);
    }
}
// =============================


// =============================
// 归并排序算法
int n = 1000000;
int *B = new int[n + 1];

void Merge(int A[], int low, int mid, int high) {
    int i, j, k;
    for (k = low; k <= high; k++) {
        B[k] = A[k];
    }
    for (i = low, j = mid + 1, k = i; i <= mid && j <= high; k++) {
        if (B[i] <= B[j]) {
            A[k] = B[i++];
        } else {
            A[k] = B[j++];
        }
    }
    while (i <= mid) {
        A[k++] = B[i++];
    }
    while (j <= high) {
        A[k++] = B[j++];
    }
}

void MergeSort(int A[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        MergeSort(A, low, mid);
        MergeSort(A, mid + 1, high);
        Merge(A, low, mid, high);
    }
}
// =============================
// 基数排序
void RadixSort(int A[], int n) {
    int max = A[0];
    for (int i = 1; i < n; i++) {
        if (A[i] > max) {
            max = A[i];
        }
    }
    int d = 0;
    while (max > 0) {
        max /= 10;
        d++;
    }
    int *tmp = new int[n];
    int *count = new int[10];
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < 10; j++) {
            count[j] = 0;
        }
        for (int j = 0; j < n; j++) {
            int k = (A[j] / static_cast<int>(pow(10, i))) % 10;
            count[k]++;
        }
        for (int j = 1; j < 10; j++) {
            count[j] += count[j - 1];
        }
        for (int j = n - 1; j >= 0; j--) {
            int k = (A[j] / static_cast<int>(pow(10, i))) % 10;
            tmp[count[k] - 1] = A[j];
            count[k]--;
        }
        for (int j = 0; j < n; j++) {
            A[j] = tmp[j];
        }
    }
    delete[] tmp;
    delete[] count;
}
// =============================
// 计数排序
void CountingSort(const int A[], int B[], int n, int k) {
    int *C = new int[k + 1];
    for (int i = 0; i <= k; i++) {
        C[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        C[A[i]]++;
    }
    for (int i = 1; i <= k; i++) {
        C[i] += C[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        B[C[A[i]] - 1] = A[i];
        C[A[i]]--;
    }
    delete[] C;
}
// =============================