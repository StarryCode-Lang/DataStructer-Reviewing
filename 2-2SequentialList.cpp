#include <memory>
using namespace std;

// 动态分配的顺序表存储结构
#define InitSize 100

typedef struct {
    unique_ptr<int []> data; // 8 字节，当前数组
    int MaxSize{}; //最大容量
    int length{}; //4 + 4 字节，实际长度
} SeqList;

//初始化
void InitList(SeqList &L) {
    L.data = make_unique<int[]>(InitSize);
    L.length = 0;
    L.MaxSize = InitSize;
}

bool ListInsert(SeqList &L, int i, int e) {
    if (i < 1 || i > L.length + 1) {
        return false;
    }
    if (L.length > L.MaxSize) {
        return false;
    }
    for (int j = L.length; j >= i; j--) {
        L.data[j] = L.data[j - 1];
    }
    L.data[i - 1] = e;
    L.length++;
    return true;
}

bool ListDelete(SeqList &L, int i, int &e) {
    if (i < 1 || i > L.length) {
        return false;
    }
    e = L.data[i - 1];
    for (int j = i; j < L.length; ++j) {
        L.data[j - 1] = L.data[j];
    }
    L.length--;
    return true;
}

int LocateElem(const SeqList &L, const int e) {
    for (int i = 0; i < L.length; ++i) {
        if (L.data[i] == e) {
            return i + 1; //第i+1个元素
        }
    }
    return -1; //没有找到
}
