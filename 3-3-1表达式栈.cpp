#include <iostream>
#include <memory>
#include <string>
#include <cctype>
#include <stdexcept>
#include <unordered_map>
using namespace std;

// 栈节点结构
struct LinkNode {
    char data{}; // 操作符、括号或操作数
    shared_ptr<LinkNode> next; // 下一节点
};

// 类型别名
using LiStack = shared_ptr<LinkNode>;

// 栈操作
void InitStack(LiStack &Lhead) {
    Lhead = nullptr;
    cout << "Initialized" << endl;
}

bool IsEmpty(const LiStack &Lhead) {
    return Lhead == nullptr;
}

bool Push(LiStack &Lhead, const char &value) {
    auto newNode = make_shared<LinkNode>();
    newNode->data = value;
    newNode->next = Lhead;
    Lhead = newNode;
    return true;
}

bool Pop(LiStack &Lhead, char &value) {
    if (IsEmpty(Lhead)) {
        cout << "Empty Stack Error" << endl;
        return false;
    }
    value = Lhead->data;
    Lhead = Lhead->next;
    return true;
}

bool GetTop(const LiStack &Lhead, char &value) {
    if (IsEmpty(Lhead)) {
        cout << "Empty Stack Error" << endl;
        return false;
    }
    value = Lhead->data;
    return true;
}

void PrintStack(const LiStack &Lhead) {
    if (IsEmpty(Lhead)) {
        cout << "Empty Stack Error" << endl;
        return;
    }
    cout << "The whole stack: ";
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

// 括号匹配映射和优先级
const unordered_map<char, char> bracket_pairs = {
    {')', '('},
    {'}', '{'},
    {']', '['}
};

const unordered_map<char, int> bracket_priority = {
    {'(', 0}, {')', 0},
    {'{', 1}, {'}', 1},
    {'[', 2}, {']', 2}
};

// 操作符优先级
int Precedence(char op) {
    switch (op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        default: return 0; // 非操作符或括号
    }
}

// 检查括号匹配
bool IsBracketMatched(const string &expr) {
    LiStack s;
    InitStack(s);
    for (char c: expr) {
        if (isspace(c)) continue;
        if (c == '(' || c == '{' || c == '[') {
            Push(s, c);
        } else if (c == ')' || c == '}' || c == ']') {
            char top;
            if (!Pop(s, top) || top != bracket_pairs.at(c)) {
                return false;
            }
        }
    }
    return IsEmpty(s);
}

// 中缀转后缀
string InfixToPostfix(const string &infix) {
    if (!IsBracketMatched(infix)) {
        throw runtime_error("括号不匹配");
    }

    LiStack s;
    InitStack(s);
    string postfix;

    for (char c: infix) {
        if (isspace(c)) continue;
        if (isdigit(c)) {
            postfix += c;
        } else if (c == '(' || c == '{' || c == '[') {
            Push(s, c);
        } else if (c == ')' || c == '}' || c == ']') {
            char op;
            while (Pop(s, op) && op != bracket_pairs.at(c)) {
                postfix += op;
            }
        } else {
            char top;
            while (!IsEmpty(s) && GetTop(s, top) && Precedence(top) >= Precedence(c) &&
                   bracket_priority.at(top) <= bracket_priority.at(c)) {
                Pop(s, top);
                postfix += top;
            }
            Push(s, c);
        }
    }

    char op;
    while (Pop(s, op)) {
        if (op == '(' || op == '{' || op == '[') {
            throw runtime_error("未匹配的左括号");
        }
        postfix += op;
    }

    return postfix;
}

// 后缀表达式求值
int EvaluatePostfix(const string &postfix) {
    LiStack s;
    InitStack(s);

    for (char c: postfix) {
        if (isdigit(c)) {
            Push(s, c - '0');
        } else {
            char b, a;
            if (!Pop(s, b) || !Pop(s, a)) {
                throw runtime_error("无效的后缀表达式");
            }
            switch (c) {
                case '+': Push(s, a + b);
                    break;
                case '-': Push(s, a - b);
                    break;
                case '*': Push(s, a * b);
                    break;
                case '/':
                    if (b == 0) throw runtime_error("除零错误");
                    Push(s, a / b);
                    break;
                default: throw runtime_error("未知操作符");
            }
        }
    }

    char result;
    if (!Pop(s, result) || !IsEmpty(s)) {
        throw runtime_error("无效的后缀表达式");
    }
    return result;
}

// 测试函数
void TestExpressionEvaluation() {
    struct TestCase {
        string infix;
        int expected;
        bool should_fail;
    };

    TestCase tests[] = {
        {"3 + 4 * 2", 11, false},
        {"{5 + 3} * 2", 16, false},
        {"[8 - 2] + 3", 9, false},
        {"6 / (2 + 1)", 2, false},
        {"(3 + 4", 0, true},
        {"{3 * 2] + 1", 0, true},
        {"5 / 0", 0, true},
    };

    for (const auto &test: tests) {
        cout << "测试中缀: " << test.infix << endl;
        try {
            string postfix = InfixToPostfix(test.infix);
            int result = EvaluatePostfix(postfix);
            if (test.should_fail) {
                cout << "错误: 预期失败但通过 (结果: " << result << ")\n";
                continue;
            }
            cout << "后缀: " << postfix << " -> 结果: " << result
                    << " (预期: " << test.expected << ")\n";
            if (result != test.expected) {
                cout << "测试失败!\n";
            }
        } catch (const exception &e) {
            if (test.should_fail) {
                cout << "通过: 正确捕获错误 - " << e.what() << endl;
            } else {
                cout << "失败: " << e.what() << endl;
            }
        }
        cout << endl;
    }
}

// 主函数
int main() {
    cout << "请输入中缀表达式（支持 (), {}, [], 单数字, +-*/）：";
    string infix;
    getline(cin, infix);

    try {
        string postfix = InfixToPostfix(infix);
        int result = EvaluatePostfix(postfix);
        cout << "后缀表达式: " << postfix << endl;
        cout << "计算结果: " << result << endl;
    } catch (const exception &e) {
        cout << "错误: " << e.what() << endl;
    }

    cout << "\n=== 运行测试 ===\n";
    TestExpressionEvaluation();

    return 0;
}
