#include <iostream>
#include <memory>
using namespace std;

// 定义队列节点结构
struct LinkNode {
    int data{}; // 数据域，默认初始化为 0
    shared_ptr<LinkNode> next; // 下一节点智能指针
};

// 定义队列结构
struct LinkQueue {
    shared_ptr<LinkNode> front; // 队首指针（头节点）
    shared_ptr<LinkNode> rear; // 队尾指针
};

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
bool EnQueue(LinkQueue &Q, int value) {
    auto newNode = make_shared<LinkNode>(); // 创建新节点
    newNode->data = value;
    newNode->next = nullptr;
    Q.rear->next = newNode; // 原队尾指向新节点
    Q.rear = newNode; // 更新队尾
    cout << "入队元素: " << value << endl;
    return true;
}

// 出队操作（从队首删除）
bool DeQueue(LinkQueue &Q, int &value) {
    if (IsEmpty(Q)) {
        cout << "队列为空，无法出队" << endl;
        return false;
    }
    auto p = Q.front->next; // 获取第一个数据节点
    value = p->data; // 保存出队元素的值
    Q.front->next = p->next; // 更新队首的下一节点
    if (Q.rear == p) {
        // 如果出队的是最后一个节点
        Q.rear = Q.front; // 队尾回到头节点
    }
    cout << "出队元素: " << value << endl;
    return true;
}

// 获取队首元素（不删除）
bool GetFront(const LinkQueue &Q, int &value) {
    if (IsEmpty(Q)) {
        cout << "队列为空，无队首元素" << endl;
        return false;
    }
    value = Q.front->next->data;
    cout << "队首元素: " << value << endl;
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

// 主函数测试
int main() {
    LinkQueue Q;

    // 测试 1：初始化和判空
    cout << "=== 测试 1：初始化和判空 ===" << endl;
    InitQueue(Q);
    cout << "队列是否为空: " << (IsEmpty(Q) ? "是" : "否") << endl;

    // 测试 2：入队操作
    cout << "\n=== 测试 2：入队操作 ===" << endl;
    EnQueue(Q, 1);
    EnQueue(Q, 2);
    EnQueue(Q, 3);
    PrintQueue(Q);

    // 测试 3：获取队首元素
    cout << "\n=== 测试 3：获取队首元素 ===" << endl;
    int frontValue;
    GetFront(Q, frontValue);

    // 测试 4：出队操作
    cout << "\n=== 测试 4：出队操作 ===" << endl;
    int dequeuedValue;
    DeQueue(Q, dequeuedValue);
    PrintQueue(Q);
    DeQueue(Q, dequeuedValue);
    PrintQueue(Q);

    // 测试 5：清空队列
    cout << "\n=== 测试 5：清空队列 ===" << endl;
    ClearQueue(Q);
    PrintQueue(Q);

    return 0;
}
