#include <iostream>
#include <stack>
using namespace std;

// 递归方式计算斐波那契数列（效率低）
int Fibonacci_Recursive(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    return Fibonacci_Recursive(n - 1) + Fibonacci_Recursive(n - 2);
}

// 非递归方式计算斐波那契数列（使用循环）
int Fibonacci_Iterative(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    
    int a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

// 非递归方式计算斐波那契数列（使用栈模拟递归）
int Fibonacci_Stack(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    
    stack<pair<int, int>> callStack;  // 存储参数和返回地址
    stack<int> resultStack;           // 存储中间结果
    
    callStack.push({n, 0});  // 初始调用
    
    while (!callStack.empty()) {
        auto [num, state] = callStack.top();
        callStack.pop();
        
        if (num <= 0) {
            resultStack.push(0);
            continue;
        }
        
        if (num == 1) {
            resultStack.push(1);
            continue;
        }
        
        if (state == 0) {
            // 第一次调用，需要计算F(n-1)和F(n-2)
            callStack.push({num, 1});     // 返回地址
            callStack.push({num - 1, 0});  // 计算F(n-1)
        } else {
            // 已经计算了F(n-1)，现在计算F(n-2)
            int result1 = resultStack.top();
            resultStack.pop();
            callStack.push({num, 2});     // 返回地址
            callStack.push({num - 2, 0});  // 计算F(n-2)
        }
    }
    
    return resultStack.top();
}

int main() {
    int n;
    cout << "请输入要计算的斐波那契数列项数: ";
    cin >> n;
    
    cout << "递归方式计算结果: " << Fibonacci_Recursive(n) << endl;
    cout << "非递归方式（循环）计算结果: " << Fibonacci_Iterative(n) << endl;
    cout << "非递归方式（栈模拟）计算结果: " << Fibonacci_Stack(n) << endl;
    
    return 0;
}
