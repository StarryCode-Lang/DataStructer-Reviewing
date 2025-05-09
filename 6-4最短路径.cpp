#include <iomanip>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>
#include "6图的定义.h"
using namespace std;

// 全局变量
int path[MaxVertexNum][MaxVertexNum]; // 记录最短路径的前驱顶点

// Dijkstra算法 - 适用于邻接矩阵表示的图
void Dijkstra_Matrix(const MGraph &G, int start, int dist[], int path[]) {
    bool visited[MaxVertexNum] = {false}; // 标记顶点是否已找到最短路径

    // 初始化距离数组和路径数组
    for (int i = 0; i < G.vexnum; i++) {
        dist[i] = G.edge[start][i]; // 初始距离为起点到各顶点的直接距离
        if (dist[i] < INFINITY) {
            path[i] = start; // 如果可达，则前驱为起点
        } else {
            path[i] = -1; // 不可达，前驱为-1
        }
    }

    // 起点到自身的距离为0
    dist[start] = 0;
    visited[start] = true;

    // 找到其余n-1个顶点的最短路径
    for (int i = 1; i < G.vexnum; i++) {
        int minDist = INFINITY;
        int u = -1;

        // 找出当前未访问的顶点中距离最小的顶点
        for (int j = 0; j < G.vexnum; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
        }

        // 如果找不到可达的顶点，结束循环
        if (u == -1)
            break;

        // 标记该顶点已找到最短路径
        visited[u] = true;

        // 更新与u相邻的顶点的距离
        for (int v = 0; v < G.vexnum; v++) {
            // 如果v未访问，且从u到v有边，且从start经过u到v的路径更短
            if (!visited[v] && G.edge[u][v] < INFINITY && dist[u] + G.edge[u][v] < dist[v]) {
                dist[v] = dist[u] + G.edge[u][v]; // 更新距离
                path[v] = u; // 更新前驱
            }
        }
    }
}

// 使用优先队列优化的Dijkstra算法 - 适用于邻接表表示的图
void Dijkstra_List(const ALGraph &G, int start, int dist[], int path[]) {
    bool visited[MaxVertexNum] = {false}; // 标记顶点是否已找到最短路径

    // 初始化距离数组和路径数组
    for (int i = 0; i < G.vexnum; i++) {
        dist[i] = INFINITY;
        path[i] = -1;
    }

    // 起点到自身的距离为0
    dist[start] = 0;

    // 定义优先队列，按距离排序
    typedef pair<int, int> iPair; // <距离, 顶点>
    priority_queue<iPair, vector<iPair>, greater<>> pq;

    // 将起点加入优先队列
    pq.emplace(0, start);

    while (!pq.empty()) {
        // 取出当前距离最小的顶点
        int u = pq.top().second;
        pq.pop();

        // 如果该顶点已经处理过，则跳过
        if (visited[u])
            continue;

        // 标记该顶点已找到最短路径
        visited[u] = true;

        // 遍历u的所有邻接点
        for (ArcNode *p = G.vertices[u].firstarc; p; p = p->nextarc) {
            int v = p->adjvex;
            int weight = p->weight;

            // 如果从u到v的路径更短，则更新
            if (!visited[v] && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                path[v] = u;
                pq.emplace(dist[v], v);
            }
        }
    }
}

