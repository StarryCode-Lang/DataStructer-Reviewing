#include <iostream>
#include <memory>
using namespace std;

struct Linknode {
    int data{};
    shared_ptr<Linknode> next;
};

using LiStack = shared_ptr<Linknode>; // 为Linknode起别名，后面函数可以直接用LiStack &Lhead，而不是shared_ptr<LinkNode>& Lhead

void InitStack(LiStack &Lhead) {
    Lhead = nullptr;
    cout << "Initialized" << endl;
}

bool IsEmpty(const LiStack &Lhead) {
    return Lhead == nullptr;
}

bool Push(LiStack &Lhead, const int &value) {
    auto newNode = make_shared<Linknode>(); //make_shared：用于创建 shared_ptr 管理的对象
    // 等价于：shared_ptr<LinkNode> newNode(new LinkNode());
    newNode->data = value;
    newNode->next = Lhead;
    Lhead = newNode;
    return true;
}

bool Pop(LiStack &Lhead, int &value) {
    if (IsEmpty(Lhead)) {
        cout << "Empty Stack Error" << endl;
        return false;
    }
    value = Lhead->data;
    Lhead = Lhead->next;
    cout << "pop stack:" << value << endl;
    return true;
}

bool GetTop(const LiStack &Lhead, int &value) {
    if (IsEmpty(Lhead)) {
        cout << "Empty Stack Error" << endl;
        return false;
    }
    value = Lhead->data;
    cout << "stack's top:" << value << endl;
    return true;
}

void PrintStack(const LiStack &Lhead) {
    if (IsEmpty(Lhead)) {
        cout << "Empty Stack Error" << endl;
        return;
    }
    cout << "The whole stack:" << endl;
    auto p = Lhead;
    while (p) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

void ClearStack(LiStack &Lhead) {
    Lhead = nullptr;
    cout << "emptied" << endl;
}

// int main() {
//     LiStack Lhead;
//
//     // 测试 1：初始化和判空
//     cout << "=== 测试 1：初始化和判空 ===" << endl;
//     InitStack(Lhead);
//     cout << "栈是否为空: " << (IsEmpty(Lhead) ? "是" : "否") << endl;
//
//     // 测试 2：入栈操作
//     cout << "\n=== 测试 2：入栈操作 ===" << endl;
//     Push(Lhead, 1); // 栈: 1
//     Push(Lhead, 2); // 栈: 2 -> 1
//     Push(Lhead, 3); // 栈: 3 -> 2 -> 1
//     PrintStack(Lhead);
//
//     // 测试 3：获取栈顶元素
//     cout << "\n=== 测试 3：获取栈顶元素 ===" << endl;
//     int topValue;
//     GetTop(Lhead, topValue);
//
//     // 测试 4：出栈操作
//     cout << "\n=== 测试 4：出栈操作 ===" << endl;
//     int popValue;
//     Pop(Lhead, popValue); // 出栈 3，栈: 2 -> 1
//     PrintStack(Lhead);
//     Pop(Lhead, popValue); // 出栈 2，栈: 1
//     PrintStack(Lhead);
//
//     // 测试 5：清空栈
//     cout << "\n=== 测试 5：清空栈 ===" << endl;
//     ClearStack(Lhead);
//     cout << "栈是否为空: " << (IsEmpty(Lhead) ? "是" : "否") << endl;
//     Pop(Lhead, popValue); // 尝试从空栈出栈
//
//     return 0;
// }
