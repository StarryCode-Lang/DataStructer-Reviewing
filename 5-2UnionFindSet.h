#ifndef UNION_FIND_SET_H
#define UNION_FIND_SET_H

#include <iostream>

#define SIZE 100
extern int UFSets[SIZE]; // 并查集集合元素数组

// 初始化操作：将并查集初始化为每个元素自成一个集合
inline void Initial(int S[]) {
    for (int i = 0; i < SIZE; i++) // 每个元素的父节点初始化为-1，表示其为根节点且集合大小为1
        S[i] = -1;
}

// 查找操作：查找元素x所在集合的根节点，并进行路径压缩
inline int Find(int S[], int x) {
    int root = x; // 从元素x开始向上查找根节点
    while (S[root] >= 0) { // 如果当前节点不是根节点，继续向上查找
        root = S[root];
    }
    while (x != root) { // 路径压缩，将沿途节点直接连接到根节点
        int t = S[x];
        S[x] = root;
        x = t;
    }
    return root; // 返回根节点
}

// 合并操作：将两个集合合并为一个集合
inline void Union(int S[], int Root1, int Root2) {
    if (Root1 == Root2) // 如果两个集合已经属于同一集合，则无需合并
        return;
    if (S[Root1] < S[Root2]) { // 如果Root1所在集合的节点数更多
        S[Root1] += S[Root2]; // 更新Root1的集合大小
        S[Root2] = Root1; // 将Root2连接到Root1
    } else { // 如果Root2所在集合的节点数更多或相等
        S[Root2] += S[Root1]; // 更新Root2的集合大小
        S[Root1] = Root2; // 将Root1连接到Root2
    }
}

// 检查两个元素是否在同一个集合中
inline bool InSameSet(int S[], int x, int y) {
    return Find(S, x) == Find(S, y);
}

// 获取集合的大小
inline int SetSize(int S[], int x) {
    int root = Find(S, x);
    return -S[root]; // 集合大小存储为负数
}

// 获取集合的数量
inline int CountSets(int S[], int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (S[i] < 0) { // 如果是根节点
            count++;
        }
    }
    return count;
}

#endif // UNION_FIND_SET_H