// 打印Dijkstra算法的结果
void PrintDijkstraResult(const Graph &G, int start, int dist[], const int path[]) {
    cout << "从顶点 ";

    if (const auto mg = dynamic_cast<const MGraph *>(&G)) {
        cout << mg->vex[start];
    } else if (const auto ag = dynamic_cast<const ALGraph *>(&G)) {
        cout << ag->vertices[start].data;
    }

    cout << " 到其他顶点的最短路径：" << endl;

    for (int i = 0; i < G.vexnum; i++) {
        if (i == start)
            continue;

        cout << "到顶点 ";
        if (const auto mg = dynamic_cast<const MGraph *>(&G)) {
            cout << mg->vex[i];
        } else if (const auto ag = dynamic_cast<const ALGraph *>(&G)) {
            cout << ag->vertices[i].data;
        }

        if (dist[i] == INFINITY) {
            cout << " 不可达" << endl;
        } else {
            cout << " 的最短距离为: " << dist[i] << ", 路径为: ";

            // 存储路径
            vector<int> pathVertices;
            int v = i;
            while (v != start) {
                pathVertices.push_back(v);
                v = path[v];
            }
            pathVertices.push_back(start);

            // 逆序打印路径
            for (int j = pathVertices.size() - 1; j >= 0; j--) {
                if (const auto mg = dynamic_cast<const MGraph *>(&G)) {
                    cout << mg->vex[pathVertices[j]];
                } else if (const auto ag = dynamic_cast<const ALGraph *>(&G)) {
                    cout << ag->vertices[pathVertices[j]].data;
                }

                if (j > 0)
                    cout << " -> ";
            }
            cout << endl;
        }
    }
}

// Floyd算法 - 适用于邻接矩阵表示的图
void Floyd(const MGraph &G, int dist[][MaxVertexNum], int path[][MaxVertexNum]) {
    // 初始化距离矩阵和路径矩阵
    for (int i = 0; i < G.vexnum; i++) {
        for (int j = 0; j < G.vexnum; j++) {
            dist[i][j] = G.edge[i][j];
            if (i != j && dist[i][j] < INFINITY) {
                path[i][j] = i; // 如果i和j之间有直接连接，则路径为i
            } else {
                path[i][j] = -1; // 否则路径为-1
            }
        }
    }

    // Floyd算法核心：对于每个顶点k，检查从i经过k到j的路径是否比直接从i到j的路径更短
    for (int k = 0; k < G.vexnum; k++) {
        for (int i = 0; i < G.vexnum; i++) {
            for (int j = 0; j < G.vexnum; j++) {
                // 如果经过k的路径存在且比原路径短
                if (dist[i][k] < INFINITY && dist[k][j] < INFINITY && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j]; // 更新距离
                    path[i][j] = path[k][j]; // 更新路径
                }
            }
        }
    }
}

// 打印Floyd算法的结果
void PrintFloydResult(const MGraph &G, int dist[][MaxVertexNum], int path[][MaxVertexNum]) {
    cout << "所有顶点对之间的最短路径：" << endl;

    for (int i = 0; i < G.vexnum; i++) {
        for (int j = 0; j < G.vexnum; j++) {
            if (i != j) {
                cout << "从顶点 " << G.vex[i] << " 到顶点 " << G.vex[j];

                if (dist[i][j] == INFINITY) {
                    cout << " 不可达" << endl;
                } else {
                    cout << " 的最短距离为: " << dist[i][j] << ", 路径为: ";

                    // 打印路径
                    cout << G.vex[i];
                    int k = path[i][j];
                    while (k != -1 && k != j) {
                        cout << " -> " << G.vex[k];
                        k = path[k][j];
                    }
                    cout << " -> " << G.vex[j] << endl;
                }
            }
        }
    }
}

// 打印距离矩阵
void PrintDistanceMatrix(const MGraph &G, int dist[][MaxVertexNum]) {
    cout << "距离矩阵：" << endl;
    cout << "    ";
    for (int i = 0; i < G.vexnum; i++) {
        cout << setw(5) << G.vex[i];
    }
    cout << endl;

    for (int i = 0; i < G.vexnum; i++) {
        cout << setw(4) << G.vex[i];
        for (int j = 0; j < G.vexnum; j++) {
            if (dist[i][j] == INFINITY) {
                cout << setw(5) << "∞";
            } else {
                cout << setw(5) << dist[i][j];
            }
        }
        cout << endl;
    }
}

