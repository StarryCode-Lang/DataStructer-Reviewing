#include <iomanip>
#include <iostream>
#include <stack>
#include <vector>
#include "6-0GraphDefinition.h"

using namespace std;

// 活动信息结构体
struct Activity {
    int from; // 起点
    int to; // 终点
    int weight; // 持续时间
    int ee; // 最早开始时间
    int el; // 最迟开始时间
    int slack; // 时间余量
};

bool TopologicalOrder(const ALGraph &G, vector<int> &ve, stack<int> &T) {
    vector<int> inDegree(G.vexnum, 0);
    // 统计入度
    for (int i = 0; i < G.vexnum; i++) {
        for (ArcNode *p = G.vertices[i].firstarc; p; p = p->nextarc) {
            inDegree[p->adjvex]++;
        }
    }

    stack<int> S;
    // 入度为0的顶点入栈
    for (int i = 0; i < G.vexnum; i++) {
        if (inDegree[i] == 0) {
            S.push(i);
        }
    }

    int count = 0;
    ve.assign(G.vexnum, 0); // 初始化最早发生时间

    while (!S.empty()) {
        int j = S.top();
        S.pop();
        T.push(j);
        count++;

        for (ArcNode *p = G.vertices[j].firstarc; p; p = p->nextarc) {
            int k = p->adjvex;
            if (--inDegree[k] == 0) {
                S.push(k);
            }
            if (ve[j] + p->weight > ve[k]) {
                ve[k] = ve[j] + p->weight;
            }
        }
    }
    return count == G.vexnum;
}

void CriticalPath(const ALGraph &G) {
    vector<int> ve; // 事件的最早发生时间
    vector<int> vl; // 事件的最迟发生时间
    vector<Activity> acts; // 活动信息
    stack<int> T; // 拓扑序列栈

    // 1. 计算事件的最早发生时间ve[]
    if (!TopologicalOrder(G, ve, T)) {
        cout << "图中存在环，无法计算关键路径！" << endl;
        return;
    }

    // 2. 初始化事件的最迟发生时间vl[]
    vl.assign(G.vexnum, ve[G.vexnum - 1]);

    // 3. 按拓扑逆序计算vl[]
    while (!T.empty()) {
        int j = T.top();
        T.pop();
        for (ArcNode *p = G.vertices[j].firstarc; p; p = p->nextarc) {
            int k = p->adjvex;
            if (vl[k] - p->weight < vl[j]) {
                vl[j] = vl[k] - p->weight;
            }
        }
    }

    // 4. 收集所有活动信息
    for (int j = 0; j < G.vexnum; j++) {
        for (ArcNode *p = G.vertices[j].firstarc; p; p = p->nextarc) {
            Activity act{};
            act.from = j;
            act.to = p->adjvex;
            act.weight = p->weight;
            act.ee = ve[j]; // 活动最早开始时间
            act.el = vl[p->adjvex] - p->weight; // 活动最迟开始时间
            act.slack = act.el - act.ee; // 时间余量
            acts.push_back(act);
        }
    }

    // 5. 输出结果
    // 5.1 输出事件的最早和最迟发生时间
    cout << "\n事件的最早和最迟发生时间：" << endl;
    cout << setw(8) << "事件" << setw(8) << "Ve" << setw(8) << "Vl" << endl;
    cout << "------------------------" << endl;
    for (int i = 0; i < G.vexnum; i++) {
        cout << setw(8) << G.vertices[i].data << setw(8) << ve[i] << setw(8) << vl[i] << endl;
    }

    // 5.2 输出活动的各个时间参数
    cout << "\n活动的时间参数：" << endl;
    cout << setw(8) << "活动" << setw(8) << "持续时间" << setw(8) << "e(i)" << setw(8) << "l(i)" << setw(8)
         << "l(i)-e(i)" << endl;
    cout << "----------------------------------------" << endl;

    for (const auto &act: acts) {
        cout << setw(6) << G.vertices[act.from].data << "->" << setw(4) << G.vertices[act.to].data << setw(8)
             << act.weight << setw(8) << act.ee << setw(8) << act.el << setw(8) << act.slack << endl;
    }

    // 5.3 输出关键活动
    cout << "\n关键活动（时间余量为0的活动）：" << endl;
    cout << "活动\t持续时间" << endl;
    cout << "----------------" << endl;
    for (const auto &act: acts) {
        if (act.slack == 0) {
            cout << G.vertices[act.from].data << "->" << G.vertices[act.to].data << "\t" << act.weight << endl;
        }
    }
}

// 测试用例
int main() {
    ALGraph G;
    G.vexnum = 6;
    G.arcnum = 8;

    // 初始化顶点
    for (int i = 0; i < G.vexnum; i++) {
        G.vertices[i].data = 'A' + i;
        G.vertices[i].firstarc = nullptr;
    }

    // 添加边的辅助函数
    auto addEdge = [&](int from, int to, int weight) {
        auto *p = new ArcNode;
        p->adjvex = to;
        p->weight = weight;
        p->nextarc = G.vertices[from].firstarc;
        G.vertices[from].firstarc = p;
    };

    // 添加AOE网络的边
    addEdge(0, 1, 3); // A->B
    addEdge(0, 2, 4); // A->C
    addEdge(1, 3, 5); // B->D
    addEdge(2, 3, 6); // C->D
    addEdge(2, 4, 7); // C->E
    addEdge(3, 5, 2); // D->F
    addEdge(4, 5, 5); // E->F
    addEdge(1, 4, 6); // B->E

    cout << "AOE网络的关键路径分析：" << endl;
    CriticalPath(G);

    return 0;
}
