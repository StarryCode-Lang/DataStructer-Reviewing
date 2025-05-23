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
