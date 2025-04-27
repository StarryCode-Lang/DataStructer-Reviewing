#include <iostream>
#include <memory>
#include "LinkQueue.h" // 引入队列头文件
using namespace std;

typedef struct BiNode {
    int data;
    shared_ptr<BiNode> lchild, rchild;
} BiNode;

typedef struct ThreadNode {
    int data_t;
    shared_ptr<ThreadNode> lchild, rchild;
    int ltag, rtag;
} ThreadNode;

using BiTree = shared_ptr<BiNode>;
using ThreadTree = shared_ptr<ThreadNode>;

void visit(const auto &T) { cout << T->data << " "; }

void InThread(ThreadTree &p, ThreadTree &pre) {
    if (p) {
        InThread(p->lchild, pre);
        if (!p->lchild) {
            p->lchild = pre;
            p->ltag = 1;
        }
        if (pre && !pre->rchild) {
            pre->rchild = p;
            pre->rtag = 1;
        }
        pre = p;
        InThread(p->rchild, pre);
    }
}

void CreateInThread(ThreadTree &T) {
    ThreadTree pre = nullptr;
    if (T) {
        InThread(T, pre);
        pre->rtag = 1;
        pre->rchild = nullptr;
    }
}

shared_ptr<ThreadNode> FirstInNode(shared_ptr<ThreadNode> p) {
    while (p->ltag == 0)
        p = p->lchild;
    return p;
}

shared_ptr<ThreadNode> LastInNode(shared_ptr<ThreadNode> p) {
    while (p->rtag == 0)
        p = p->rchild;
    return p;
}

shared_ptr<ThreadNode> NextInOrder(const shared_ptr<ThreadNode> &p) {
    if (p->rtag == 1)
        return p->rchild;
    return NextInOrder(p->rchild);
}

shared_ptr<ThreadNode> PrevInOrder(const shared_ptr<ThreadNode> &p) {
    if (p->ltag == 1)
        return p->lchild;
    return PrevInOrder(p->lchild);
}

void ThreadInOrder(const shared_ptr<ThreadNode> &t) {
    for (shared_ptr<ThreadNode> p = FirstInNode(t); t; p = NextInOrder(t)) {
        visit(p);
    }
}

void PreOrder(const BiTree &T) {
    if (T) {
        visit(T);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}

void InOrder(const BiTree &T) {
    if (T) {
        InOrder(T->lchild);
        visit(T);
        InOrder(T->rchild);
    }
}

void PostOrder(const BiTree &T) {
    if (T) {
        PostOrder(T->lchild);
        PostOrder(T->rchild);
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
        if (p->lchild)
            EnQueue(Q, p->lchild);
        if (p->rchild)
            EnQueue(Q, p->rchild);
    }
}


int main() {}
