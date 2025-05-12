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
    if (j >= T.length)
        return i - T.length;
    else
        return -1;
}

// KMP算法
void get_next(const HString T, int next[]) {
    int i = 0, j = -1;
    next[0] = -1;
    while (i < T.length - 1) {
        if (j == -1 || T.ch[i] == T.ch[j]) {
            ++i, ++j;
            next[i] = j;
        } else {
            j = next[j];
        }
    }
}

// KMP优化
void get_nextval(const HString T, int nextval[]) {
    int i = 0, j = -1;
    nextval[0] = -1;
    while (i < T.length - 1) {
        if (j == -1 || T.ch[i] == T.ch[j]) {
            ++i, ++j;
            if (T.ch[i] != T.ch[j])
                nextval[i] = j;
            else
                nextval[i] = nextval[j];
        } else {
            j = nextval[j];
        }
    }
}

int KMP(const HString S, const HString T, int next[]) {
    int i = 0, j = 0;
    while (i < S.length && j < T.length) {
        if (j == -1 || S.ch[i] == T.ch[j]) {
            ++i, ++j;
        } else {
            j = next[j];
        }
    }
    if (j >= T.length)
        return i - T.length;
    else
        return -1;
}
