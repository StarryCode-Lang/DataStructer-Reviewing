#include <iostream>
#include <memory>
#include <vector>
#include <stdexcept>
using namespace std;

// 单链表节点结构
struct LNode {
    int data{}; // 数据域，初始化为 0
    shared_ptr<LNode> next; // 下一节点指针
};

// 链表类型别名
using LinkList = shared_ptr<LNode>;

// 初始化空链表
bool InitList(LinkList &L) {
    L = make_shared<LNode>(); // 创建头节点
    L->next = nullptr;
    return true;
}

// 获取链表长度（不含头节点）
int Length(const LinkList &L) {
    int len = 0;
    auto p = L->next;
    while (p) {
        len++;
        p = p->next;
    }
    return len;
}

// 判断链表是否为空
bool IsEmpty(const LinkList &L) {
    return L->next == nullptr;
}

// 获取第 i 个节点（0 为头节点，1 为第一个数据节点）
shared_ptr<LNode> GetElem(const LinkList &L, int i) {
    if (i < 0) return nullptr;
    auto p = L;
    int j = 0;
    while (p && j < i) {
        p = p->next;
        j++;
    }
    return p;
}

// 按值查找第一个匹配的节点
shared_ptr<LNode> LocateElem(const LinkList &L, int e) {
    auto p = L->next;
    while (p && p->data != e) {
        p = p->next;
    }
    return p;
}

// 在第 i 个位置插入节点（1 基索引）
bool ListInsert(LinkList &L, int i, int e) {
    if (i < 1) return false;
    auto p = GetElem(L, i - 1);
    if (!p) return false;
    auto s = make_shared<LNode>();
    s->data = e;
    s->next = p->next;
    p->next = s;
    return true;
}

// 删除第 i 个节点（1 基索引）
bool ListDelete(LinkList &L, int i) {
    if (i < 1 || IsEmpty(L)) return false;
    auto p = GetElem(L, i - 1);
    if (!p || !p->next) return false;
    p->next = p->next->next; // 智能指针自动释放被删除节点
    return true;
}

// 删除第一个值为 e 的节点
bool DeleteByValue(LinkList &L, int e) {
    auto p = L;
    while (p->next && p->next->data != e) {
        p = p->next;
    }
    if (!p->next) return false;
    p->next = p->next->next;
    return true;
}

// 清空链表
void ClearList(LinkList &L) {
    L->next = nullptr; // 智能指针自动释放所有节点
}

// 头插法创建链表
void List_HeadInsert(LinkList &L, const vector<int> &values) {
    InitList(L);
    for (auto it = values.rbegin(); it != values.rend(); ++it) {
        auto s = make_shared<LNode>();
        s->data = *it;
        s->next = L->next;
        L->next = s;
    }
}

// 尾插法创建链表
void List_TailInsert(LinkList &L, const vector<int> &values) {
    InitList(L);
    auto tail = L;
    for (int x: values) {
        auto s = make_shared<LNode>();
        s->data = x;
        tail->next = s;
        tail = s;
    }
}

// 反转链表（迭代法）
void ReverseList(LinkList &L) {
    shared_ptr<LNode> prev = nullptr;
    auto curr = L->next;
    while (curr) {
        auto next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    L->next = prev;
}

// 合并两个有序链表（升序）
LinkList MergeSortedLists(const LinkList &L1, const LinkList &L2) {
    LinkList L;
    InitList(L);
    auto p1 = L1->next;
    auto p2 = L2->next;
    auto tail = L;
    while (p1 && p2) {
        if (p1->data <= p2->data) {
            tail->next = p1;
            p1 = p1->next;
        } else {
            tail->next = p2;
            p2 = p2->next;
        }
        tail = tail->next;
    }
    tail->next = p1 ? p1 : p2; // 剩余部分直接接上
    return L;
}

// 检测链表是否有环（快慢指针法）
bool HasCycle(const LinkList &L) {
    auto slow = L->next;
    auto fast = L->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

// 打印链表
void PrintList(const LinkList &L) {
    auto p = L->next;
    if (!p) {
        cout << "链表为空" << endl;
        return;
    }
    while (p) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

// 测试模块
void RunTests() {
    // 测试 1：初始化与基本操作
    cout << "=== 测试 1：初始化与基本操作 ===" << endl;
    LinkList L1;
    InitList(L1);
    cout << "初始化后是否为空: " << (IsEmpty(L1) ? "是" : "否") << endl;
    cout << "长度: " << Length(L1) << endl;
    for (int i = 1; i <= 5; i++) ListInsert(L1, i, i * 10);
    cout << "插入 10 20 30 40 50 后: ";
    PrintList(L1);
    ListDelete(L1, 3);
    cout << "删除第 3 个节点后: ";
    PrintList(L1);
    auto node = LocateElem(L1, 40);
    cout << "查找 40: " << (node ? "找到，值=" + to_string(node->data) : "未找到") << endl;

    // 测试 2：头插法与尾插法
    cout << "\n=== 测试 2：头插法与尾插法 ===" << endl;
    LinkList L2, L3;
    vector<int> vals = {1, 2, 3, 4, 5};
    List_HeadInsert(L2, vals);
    cout << "头插法 {1, 2, 3, 4, 5}: ";
    PrintList(L2);
    List_TailInsert(L3, vals);
    cout << "尾插法 {1, 2, 3, 4, 5}: ";
    PrintList(L3);

    // 测试 3：反转链表
    cout << "\n=== 测试 3：反转链表 ===" << endl;
    cout << "反转前: ";
    PrintList(L3);
    ReverseList(L3);
    cout << "反转后: ";
    PrintList(L3);

    // 测试 4：合并有序链表
    cout << "\n=== 测试 4：合并有序链表 ===" << endl;
    LinkList L4, L5;
    vector<int> v1 = {1, 3, 5}, v2 = {2, 4, 6};
    List_TailInsert(L4, v1);
    List_TailInsert(L5, v2);
    cout << "L4: ";
    PrintList(L4);
    cout << "L5: ";
    PrintList(L5);
    auto L6 = MergeSortedLists(L4, L5);
    cout << "合并后: ";
    PrintList(L6);

    // 测试 5：检测环与清空
    cout << "\n=== 测试 5：检测环与清空 ===" << endl;
    LinkList L7;
    InitList(L7);
    ListInsert(L7, 1, 1);
    ListInsert(L7, 2, 2);
    auto last = GetElem(L7, 2);
    last->next = L7->next; // 人为制造环
    cout << "是否有环: " << (HasCycle(L7) ? "是" : "否") << endl;
    ClearList(L7);
    cout << "清空后: ";
    PrintList(L7);
}

// int main() {
//     try {
//         RunTests();
//     } catch (const exception &e) {
//         cerr << "发生异常: " << e.what() << endl;
//     }
//     return 0;
// }
