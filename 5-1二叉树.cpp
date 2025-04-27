#include <iostream>
#include <memory>
#include "LinkQueue.h" // 引入队列头文件
using namespace std;

typedef struct BiNode {
    int data;
    shared_ptr<BiNode> lclild, rclild;
} BiNode;

typedef struct ThreadNode {
    int data_t;
    shared_ptr<ThreadNode> lclild, rclild;
    int ltag, rtag;
} ThreadNode;

using BiTree = shared_ptr<BiNode>;
using ThreadTree = shared_ptr<ThreadNode>;

void visit(const BiTree &T) { cout << T->data << " "; }

void PreOrder(const BiTree &T) {
    if (T) {
        visit(T);
        PreOrder(T->lclild);
        PreOrder(T->rclild);
    }
}

void InOrder(const BiTree &T) {
    if (T) {
        InOrder(T->lclild);
        visit(T);
        InOrder(T->rclild);
    }
}

void PostOrder(const BiTree &T) {
    if (T) {
        PostOrder(T->lclild);
        PostOrder(T->rclild);
        visit(T);
    }
}

// 层次遍历实现
void LevelOrder(const BiTree &T) {
    LinkQueue Q;
    InitQueue(Q);
    BiTree p;
    EnQueue(Q, T);
    while (!IsEmpty(Q)) {
        DeQueue(Q, p);
        visit(p);
        if (p->lclild)
            EnQueue(Q, p->lclild);
        if (p->rclild)
            EnQueue(Q, p->rclild);
    }
}


int main() {}
