#ifndef LINKQUEUE_H
#define LINKQUEUE_H

#include <memory>
using namespace std;

// 前向声明BiNode结构体和BiTree类型
struct BiNode;
using BiTree = shared_ptr<BiNode>;

// 定义队列节点结构
struct LinkNode {
    BiTree data; // 存储二叉树节点指针
    shared_ptr<LinkNode> next; // 下一节点智能指针
};

// 定义队列结构
struct LinkQueue {
    shared_ptr<LinkNode> front; // 队首指针（头节点）
    shared_ptr<LinkNode> rear; // 队尾指针
};

// 初始化队列（带头节点的空队列）
void InitQueue(LinkQueue &Q);

// 判断队列是否为空
bool IsEmpty(const LinkQueue &Q);

// 入队操作（在队尾插入）
bool EnQueue(LinkQueue &Q, const BiTree &value);

// 出队操作（从队首删除）
bool DeQueue(LinkQueue &Q, BiTree &value);

// 获取队首元素（不删除）
bool GetFront(const LinkQueue &Q, BiTree &value);

// 清空队列
void ClearQueue(LinkQueue &Q);

// 打印队列（从队首到队尾）
void PrintQueue(const LinkQueue &Q);

#endif // LINKQUEUE_H
