#include <iostream>
#include <cstring>
#include <memory>
using namespace std;

// 定长顺序存储
#define MAXLEN 255

typedef struct {
    char ch[MAXLEN];
    int length;
} SString;

// 堆分配存储
typedef struct {
    char *ch;
    int length;
} HString;

// 块链存储表示
struct Chunk {
    char ch[4];
    shared_ptr<Chunk> next;
};

typedef struct {
    shared_ptr<Chunk> first;
    shared_ptr<Chunk> last;
    int length;
} LString;

// 朴素匹配
int Index(const HString S, const HString T) {
    int i = 0, j = 0;
    while (i < S.length && j < T.length) {
        if (S.ch[i] == T.ch[j]) {
            ++i, ++j;
        } else {
            i = i - j + 1, j = 0;
        }
    }
    return j == T.length ? i - T.length : -1;
}

// KMP 辅助函数：计算 next 数组
void GetNext(const HString &T, int *next) {
    int k = next[0] = -1;
    for (int j = 0; j < T.length - 1; ++j) {
        while (k >= 0 && T.ch[k] != T.ch[j]) k = next[k];
        next[j + 1] = ++k;
    }
}

void AdvancedNext(const HString &T, int *next) {
    int k = next[0] = -1;
    for (int j = 0; j < T.length; ++j) {
        while (k >= 0 && T.ch[k] != T.ch[j]) k = next[k];
        next[j + 1] = (T.ch[j + 1] != T.ch[++k]) ? k : next[k];
    }
}

int Index_KMP(const HString S, const HString T) {
    int i = 0, j = 0, *next = new int[T.length];
    GetNext(T, next);
    while (i < S.length && j < T.length) {
        if (j == -1 || S.ch[i] == T.ch[j]) ++i, ++j;
        else j = next[j];
    }
    delete[] next;
    return j == T.length ? i - T.length : -1;
}


int main() {
    HString S;
    S.length = 8;
    S.ch = new char[S.length + 1];
    strcpy(S.ch, "abcabcbb");

    HString T;
    T.length = 6;
    T.ch = new char[T.length + 1];
    strcpy(T.ch, "aabaab");

    // int index = Index(S, T);
    // cout << "朴素匹配位置: " << index << endl;

    int *next = new int[T.length];
    AdvancedNext(T, next);
    for (int i = 0; i < T.length; ++i) {
        cout << next[i] << " ";
    }
    delete[] next;

    // index = Index_KMP(S, T);
    // cout << "KMP 匹配位置: " << index << endl;

    delete[] S.ch;
    delete[] T.ch;
    return 0;
}
