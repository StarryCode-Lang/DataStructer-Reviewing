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
