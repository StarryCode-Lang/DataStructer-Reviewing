#include <iostream>
#include <memory>
#include "LinkQueue.h" // 引入队列头文件
using namespace std;

typedef struct BiNode {
    int data;
    shared_ptr<BiNode> lclild, rclild;
} BiNode;

using BiTree = shared_ptr<BiNode>;

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
    if (!T)
        return; // 空树直接返回

    LinkQueue Q; // 创建队列
    InitQueue(Q); // 初始化队列

    // 根节点入队
    EnQueue(Q, T);

    // 队列不为空时循环处理
    BiTree node;
    while (!IsEmpty(Q)) {
        // 出队一个节点并访问
        DeQueue(Q, node);
        visit(node);

        // 左子树不为空，入队
        if (node->lclild) {
            EnQueue(Q, node->lclild);
        }

        // 右子树不为空，入队
        if (node->rclild) {
            EnQueue(Q, node->rclild);
        }
    }
}
