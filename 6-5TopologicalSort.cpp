#include <iostream>
#include <stack>
#include "6-0GraphDefinition.h"

using namespace std;

void FindInDegree(const ALGraph &G, vector<int> &inDegree) {
    inDegree.resize(G.vexnum, 0);
    for (int i = 0; i < G.vexnum; i++) {
        for (ArcNode *p = G.vertices[i].firstarc; p; p = p->nextarc) {
            inDegree[p->adjvex]++;
        }
    }
}

bool TopologicalSort(const ALGraph &G) {
    vector<int> inDegree(G.vexnum, 0);
    FindInDegree(G, inDegree);
    stack<int> S;
    int i;
    int count = 0; // 输出顶点计数
    for (i = 0; i < G.vexnum; ++i) {
        if (inDegree[i] == 0) {
            S.push(i);
        }
    }
    cout << "序列" << endl;
    while (!S.empty()) {
        int v = S.top();
        S.pop();
        cout << G.vertices[i].data << " ";
        count++;

        for (ArcNode *p = G.vertices[v].firstarc; p; p = p->nextarc) {
            if (!(--inDegree[p->adjvex])) {
                S.push(p->adjvex);
            }
        }
    }
    cout << endl;
    return count == G.vexnum;
}
