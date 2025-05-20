#include <iostream>
using namespace std;

typedef struct {
    int *elem;
    int TableLen;
} SSTable;


int Search_Seq(const SSTable ST, const int key) {
    int i;
    ST.elem[0] = key;
    for (i = ST.TableLen; ST.elem[i] != key; --i) {
    }
    return i;
}
int Binary_Seq(const SSTable ST, const int key) {
    int low = 0, high = ST.TableLen;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (ST.elem[mid] == key) {
            return mid;
        }
        if (ST.elem[mid] > key) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;
}
