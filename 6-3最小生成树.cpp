#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>
#include "5-2并查集.h"
#include "6图的定义.h"

using namespace std;

int UFSets[SIZE]; // 并查集数组

// 定义边结构体，用于最小生成树算法
struct Edge {
    int u, v; // 边的两个顶点索引
    EdgeType weight; // 边的权值
    VertexType u_data, v_data; // 顶点数据

    // 重载小于运算符，用于排序
    bool operator<(const Edge &other) const { return weight < other.weight; }
};

// Prim算法 - 适用于邻接矩阵表示的图
void Prim(const MGraph &G) {
    if (G.vexnum <= 0)
        return;

    cout << "Prim算法生成最小生成树：" << endl;

    int lowcost[MaxVertexNum]; // 存储顶点i到当前最小生成树的最小权值
    int closest[MaxVertexNum]; // 存储顶点i到当前最小生成树的最近顶点
    bool added[MaxVertexNum]; // 标记顶点是否已加入最小生成树

    // 初始化
    for (int i = 0; i < G.vexnum; i++) {
        lowcost[i] = G.edge[0][i]; // 初始化为第一个顶点到其他顶点的权值
        closest[i] = 0; // 初始时所有顶点的最近顶点都是0
        added[i] = false; // 初始时所有顶点都未加入最小生成树
    }

    // 将第一个顶点加入最小生成树
    added[0] = true;

    // 输出最小生成树的信息
    cout << "最小生成树的边：" << endl;

    // 循环n-1次，每次加入一个顶点
    for (int i = 1; i < G.vexnum; i++) {
        int minWeight = INFINITY;
        int minVertex = -1;

        // 找出权值最小的边
        for (int j = 0; j < G.vexnum; j++) {
            if (!added[j] && lowcost[j] < minWeight) {
                minWeight = lowcost[j];
                minVertex = j;
            }
        }

        // 如果找不到最小边，说明图不连通
        if (minVertex == -1) {
            cout << "图不连通，无法生成最小生成树" << endl;
            return;
        }

        // 将找到的顶点加入最小生成树
        added[minVertex] = true;

        // 输出这条边
        cout << "(" << G.vex[closest[minVertex]] << ", " << G.vex[minVertex] << ") 权值: " << minWeight << endl;

        // 更新lowcost和closest数组
        for (int j = 0; j < G.vexnum; j++) {
            if (!added[j] && G.edge[minVertex][j] < lowcost[j]) {
                lowcost[j] = G.edge[minVertex][j];
                closest[j] = minVertex;
            }
        }
    }
}

// 使用并查集的Kruskal算法 - 适用于邻接表表示的图
void Kruskal(const ALGraph &G) {
    if (G.vexnum <= 0)
        return;

    cout << "Kruskal算法生成最小生成树：" << endl;

    // 收集图中所有的边
    vector<Edge> edges;
    for (int i = 0; i < G.vexnum; i++) {
        for (ArcNode *p = G.vertices[i].firstarc; p; p = p->nextarc) {
            // 为避免无向图中边重复，只添加顶点编号大于当前顶点的边
            if (p->adjvex > i) {
                Edge e{};
                e.u = i;
                e.v = p->adjvex;
                e.weight = p->weight;
                e.u_data = G.vertices[i].data;
                e.v_data = G.vertices[p->adjvex].data;
                edges.push_back(e);
            }
        }
    }

    // 按权值对边进行排序
    sort(edges.begin(), edges.end());

    // 初始化并查集
    Initial(UFSets);

    // 输出最小生成树的信息
    cout << "最小生成树的边：" << endl;

    vector<Edge> mst; // 存储最小生成树的边

    // 按权值从小到大遍历所有边
    for (const Edge &e: edges) {
        // 查找两个顶点所在的集合
        int root1 = Find(UFSets, e.u);
        int root2 = Find(UFSets, e.v);

        // 如果两个顶点不在同一个集合中，则这条边可以加入最小生成树
        if (root1 != root2) {
            // 合并两个集合
            Union(UFSets, root1, root2);

            // 将边加入最小生成树
            mst.push_back(e);

            // 输出这条边
            cout << "(" << e.u_data << ", " << e.v_data << ") 权值: " << e.weight << endl;

            // 如果已经有n-1条边，则最小生成树已经生成完毕
            if (mst.size() == G.vexnum - 1) {
                break;
            }
        }
    }

    // 如果边数小于n-1，说明图不连通
    if (mst.size() < G.vexnum - 1) {
        cout << "图不连通，无法生成完整的最小生成树" << endl;
    }
}