// 初始化带权有向图的邻接矩阵
void InitDirectedWeightedMGraph(MGraph &G) {
    G.vexnum = 5;
    G.arcnum = 8;

    // 初始化顶点
    G.vex[0] = 'A';
    G.vex[1] = 'B';
    G.vex[2] = 'C';
    G.vex[3] = 'D';
    G.vex[4] = 'E';

    // 初始化邻接矩阵，先全部设为无穷大
    for (int i = 0; i < G.vexnum; i++) {
        for (int j = 0; j < G.vexnum; j++) {
            G.edge[i][j] = INFINITY;
        }
        G.edge[i][i] = 0; // 自己到自己的距离为0
    }

    // 添加有向边
    G.edge[0][1] = 10; // A -> B
    G.edge[0][3] = 30; // A -> D
    G.edge[0][4] = 100; // A -> E
    G.edge[1][2] = 50; // B -> C
    G.edge[2][4] = 10; // C -> E
    G.edge[3][2] = 20; // D -> C
    G.edge[3][4] = 60; // D -> E
    G.edge[4][1] = 10; // E -> B
}

// 初始化带权有向图的邻接表
void InitDirectedWeightedALGraph(ALGraph &G) {
    G.vexnum = 5;
    G.arcnum = 8;

    // 初始化顶点
    G.vertices[0].data = 'A';
    G.vertices[1].data = 'B';
    G.vertices[2].data = 'C';
    G.vertices[3].data = 'D';
    G.vertices[4].data = 'E';

    // 初始化邻接表，先将所有顶点的第一个邻接点设为NULL
    for (int i = 0; i < G.vexnum; i++) {
        G.vertices[i].firstarc = nullptr;
    }

    // 添加边的函数
    auto addEdge = [&](int u, int v, EdgeType w) {
        auto *p = new ArcNode;
        p->adjvex = v;
        p->weight = w;
        p->nextarc = G.vertices[u].firstarc;
        G.vertices[u].firstarc = p;
    };

    // 添加有向边
    addEdge(0, 1, 10); // A -> B
    addEdge(0, 3, 30); // A -> D
    addEdge(0, 4, 100); // A -> E
    addEdge(1, 2, 50); // B -> C
    addEdge(2, 4, 10); // C -> E
    addEdge(3, 2, 20); // D -> C
    addEdge(3, 4, 60); // D -> E
    addEdge(4, 1, 10); // E -> B
}


int main() {
    // 测试Dijkstra算法 - 邻接矩阵实现
    MGraph mg;
    InitDirectedWeightedMGraph(mg);
    cout << "=== 测试Dijkstra算法（邻接矩阵实现）===" << endl;
    PrintGraph(mg);

    int dist_matrix[MaxVertexNum];
    int path_matrix[MaxVertexNum];
    int start = 0; // 从顶点A开始

    Dijkstra_Matrix(mg, start, dist_matrix, path_matrix);
    PrintDijkstraResult(mg, start, dist_matrix, path_matrix);

    cout << "\n----------------------------------------\n" << endl;

    // 测试Dijkstra算法 - 邻接表实现
    ALGraph ag;
    InitDirectedWeightedALGraph(ag);
    cout << "=== 测试Dijkstra算法（邻接表实现）===" << endl;
    PrintGraph(ag);

    int dist_list[MaxVertexNum];
    int path_list[MaxVertexNum];

    Dijkstra_List(ag, start, dist_list, path_list);
    PrintDijkstraResult(ag, start, dist_list, path_list);

    cout << "\n----------------------------------------\n" << endl;

    // 测试Floyd算法
    cout << "=== 测试Floyd算法 ===" << endl;
    PrintGraph(mg);

    int floyd_dist[MaxVertexNum][MaxVertexNum];
    int floyd_path[MaxVertexNum][MaxVertexNum];

    Floyd(mg, floyd_dist, floyd_path);
    PrintDistanceMatrix(mg, floyd_dist);
    PrintFloydResult(mg, floyd_dist, floyd_path);

    return 0;
}
