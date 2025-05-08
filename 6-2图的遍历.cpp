#include <iostream>
#include <limits>
#include <queue>
#include "GraphOperation.h"

using namespace std;

queue<int> Q;

void visit(const MGraph &G, int i) { cout << G.vex[i] << " "; }
void visit(const ALGraph &G, int i) { cout << G.vertices[i].data << " "; }

// BFS解决非带权图的单源最短路径问题
void BFS(const MGraph &G, int u) {
    int d[G.vexnum];
    for (int i = 0; i < G.vexnum; ++i)
        d[i] = INFINITY;
    visit(G, u);
    visited[u] = true;
    d[u] = 0;
    Q.push(u);
    while (!Q.empty()) {
        int curr = Q.front();
        Q.pop();
        for (int w = 0; w < G.vexnum; ++w) {
            if (!visited[w] && G.edge[curr][w] == 1) {
                visit(G, w);
                visited[w] = true;
                d[w] = d[curr] + 1;
                Q.push(w);
            }
        }
    }
}

void BFS(const ALGraph &G, int u) {
    int d[G.vexnum];
    for (int i = 0; i < G.vexnum; ++i)
        d[i] = INFINITY;
    visit(G, u);
    visited[u] = true;
    d[u] = 0;
    Q.push(u);
    while (!Q.empty()) {
        int curr = Q.front();
        Q.pop();
        for (ArcNode *p = G.vertices[curr].firstarc; p; p = p->nextarc) {
            int w = p->adjvex;
            if (!visited[w]) {
                visit(G, w);
                visited[w] = true;
                d[w] = d[curr] + 1;
                Q.push(w);
            }
        }
    }
}

void BFSTraverse(const Graph &G) {
    for (int i = 0; i < G.vexnum; ++i)
        visited[i] = false;
    for (int i = 0; i < G.vexnum; ++i) {
        if (!visited[i]) {
            // 判断类型并调用对应BFS
            if (const auto mg = dynamic_cast<const MGraph *>(&G)) {
                BFS(*mg, i);
            } else if (const auto ag = dynamic_cast<const ALGraph *>(&G)) {
                BFS(*ag, i);
            }
        }
    }
}

void DFS(const MGraph &G, int i) {
    visit(G, i);
    visited[i] = true;
    for (int j = 0; j < G.vexnum; ++j) {
        if (!visited[j] && G.edge[i][j] == 1) {
            DFS(G, j);
        }
    }
}
void DFS(const ALGraph &G, int i) {
    visit(G, i);
    visited[i] = true;
    for (ArcNode *p = G.vertices[i].firstarc; p; p = p->nextarc) {
        int w = p->adjvex;
        if (!visited[w]) {
            DFS(G, w);
        }
    }
}


void DFSTraverse(const Graph &G) {
    for (int i = 0; i < G.vexnum; ++i)
        visited[i] = false;
    for (int i = 0; i < G.vexnum; ++i) {
        if (!visited[i]) {
            if (const auto mg = dynamic_cast<const MGraph *>(&G)) {
                DFS(*mg, i);
            } else if (const auto ag = dynamic_cast<const ALGraph *>(&G)) {
                DFS(*ag, i);
            }
        }
    }
}

// 示例：邻接矩阵和邻接表的简单初始化
void InitSampleMGraph(MGraph &G) {
    G.vexnum = 4;
    G.arcnum = 4;
    G.vex[0] = 'A';
    G.vex[1] = 'B';
    G.vex[2] = 'C';
    G.vex[3] = 'D';
    for (int i = 0; i < G.vexnum; ++i)
        for (int j = 0; j < G.vexnum; ++j)
            G.edge[i][j] = 0;
    G.edge[0][1] = G.edge[1][0] = 1;
    G.edge[0][2] = G.edge[2][0] = 1;
    G.edge[1][3] = G.edge[3][1] = 1;
    G.edge[2][3] = G.edge[3][2] = 1;
}

void InitSampleALGraph(ALGraph &G) {
    G.vexnum = 4;
    G.arcnum = 4;
    G.vertices[0].data = 'A';
    G.vertices[1].data = 'B';
    G.vertices[2].data = 'C';
    G.vertices[3].data = 'D';
    for (int i = 0; i < G.vexnum; ++i)
        G.vertices[i].firstarc = nullptr;
    auto addEdge = [&](int u, int v) {
        auto *p = new ArcNode{v, G.vertices[u].firstarc, 1};
        G.vertices[u].firstarc = p;
    };
    addEdge(0, 1);
    addEdge(1, 0);
    addEdge(0, 2);
    addEdge(2, 0);
    addEdge(1, 3);
    addEdge(3, 1);
    addEdge(2, 3);
    addEdge(3, 2);
}

int main() {
    MGraph mg;
    ALGraph ag;
    cout << "邻接矩阵BFS: ";
    InitSampleMGraph(mg);
    BFSTraverse(mg);

    cout << "邻接表BFS: ";
    InitSampleALGraph(ag);
    BFSTraverse(ag);

    return 0;
}