// 初始化带权图的邻接矩阵
void InitWeightedMGraph(MGraph &G) {
    G.vexnum = 6;
    G.arcnum = 10;

    // 初始化顶点
    G.vex[0] = 'A';
    G.vex[1] = 'B';
    G.vex[2] = 'C';
    G.vex[3] = 'D';
    G.vex[4] = 'E';
    G.vex[5] = 'F';

    // 初始化邻接矩阵，先全部设为无穷大
    for (int i = 0; i < G.vexnum; i++) {
        for (int j = 0; j < G.vexnum; j++) {
            G.edge[i][j] = INFINITY;
        }
        G.edge[i][i] = 0; // 自己到自己的距离为0
    }

    // 添加边（无向图，对称）
    G.edge[0][1] = G.edge[1][0] = 6;
    G.edge[0][2] = G.edge[2][0] = 1;
    G.edge[0][3] = G.edge[3][0] = 5;
    G.edge[1][2] = G.edge[2][1] = 5;
    G.edge[1][4] = G.edge[4][1] = 3;
    G.edge[2][3] = G.edge[3][2] = 5;
    G.edge[2][4] = G.edge[4][2] = 6;
    G.edge[2][5] = G.edge[5][2] = 4;
    G.edge[3][5] = G.edge[5][3] = 2;
    G.edge[4][5] = G.edge[5][4] = 6;
}

// 初始化带权图的邻接表
void InitWeightedALGraph(ALGraph &G) {
    G.vexnum = 6;
    G.arcnum = 10;

    // 初始化顶点
    G.vertices[0].data = 'A';
    G.vertices[1].data = 'B';
    G.vertices[2].data = 'C';
    G.vertices[3].data = 'D';
    G.vertices[4].data = 'E';
    G.vertices[5].data = 'F';

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

    // 添加边（无向图，需要添加两次）
    addEdge(0, 1, 6);
    addEdge(1, 0, 6);
    addEdge(0, 2, 1);
    addEdge(2, 0, 1);
    addEdge(0, 3, 5);
    addEdge(3, 0, 5);
    addEdge(1, 2, 5);
    addEdge(2, 1, 5);
    addEdge(1, 4, 3);
    addEdge(4, 1, 3);
    addEdge(2, 3, 5);
    addEdge(3, 2, 5);
    addEdge(2, 4, 6);
    addEdge(4, 2, 6);
    addEdge(2, 5, 4);
    addEdge(5, 2, 4);
    addEdge(3, 5, 2);
    addEdge(5, 3, 2);
    addEdge(4, 5, 6);
    addEdge(5, 4, 6);
}

int main() {
    // 测试Prim算法
    MGraph mg;
    InitWeightedMGraph(mg);
    cout << "邻接矩阵表示的图：" << endl;
    for (int i = 0; i < mg.vexnum; i++) {
        cout << mg.vex[i] << ": ";
        for (int j = 0; j < mg.vexnum; j++) {
            if (mg.edge[i][j] != INFINITY && i != j) {
                cout << "(" << mg.vex[j] << ", " << mg.edge[i][j] << ") ";
            }
        }
        cout << endl;
    }
    cout << endl;
    Prim(mg);

    cout << "\n----------------------------------------\n" << endl;

    // 测试Kruskal算法
    ALGraph ag;
    InitWeightedALGraph(ag);
    cout << "邻接表表示的图：" << endl;
    for (int i = 0; i < ag.vexnum; i++) {
        cout << ag.vertices[i].data << ": ";
        for (ArcNode *p = ag.vertices[i].firstarc; p; p = p->nextarc) {
            cout << "(" << ag.vertices[p->adjvex].data << ", " << p->weight << ") ";
        }
        cout << endl;
    }
    cout << endl;
    Kruskal(ag);

    return 0;
}
