#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;

// 定义一个简单的计数器类
class Counter {
private:
    int value; // 计数器值
    mutable mutex mtx; // 可变的互斥锁，用于保护 value 的访问

public:
    explicit Counter(int initialValue = 0) : value(initialValue) {
    }

    // 增加计数器值，线程安全
    void increment() {
        lock_guard<mutex> lock(mtx); // 自动加锁和解锁
        value++;
    }

    // 获取当前值，线程安全
    int getValue() const {
        lock_guard<mutex> lock(mtx);
        return value;
    }

    // 析构函数，用于验证对象销毁
    ~Counter() {
        cout << "Counter 对象被销毁，结束值: " << value << endl;
    }
};

// 线程函数，接收 shared_ptr 并操作计数器
void threadFunction(const shared_ptr<Counter> &counter, int threadId, int increments) {
    for (int i = 0; i < increments; ++i) {
        counter->increment(); // 增加计数器
        cout << "线程 " << threadId << " 增加计数器，当前值: " << counter->getValue() << endl;
        this_thread::sleep_for(chrono::milliseconds(10)); // 模拟工作，增加竞争
    }
}

int main() {
    constexpr int NUM_THREADS = 4; // 线程数量

    // 创建共享的 Counter 对象
    auto counter = make_shared<Counter>(0);
    cout << "初始计数器值: " << counter->getValue() << endl;
    cout << "初始引用计数: " << counter.use_count() << endl;

    // 创建线程容器
    vector<thread> threads;

    // 启动多个线程，共享同一个 counter 对象
    for (int i = 0; i < NUM_THREADS; ++i) {
        constexpr int INCREMENTS = 5;
        threads.emplace_back(threadFunction, counter, i + 1, INCREMENTS);
        cout << "线程 " << (i + 1) << " 已启动，引用计数: " << counter.use_count() << endl;
    }

    // 等待所有线程完成
    for (auto &t: threads) {
        t.join();
    }

    // 所有线程完成后，检查最终值
    cout << "所有线程完成，最终计数器值: " << counter->getValue() << endl;
    cout << "main 中引用计数: " << counter.use_count() << endl;

    // counter 离开作用域时自动销毁
    return 0;
}
