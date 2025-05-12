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
