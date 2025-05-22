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
void BinaryInsertSort(int A[], int n) {}


// 3. 希尔排序
void ShellSort(int A[], int n);


// =============================
