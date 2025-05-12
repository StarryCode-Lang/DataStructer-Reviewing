#include <iostream>
#include <stack>
#include <string>
#include <cctype>
using namespace std;

// 判断运算符优先级
int Priority(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

// 执行二元运算
double Calculate(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: return 0;
    }
}

// 中缀表达式求值
double EvaluateInfix(const string& expression) {
    stack<double> numStack;  // 操作数栈
    stack<char> opStack;     // 运算符栈
    
    for (size_t i = 0; i < expression.length(); i++) {
        char c = expression[i];
        
        if (isspace(c)) {
            continue;  // 跳过空白字符
        } else if (isdigit(c) || c == '.') {
            // 解析数字
            string numStr;
            while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.')) {
                numStr += expression[i++];
            }
            i--;  // 回退一位，因为for循环会自增
            numStack.push(stod(numStr));
        } else if (c == '(') {
            opStack.push(c);
        } else if (c == ')') {
            // 处理括号内的运算
            while (!opStack.empty() && opStack.top() != '(') {
                char op = opStack.top(); opStack.pop();
                double b = numStack.top(); numStack.pop();
                double a = numStack.top(); numStack.pop();
                numStack.push(Calculate(a, b, op));
            }
            if (!opStack.empty()) opStack.pop();  // 弹出左括号
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            // 处理运算符
            while (!opStack.empty() && opStack.top() != '(' && Priority(opStack.top()) >= Priority(c)) {
                char op = opStack.top(); opStack.pop();
                double b = numStack.top(); numStack.pop();
                double a = numStack.top(); numStack.pop();
                numStack.push(Calculate(a, b, op));
            }
            opStack.push(c);
        }
    }
    
    // 处理剩余的运算符
    while (!opStack.empty()) {
        char op = opStack.top(); opStack.pop();
        double b = numStack.top(); numStack.pop();
        double a = numStack.top(); numStack.pop();
        numStack.push(Calculate(a, b, op));
    }
    
    return numStack.top();
}

// 中缀转后缀表达式
string InfixToPostfix(const string& infix) {
    string postfix;
    stack<char> opStack;
    
    for (char c : infix) {
        if (isspace(c)) {
            continue;
        } else if (isdigit(c) || c == '.') {
            postfix += c;
        } else if (c == '(') {
            opStack.push(c);
        } else if (c == ')') {
            while (!opStack.empty() && opStack.top() != '(') {
                postfix += ' ';
                postfix += opStack.top();
                opStack.pop();
            }
            if (!opStack.empty()) opStack.pop();  // 弹出左括号
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            postfix += ' ';  // 分隔数字和运算符
            while (!opStack.empty() && opStack.top() != '(' && Priority(opStack.top()) >= Priority(c)) {
                postfix += opStack.top();
                postfix += ' ';
                opStack.pop();
            }
            opStack.push(c);
        }
    }
    
    while (!opStack.empty()) {
        postfix += ' ';
        postfix += opStack.top();
        opStack.pop();
    }
    
    return postfix;
}

// 后缀表达式求值
double EvaluatePostfix(const string& postfix) {
    stack<double> numStack;
    string numStr;
    
    for (size_t i = 0; i < postfix.length(); i++) {
        char c = postfix[i];
        
        if (isspace(c)) {
            if (!numStr.empty()) {
                numStack.push(stod(numStr));
                numStr.clear();
            }
        } else if (isdigit(c) || c == '.') {
            numStr += c;
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            if (!numStr.empty()) {
                numStack.push(stod(numStr));
                numStr.clear();
            }
            
            double b = numStack.top(); numStack.pop();
            double a = numStack.top(); numStack.pop();
            numStack.push(Calculate(a, b, c));
        }
    }
    
    if (!numStr.empty()) {
        numStack.push(stod(numStr));
    }
    
    return numStack.top();
}

int main() {
    string expression;
    cout << "请输入中缀表达式: ";
    getline(cin, expression);
    
    cout << "中缀表达式: " << expression << endl;
    cout << "后缀表达式: " << InfixToPostfix(expression) << endl;
    cout << "计算结果: " << EvaluateInfix(expression) << endl;
    
    return 0;
}
