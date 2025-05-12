#include <iostream>
#include <memory>
#include "LinkQueue.h"
using namespace std;

// 初始化队列（带头节点的空队列）
void InitQueue(LinkQueue &Q) {
    Q.front = make_shared<LinkNode>(); // 创建头节点
    Q.front->next = nullptr;
    Q.rear = Q.front; // 队尾指向头节点
    cout << "队列已初始化" << endl;
}

// 判断队列是否为空
bool IsEmpty(const LinkQueue &Q) {
    return Q.front == Q.rear; // 队首等于队尾表示空队列
}

// 入队操作（在队尾插入）
bool EnQueue(LinkQueue &Q, const BiTree &value) {
    auto newNode = make_shared<LinkNode>(); // 创建新节点
    newNode->data = value;
    newNode->next = nullptr;
    Q.rear->next = newNode; // 原队尾指向新节点
    Q.rear = newNode; // 更新队尾
    cout << "入队元素: " << value << endl;
    return true;
}

// 打印队列（从队首到队尾）
void PrintQueue(const LinkQueue &Q) {
    if (IsEmpty(Q)) {
        cout << "队列为空" << endl;
        return;
    }
    cout << "队列内容（从首到尾）: ";
    auto p = Q.front->next; // 从第一个数据节点开始
    while (p) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

// 清空队列
void ClearQueue(LinkQueue &Q) {
    Q.front->next = nullptr; // 断开数据节点，自动释放
    Q.rear = Q.front; // 队尾回到头节点
    cout << "队列已清空" << endl;
}
