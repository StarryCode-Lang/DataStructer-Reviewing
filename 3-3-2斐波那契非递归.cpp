#include <iostream>
#include <stack>
using namespace std;

int Fibonacci(int n) {
    if (n < 2) {
        cout << "Fib(" << n << ") = " << n << "（直接返回）" << endl;
        return n;
    }

    stack<int> s;
    s.push(n);
    int result = 0;

    cout << "开始非递归计算 Fib(" << n << ")：\n";
    while (!s.empty()) {
        int x = s.top();
        s.pop();
        cout << "  出栈: Fib(" << x << ")\n";
        if (x < 2) {
            cout << "    是基本项，Fib(" << x << ") = " << x << "，累加到结果\n";
            result += x;
        } else {
            cout << "    拆分: Fib(" << x << ") = Fib(" << x - 1 << ") + Fib(" << x - 2 << ")\n";
            s.push(x - 1);
            s.push(x - 2);
            cout << "    入栈: Fib(" << x - 2 << "), Fib(" << x - 1 << ")\n";
        }
    }

    cout << "计算结束，Fib(" << n << ") = " << result << endl;
    return result;
}

int main() {
    int n;
    cout << "请输入 n：";
    cin >> n;
    Fibonacci(n);
    return 0;
}
