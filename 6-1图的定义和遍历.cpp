/**
 * 文件名：graph_operations.cpp
 * 描述：实现图的基本操作，包括四种存储方式：邻接矩阵、邻接表、十字链表和邻接多重表
 * 包含的操作：Adjacent、Neighbors、InsertVertex、DeleteVertex、AddEdge、RemoveEdge、
 *           FirstNeighbor、NextNeighbor、Get_edge_value、Set_edge_value
 */

#include <iostream>
#include <limits>
#include <vector>

using namespace std;

#define MaxVertexNum 100
#define INFINITY numeric_limits<int>::max()
typedef char VertexType; // 顶点的数据类型
typedef int EdgeType; // 边的权值类型

// =============== 1. 邻接矩阵表示法 ===============
typedef struct {
    VertexType vex[MaxVertexNum]; // 顶点数组
    EdgeType edge[MaxVertexNum][MaxVertexNum]; // 邻接矩阵，存储边的权值
    int vexnum, arcnum; // 图的当前顶点数和边数
} MGraph;

// 初始化邻接矩阵表示的图
void InitMGraph(MGraph &G) {
    G.vexnum = 0;
    G.arcnum = 0;
    // 初始化邻接矩阵，所有边的权值置为无穷大，表示不连通
    for (int i = 0; i < MaxVertexNum; i++) {
        for (int j = 0; j < MaxVertexNum; j++) {
            G.edge[i][j] = INFINITY;
        }
        G.edge[i][i] = 0; // 自环设为0
    }
}

// 在邻接矩阵中定位顶点的位置
int LocateVex_M(const MGraph &G, VertexType x) {
    for (int i = 0; i < G.vexnum; i++) {
        if (G.vex[i] == x) {
            return i;
        }
    }
    return -1; // 顶点不存在
}

// Adjacent(G,x,y): 判断图G是否存在边<x,y>或(x,y)
bool Adjacent_M(const MGraph &G, VertexType x, VertexType y) {
    int xIndex = LocateVex_M(G, x);
    int yIndex = LocateVex_M(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return false; // 顶点不存在
    }

    return G.edge[xIndex][yIndex] != INFINITY;
}

// Neighbors(G,x): 列出图G中与顶点x邻接的边
vector<VertexType> Neighbors_M(const MGraph &G, VertexType x) {
    vector<VertexType> neighbors;
    int xIndex = LocateVex_M(G, x);

    if (xIndex == -1) {
        return neighbors; // 顶点不存在，返回空列表
    }

    for (int i = 0; i < G.vexnum; i++) {
        if (G.edge[xIndex][i] != INFINITY && i != xIndex) {
            neighbors.push_back(G.vex[i]);
        }
    }

    return neighbors;
}

// InsertVertex(G,x): 在图G中插入顶点x
bool InsertVertex_M(MGraph &G, VertexType x) {
    // 检查图是否已满
    if (G.vexnum >= MaxVertexNum) {
        return false;
    }

    // 检查顶点是否已存在
    if (LocateVex_M(G, x) != -1) {
        return false;
    }

    // 插入顶点
    G.vex[G.vexnum] = x;

    // 初始化新顶点的边
    for (int i = 0; i <= G.vexnum; i++) {
        G.edge[G.vexnum][i] = INFINITY;
        G.edge[i][G.vexnum] = INFINITY;
    }
    G.edge[G.vexnum][G.vexnum] = 0; // 自环设为0

    G.vexnum++;
    return true;
}

// DeleteVertex(G,x): 从图G中删除顶点x
bool DeleteVertex_M(MGraph &G, VertexType x) {
    int xIndex = LocateVex_M(G, x);

    if (xIndex == -1) {
        return false; // 顶点不存在
    }

    // 更新边数
    for (int i = 0; i < G.vexnum; i++) {
        if (G.edge[xIndex][i] != INFINITY && i != xIndex) {
            G.arcnum--;
        }
        if (G.edge[i][xIndex] != INFINITY && i != xIndex) {
            // 如果是有向图，需要减去所有入边
            G.arcnum--;
        }
    }

    // 删除顶点，将后面的顶点前移
    for (int i = xIndex; i < G.vexnum - 1; i++) {
        G.vex[i] = G.vex[i + 1];
    }

    // 更新邻接矩阵
    for (int i = xIndex; i < G.vexnum - 1; i++) {
        for (int j = 0; j < G.vexnum; j++) {
            G.edge[i][j] = G.edge[i + 1][j];
        }
    }

    for (int j = xIndex; j < G.vexnum - 1; j++) {
        for (int i = 0; i < G.vexnum - 1; i++) {
            G.edge[i][j] = G.edge[i][j + 1];
        }
    }

    G.vexnum--;
    return true;
}

// AddEdge(G,x,y): 如果无向边(x,y)或有向边<x,y>不存在，则向图G中添加该边
bool AddEdge_M(MGraph &G, VertexType x, VertexType y, EdgeType weight = 1) {
    int xIndex = LocateVex_M(G, x);
    int yIndex = LocateVex_M(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return false; // 顶点不存在
    }

    if (G.edge[xIndex][yIndex] != INFINITY) {
        return false; // 边已存在
    }

    G.edge[xIndex][yIndex] = weight;
    G.arcnum++;
    return true;
}

// RemoveEdge(G,x,y): 如果无向边(x,y)或有向边<x,y>存在，则从图G中删除该边
bool RemoveEdge_M(MGraph &G, VertexType x, VertexType y) {
    int xIndex = LocateVex_M(G, x);
    int yIndex = LocateVex_M(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return false; // 顶点不存在
    }

    if (G.edge[xIndex][yIndex] == INFINITY) {
        return false; // 边不存在
    }

    G.edge[xIndex][yIndex] = INFINITY;
    G.arcnum--;
    return true;
}

// FirstNeighbor(G,x): 求图G中顶点x的第一个邻接点，若有则返回顶点号，若x没有邻接点或图中不存在x，则返回-1
int FirstNeighbor_M(const MGraph &G, VertexType x) {
    int xIndex = LocateVex_M(G, x);

    if (xIndex == -1) {
        return -1; // 顶点不存在
    }

    for (int i = 0; i < G.vexnum; i++) {
        if (G.edge[xIndex][i] != INFINITY && i != xIndex) {
            return i;
        }
    }

    return -1; // 没有邻接点
}

// NextNeighbor(G,x,y): 假设图G中顶点y是顶点x的一个邻接点，返回除y外顶点x的下一个邻接点的顶点号，
// 若y是x的最后一个邻接点，则返回-1
int NextNeighbor_M(const MGraph &G, VertexType x, VertexType y) {
    int xIndex = LocateVex_M(G, x);
    int yIndex = LocateVex_M(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return -1; // 顶点不存在
    }

    if (G.edge[xIndex][yIndex] == INFINITY) {
        return -1; // y不是x的邻接点
    }

    for (int i = yIndex + 1; i < G.vexnum; i++) {
        if (G.edge[xIndex][i] != INFINITY && i != xIndex) {
            return i;
        }
    }

    return -1; // 没有下一个邻接点
}

// Get_edge_value(G,x,y): 获取图G中边(x,y)或<x,y>对应的权值
EdgeType Get_edge_value_M(const MGraph &G, VertexType x, VertexType y) {
    int xIndex = LocateVex_M(G, x);
    int yIndex = LocateVex_M(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return INFINITY; // 顶点不存在
    }

    return G.edge[xIndex][yIndex];
}

// Set_edge_value(G,x,y,v): 设置图G中边(x,y)或<x,y>对应的权值为v
bool Set_edge_value_M(MGraph &G, VertexType x, VertexType y, EdgeType v) {
    int xIndex = LocateVex_M(G, x);
    int yIndex = LocateVex_M(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return false; // 顶点不存在
    }

    if (G.edge[xIndex][yIndex] == INFINITY && v != INFINITY) {
        G.arcnum++; // 如果原来不存在边，现在添加了边，边数加1
    } else if (G.edge[xIndex][yIndex] != INFINITY && v == INFINITY) {
        G.arcnum--; // 如果原来存在边，现在删除了边，边数减1
    }

    G.edge[xIndex][yIndex] = v;
    return true;
}

// =============== 2. 邻接表表示法 ===============
typedef struct ArcNode { // 边表节点
    int adjvex; // 该边所指向的顶点下标
    struct ArcNode *nextarc; // 指向下一条边的指针
    EdgeType weight; // 边的权值
} ArcNode;

typedef struct VNode { // 顶点表节点
    VertexType data; // 顶点信息
    ArcNode *firstarc; // 指向第一条依附该顶点的边
} VNode, AdjList[MaxVertexNum];

typedef struct {
    AdjList vertices; // 顶点表
    int vexnum, arcnum; // 图的当前顶点数和边数
} ALGraph;

// 初始化邻接表表示的图
void InitALGraph(ALGraph &G) {
    G.vexnum = 0;
    G.arcnum = 0;

    for (auto &vertice: G.vertices) {
        vertice.firstarc = nullptr;
    }
}

// 在邻接表中定位顶点的位置
int LocateVex_AL(const ALGraph &G, VertexType x) {
    for (int i = 0; i < G.vexnum; i++) {
        if (G.vertices[i].data == x) {
            return i;
        }
    }
    return -1; // 顶点不存在
}

// Adjacent(G,x,y): 判断图G是否存在边<x,y>或(x,y)
bool Adjacent_AL(const ALGraph &G, VertexType x, VertexType y) {
    int xIndex = LocateVex_AL(G, x);
    int yIndex = LocateVex_AL(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return false; // 顶点不存在
    }

    ArcNode *p = G.vertices[xIndex].firstarc;
    while (p != nullptr) {
        if (p->adjvex == yIndex) {
            return true; // 边存在
        }
        p = p->nextarc;
    }

    return false; // 边不存在
}

// Neighbors(G,x): 列出图G中与顶点x邻接的边
vector<VertexType> Neighbors_AL(const ALGraph &G, VertexType x) {
    vector<VertexType> neighbors;
    int xIndex = LocateVex_AL(G, x);

    if (xIndex == -1) {
        return neighbors; // 顶点不存在，返回空列表
    }

    ArcNode *p = G.vertices[xIndex].firstarc;
    while (p != nullptr) {
        neighbors.push_back(G.vertices[p->adjvex].data);
        p = p->nextarc;
    }

    return neighbors;
}

// InsertVertex(G,x): 在图G中插入顶点x
bool InsertVertex_AL(ALGraph &G, VertexType x) {
    // 检查图是否已满
    if (G.vexnum >= MaxVertexNum) {
        return false;
    }

    // 检查顶点是否已存在
    if (LocateVex_AL(G, x) != -1) {
        return false;
    }

    // 插入顶点
    G.vertices[G.vexnum].data = x;
    G.vertices[G.vexnum].firstarc = nullptr;

    G.vexnum++;
    return true;
}

// DeleteVertex(G,x): 从图G中删除顶点x
bool DeleteVertex_AL(ALGraph &G, VertexType x) {
    int xIndex = LocateVex_AL(G, x);

    if (xIndex == -1) {
        return false; // 顶点不存在
    }

    // 删除以x为起点的所有边
    ArcNode *p = G.vertices[xIndex].firstarc;
    ArcNode *q;
    while (p != nullptr) {
        q = p;
        p = p->nextarc;
        delete q;
        G.arcnum--;
    }

    // 删除以x为终点的所有边
    for (int i = 0; i < G.vexnum; i++) {
        if (i == xIndex)
            continue;

        p = G.vertices[i].firstarc;
        q = nullptr;

        while (p != nullptr && p->adjvex != xIndex) {
            q = p;
            p = p->nextarc;
        }

        if (p != nullptr) { // 找到了以x为终点的边
            if (q == nullptr) { // 是第一条边
                G.vertices[i].firstarc = p->nextarc;
            } else {
                q->nextarc = p->nextarc;
            }
            delete p;
            G.arcnum--;
        }
    }

    // 更新所有顶点的边表中大于xIndex的节点值
    for (int i = 0; i < G.vexnum; i++) {
        p = G.vertices[i].firstarc;

        while (p != nullptr) {
            if (p->adjvex > xIndex) {
                p->adjvex--; // 下标减1
            }
            p = p->nextarc;
        }
    }

    // 删除顶点，将后面的顶点前移
    for (int i = xIndex; i < G.vexnum - 1; i++) {
        G.vertices[i] = G.vertices[i + 1];
    }

    G.vexnum--;
    return true;
}

// AddEdge(G,x,y): 如果无向边(x,y)或有向边<x,y>不存在，则向图G中添加该边
bool AddEdge_AL(ALGraph &G, VertexType x, VertexType y, EdgeType weight = 1) {
    int xIndex = LocateVex_AL(G, x);
    int yIndex = LocateVex_AL(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return false; // 顶点不存在
    }

    // 检查边是否已存在
    ArcNode *p = G.vertices[xIndex].firstarc;
    while (p != nullptr) {
        if (p->adjvex == yIndex) {
            return false; // 边已存在
        }
        p = p->nextarc;
    }

    // 创建新边
    auto *newArc = new ArcNode;
    newArc->adjvex = yIndex;
    newArc->weight = weight;
    newArc->nextarc = G.vertices[xIndex].firstarc;
    G.vertices[xIndex].firstarc = newArc;

    G.arcnum++;
    return true;
}

// RemoveEdge(G,x,y): 如果无向边(x,y)或有向边<x,y>存在，则从图G中删除该边
bool RemoveEdge_AL(ALGraph &G, VertexType x, VertexType y) {
    int xIndex = LocateVex_AL(G, x);
    int yIndex = LocateVex_AL(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return false; // 顶点不存在
    }

    ArcNode *p = G.vertices[xIndex].firstarc;
    ArcNode *q = nullptr;

    // 查找边
    while (p != nullptr && p->adjvex != yIndex) {
        q = p;
        p = p->nextarc;
    }

    if (p == nullptr) {
        return false; // 边不存在
    }

    // 删除边
    if (q == nullptr) { // 是第一条边
        G.vertices[xIndex].firstarc = p->nextarc;
    } else {
        q->nextarc = p->nextarc;
    }

    delete p;
    G.arcnum--;
    return true;
}

// FirstNeighbor(G,x): 求图G中顶点x的第一个邻接点，若有则返回顶点号，若x没有邻接点或图中不存在x，则返回-1
int FirstNeighbor_AL(const ALGraph &G, VertexType x) {
    int xIndex = LocateVex_AL(G, x);

    if (xIndex == -1) {
        return -1; // 顶点不存在
    }

    if (G.vertices[xIndex].firstarc != nullptr) {
        return G.vertices[xIndex].firstarc->adjvex;
    }

    return -1; // 没有邻接点
}

// NextNeighbor(G,x,y): 假设图G中顶点y是顶点x的一个邻接点，返回除y外顶点x的下一个邻接点的顶点号，
// 若y是x的最后一个邻接点，则返回-1
int NextNeighbor_AL(const ALGraph &G, VertexType x, VertexType y) {
    int xIndex = LocateVex_AL(G, x);
    int yIndex = LocateVex_AL(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return -1; // 顶点不存在
    }

    ArcNode *p = G.vertices[xIndex].firstarc;

    // 查找边x->y
    while (p != nullptr && p->adjvex != yIndex) {
        p = p->nextarc;
    }

    if (p == nullptr || p->nextarc == nullptr) {
        return -1; // 边不存在或y是最后一个邻接点
    }

    return p->nextarc->adjvex;
}

// Get_edge_value(G,x,y): 获取图G中边(x,y)或<x,y>对应的权值
EdgeType Get_edge_value_AL(const ALGraph &G, VertexType x, VertexType y) {
    int xIndex = LocateVex_AL(G, x);
    int yIndex = LocateVex_AL(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return INFINITY; // 顶点不存在
    }

    ArcNode *p = G.vertices[xIndex].firstarc;

    while (p != nullptr) {
        if (p->adjvex == yIndex) {
            return p->weight; // 返回边的权值
        }
        p = p->nextarc;
    }

    return INFINITY; // 边不存在
}

// Set_edge_value(G,x,y,v): 设置图G中边(x,y)或<x,y>对应的权值为v
bool Set_edge_value_AL(ALGraph &G, VertexType x, VertexType y, EdgeType v) {
    int xIndex = LocateVex_AL(G, x);
    int yIndex = LocateVex_AL(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return false; // 顶点不存在
    }

    ArcNode *p = G.vertices[xIndex].firstarc;

    // 查找边
    while (p != nullptr && p->adjvex != yIndex) {
        p = p->nextarc;
    }

    if (p == nullptr) {
        if (v == INFINITY) {
            return true; // 边本来就不存在且权值为INFINITY，无需操作
        }

        // 边不存在且需要添加边
        return AddEdge_AL(G, x, y, v);
    } else {
        if (v == INFINITY) {
            // 存在边但需要删除
            return RemoveEdge_AL(G, x, y);
        }

        // 存在边且需要更新权值
        p->weight = v;
        return true;
    }
}

// =============== 3. 十字链表表示法 ===============
typedef struct ArcBox { // 弧结点
    int tailvex; // 弧尾顶点编号
    int headvex; // 弧头顶点编号
    struct ArcBox *hlink; // 指向弧头相同的下一条弧
    struct ArcBox *tlink; // 指向弧尾相同的下一条弧
    EdgeType weight; // 弧的权值
} ArcBox;

typedef struct OLVNode { // 顶点结点
    VertexType data; // 顶点信息
    ArcBox *firstin; // 指向以该顶点为弧头的第一条弧
    ArcBox *firstout; // 指向以该顶点为弧尾的第一条弧
} OLVNode;

typedef struct {
    OLVNode xlist[MaxVertexNum]; // 顶点数组
    int vexnum, arcnum; // 顶点数和弧数
} OLGraph;

// 初始化十字链表表示的图
void InitOLGraph(OLGraph &G) {
    G.vexnum = 0;
    G.arcnum = 0;

    for (auto &i: G.xlist) {
        i.firstin = nullptr;
        i.firstout = nullptr;
    }
}

// 在十字链表中定位顶点的位置
int LocateVex_OL(const OLGraph &G, VertexType x) {
    for (int i = 0; i < G.vexnum; i++) {
        if (G.xlist[i].data == x) {
            return i;
        }
    }
    return -1; // 顶点不存在
}

// Adjacent(G,x,y): 判断图G是否存在边<x,y>或(x,y)
bool Adjacent_OL(const OLGraph &G, VertexType x, VertexType y) {
    int xIndex = LocateVex_OL(G, x);
    int yIndex = LocateVex_OL(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return false; // 顶点不存在
    }

    ArcBox *p = G.xlist[xIndex].firstout;
    while (p != nullptr) {
        if (p->headvex == yIndex) {
            return true; // 边存在
        }
        p = p->tlink;
    }

    return false; // 边不存在
}

// Neighbors(G,x): 列出图G中与顶点x邻接的边
vector<VertexType> Neighbors_OL(const OLGraph &G, VertexType x) {
    vector<VertexType> neighbors;
    int xIndex = LocateVex_OL(G, x);

    if (xIndex == -1) {
        return neighbors; // 顶点不存在，返回空列表
    }

    ArcBox *p = G.xlist[xIndex].firstout;
    while (p != nullptr) {
        neighbors.push_back(G.xlist[p->headvex].data);
        p = p->tlink;
    }

    return neighbors;
}

// InsertVertex(G,x): 在图G中插入顶点x
bool InsertVertex_OL(OLGraph &G, VertexType x) {
    // 检查图是否已满
    if (G.vexnum >= MaxVertexNum) {
        return false;
    }

    // 检查顶点是否已存在
    if (LocateVex_OL(G, x) != -1) {
        return false;
    }

    // 插入顶点
    G.xlist[G.vexnum].data = x;
    G.xlist[G.vexnum].firstin = nullptr;
    G.xlist[G.vexnum].firstout = nullptr;

    G.vexnum++;
    return true;
}

// DeleteVertex(G,x): 从图G中删除顶点x
bool DeleteVertex_OL(OLGraph &G, VertexType x) {
    int xIndex = LocateVex_OL(G, x);

    if (xIndex == -1) {
        return false; // 顶点不存在
    }

    // 删除以x为尾的所有弧
    ArcBox *p = G.xlist[xIndex].firstout;
    ArcBox *q;

    while (p != nullptr) {
        // 从弧头的链表中删除该弧
        if (G.xlist[p->headvex].firstin == p) {
            G.xlist[p->headvex].firstin = p->hlink;
        } else {
            ArcBox *temp = G.xlist[p->headvex].firstin;
            while (temp != nullptr && temp->hlink != p) {
                temp = temp->hlink;
            }
            if (temp != nullptr) {
                temp->hlink = p->hlink;
            }
        }

        q = p;
        p = p->tlink;
        delete q;
        G.arcnum--;
    }

    // 删除以x为头的所有弧
    p = G.xlist[xIndex].firstin;

    while (p != nullptr) {
        // 从弧尾的链表中删除该弧
        if (G.xlist[p->tailvex].firstout == p) {
            G.xlist[p->tailvex].firstout = p->tlink;
        } else {
            ArcBox *temp = G.xlist[p->tailvex].firstout;
            while (temp != nullptr && temp->tlink != p) {
                temp = temp->tlink;
            }
            if (temp != nullptr) {
                temp->tlink = p->tlink;
            }
        }

        q = p;
        p = p->hlink;
        delete q;
        G.arcnum--;
    }

    // 更新所有顶点的弧中大于xIndex的顶点编号
    for (int i = 0; i < G.vexnum; i++) {
        // 更新出弧
        p = G.xlist[i].firstout;
        while (p != nullptr) {
            if (p->headvex > xIndex) {
                p->headvex--; // 下标减1
            }
            p = p->tlink;
        }

        // 更新入弧
        p = G.xlist[i].firstin;
        while (p != nullptr) {
            if (p->tailvex > xIndex) {
                p->tailvex--; // 下标减1
            }
            p = p->hlink;
        }
    }

    // 删除顶点，将后面的顶点前移
    for (int i = xIndex; i < G.vexnum - 1; i++) {
        G.xlist[i] = G.xlist[i + 1];
    }

    G.vexnum--;
    return true;
}

// AddEdge(G,x,y): 如果有向边<x,y>不存在，则向图G中添加该边
bool AddEdge_OL(OLGraph &G, VertexType x, VertexType y, EdgeType weight = 1) {
    int xIndex = LocateVex_OL(G, x);
    int yIndex = LocateVex_OL(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return false; // 顶点不存在
    }

    // 检查边是否已存在
    ArcBox *p = G.xlist[xIndex].firstout;
    while (p != nullptr) {
        if (p->headvex == yIndex) {
            return false; // 边已存在
        }
        p = p->tlink;
    }

    // 创建新弧
    auto *newArc = new ArcBox;
    newArc->tailvex = xIndex;
    newArc->headvex = yIndex;
    newArc->weight = weight;

    // 插入到出弧链表中
    newArc->tlink = G.xlist[xIndex].firstout;
    G.xlist[xIndex].firstout = newArc;

    // 插入到入弧链表中
    newArc->hlink = G.xlist[yIndex].firstin;
    G.xlist[yIndex].firstin = newArc;

    G.arcnum++;
    return true;
}

// RemoveEdge(G,x,y): 如果有向边<x,y>存在，则从图G中删除该边
bool RemoveEdge_OL(OLGraph &G, VertexType x, VertexType y) {
    int xIndex = LocateVex_OL(G, x);
    int yIndex = LocateVex_OL(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return false; // 顶点不存在
    }

    // 查找边x->y
    ArcBox *p = G.xlist[xIndex].firstout;
    ArcBox *pre = nullptr;

    while (p != nullptr && p->headvex != yIndex) {
        pre = p;
        p = p->tlink;
    }

    if (p == nullptr) {
        return false; // 边不存在
    }

    // 从出弧链表中删除
    if (pre == nullptr) {
        G.xlist[xIndex].firstout = p->tlink;
    } else {
        pre->tlink = p->tlink;
    }

    // 从入弧链表中删除
    pre = nullptr;
    ArcBox *q = G.xlist[yIndex].firstin;

    while (q != nullptr && q != p) {
        pre = q;
        q = q->hlink;
    }

    if (pre == nullptr) {
        G.xlist[yIndex].firstin = p->hlink;
    } else {
        pre->hlink = p->hlink;
    }

    delete p;
    G.arcnum--;
    return true;
}

// FirstNeighbor(G,x): 求图G中顶点x的第一个邻接点，若有则返回顶点号，若x没有邻接点或图中不存在x，则返回-1
int FirstNeighbor_OL(const OLGraph &G, VertexType x) {
    int xIndex = LocateVex_OL(G, x);

    if (xIndex == -1) {
        return -1; // 顶点不存在
    }

    if (G.xlist[xIndex].firstout != nullptr) {
        return G.xlist[xIndex].firstout->headvex;
    }

    return -1; // 没有邻接点
}

// NextNeighbor(G,x,y): 假设图G中顶点y是顶点x的一个邻接点，返回除y外顶点x的下一个邻接点的顶点号，
// 若y是x的最后一个邻接点，则返回-1
int NextNeighbor_OL(const OLGraph &G, VertexType x, VertexType y) {
    int xIndex = LocateVex_OL(G, x);
    int yIndex = LocateVex_OL(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return -1; // 顶点不存在
    }

    ArcBox *p = G.xlist[xIndex].firstout;

    // 查找边x->y
    while (p != nullptr && p->headvex != yIndex) {
        p = p->tlink;
    }

    if (p == nullptr || p->tlink == nullptr) {
        return -1; // 边不存在或y是最后一个邻接点
    }

    return p->tlink->headvex;
}

// Get_edge_value(G,x,y): 获取图G中边<x,y>对应的权值
EdgeType Get_edge_value_OL(const OLGraph &G, VertexType x, VertexType y) {
    int xIndex = LocateVex_OL(G, x);
    int yIndex = LocateVex_OL(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return INFINITY; // 顶点不存在
    }

    ArcBox *p = G.xlist[xIndex].firstout;

    while (p != nullptr) {
        if (p->headvex == yIndex) {
            return p->weight; // 返回边的权值
        }
        p = p->tlink;
    }

    return INFINITY; // 边不存在
}

// Set_edge_value(G,x,y,v): 设置图G中边<x,y>对应的权值为v
bool Set_edge_value_OL(OLGraph &G, VertexType x, VertexType y, EdgeType v) {
    int xIndex = LocateVex_OL(G, x);
    int yIndex = LocateVex_OL(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return false; // 顶点不存在
    }

    ArcBox *p = G.xlist[xIndex].firstout;

    // 查找边
    while (p != nullptr && p->headvex != yIndex) {
        p = p->tlink;
    }

    if (p == nullptr) {
        if (v == INFINITY) {
            return true; // 边本来就不存在且权值为INFINITY，无需操作
        }

        // 边不存在且需要添加边
        return AddEdge_OL(G, x, y, v);
    } else {
        if (v == INFINITY) {
            // 存在边但需要删除
            return RemoveEdge_OL(G, x, y);
        }

        // 存在边且需要更新权值
        p->weight = v;
        return true;
    }
}

// =============== 4. 邻接多重表表示法 ===============
typedef struct EdgeNode {
    int ivex, jvex; // 该边依附的两个顶点的下标
    struct EdgeNode *ilink, *jlink; // 分别指向依附于ivex和jvex的下一条边
    EdgeType weight; // 边的权值
    bool visited; // 边是否被访问过，用于遍历
} EdgeNode;

typedef struct AMLNode {
    VertexType data; // 顶点信息
    EdgeNode *firstedge; // 指向依附于该顶点的第一条边
} AMLNode;

typedef struct {
    AMLNode adjmulist[MaxVertexNum]; // 顶点数组
    int vexnum, edgenum; // 顶点数和边数
} AMLGraph;

// 初始化邻接多重表表示的图
void InitAMLGraph(AMLGraph &G) {
    G.vexnum = 0;
    G.edgenum = 0;

    for (auto &i: G.adjmulist) {
        i.firstedge = nullptr;
    }
}

// 在邻接多重表中定位顶点的位置
int LocateVex_AML(const AMLGraph &G, VertexType x) {
    for (int i = 0; i < G.vexnum; i++) {
        if (G.adjmulist[i].data == x) {
            return i;
        }
    }
    return -1; // 顶点不存在
}

// Adjacent(G,x,y): 判断图G是否存在边(x,y)
bool Adjacent_AML(const AMLGraph &G, VertexType x, VertexType y) {
    int xIndex = LocateVex_AML(G, x);
    int yIndex = LocateVex_AML(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return false; // 顶点不存在
    }

    EdgeNode *p = G.adjmulist[xIndex].firstedge;

    while (p != nullptr) {
        if ((p->ivex == xIndex && p->jvex == yIndex) || (p->ivex == yIndex && p->jvex == xIndex)) {
            return true; // 边存在
        }

        // 沿着当前顶点的下一条边前进
        p = (p->ivex == xIndex) ? p->ilink : p->jlink;
    }

    return false; // 边不存在
}

// Neighbors(G,x): 列出图G中与顶点x邻接的边
vector<VertexType> Neighbors_AML(const AMLGraph &G, VertexType x) {
    vector<VertexType> neighbors;
    int xIndex = LocateVex_AML(G, x);

    if (xIndex == -1) {
        return neighbors; // 顶点不存在，返回空列表
    }

    EdgeNode *p = G.adjmulist[xIndex].firstedge;

    while (p != nullptr) {
        // 确定另一个顶点
        int neighborIndex = (p->ivex == xIndex) ? p->jvex : p->ivex;
        neighbors.push_back(G.adjmulist[neighborIndex].data);

        // 沿着当前顶点的下一条边前进
        p = (p->ivex == xIndex) ? p->ilink : p->jlink;
    }

    return neighbors;
}

// InsertVertex(G,x): 在图G中插入顶点x
bool InsertVertex_AML(AMLGraph &G, VertexType x) {
    // 检查图是否已满
    if (G.vexnum >= MaxVertexNum) {
        return false;
    }

    // 检查顶点是否已存在
    if (LocateVex_AML(G, x) != -1) {
        return false;
    }

    // 插入顶点
    G.adjmulist[G.vexnum].data = x;
    G.adjmulist[G.vexnum].firstedge = nullptr;

    G.vexnum++;
    return true;
}

// DeleteVertex(G,x): 从图G中删除顶点x
bool DeleteVertex_AML(AMLGraph &G, VertexType x) {
    int xIndex = LocateVex_AML(G, x);

    if (xIndex == -1) {
        return false; // 顶点不存在
    }

    // 删除所有与x相关的边
    EdgeNode *p = G.adjmulist[xIndex].firstedge;

    while (p != nullptr) {
        EdgeNode *q = p;

        // 确定另一个顶点
        int otherIndex = (p->ivex == xIndex) ? p->jvex : p->ivex;

        // 从另一个顶点的边链表中删除当前边
        if (G.adjmulist[otherIndex].firstedge == p) {
            if (p->ivex == otherIndex) {
                G.adjmulist[otherIndex].firstedge = p->ilink;
            } else {
                G.adjmulist[otherIndex].firstedge = p->jlink;
            }
        } else {
            EdgeNode *pre = G.adjmulist[otherIndex].firstedge;

            // 查找前驱
            while (pre != nullptr) {
                if (pre->ivex == otherIndex && pre->ilink == p) {
                    pre->ilink = p->ilink;
                    break;
                } else if (pre->jvex == otherIndex && pre->jlink == p) {
                    pre->jlink = p->jlink;
                    break;
                }

                // 沿着当前顶点的下一条边前进
                pre = (pre->ivex == otherIndex) ? pre->ilink : pre->jlink;
            }
        }

        // 沿着当前顶点的下一条边前进，但要先保存下一条边的指针
        p = (p->ivex == xIndex) ? p->ilink : p->jlink;

        delete q;
        G.edgenum--;
    }

    // 更新所有边中大于xIndex的顶点编号
    for (int i = 0; i < G.vexnum; i++) {
        if (i == xIndex)
            continue;

        p = G.adjmulist[i].firstedge;

        while (p != nullptr) {
            if (p->ivex > xIndex) {
                p->ivex--;
            }
            if (p->jvex > xIndex) {
                p->jvex--;
            }

            // 沿着当前顶点的下一条边前进
            p = (p->ivex == i) ? p->ilink : p->jlink;
        }
    }

    // 删除顶点，将后面的顶点前移
    for (int i = xIndex; i < G.vexnum - 1; i++) {
        G.adjmulist[i] = G.adjmulist[i + 1];
    }

    G.vexnum--;
    return true;
}

// AddEdge(G,x,y): 如果无向边(x,y)不存在，则向图G中添加该边
bool AddEdge_AML(AMLGraph &G, VertexType x, VertexType y, EdgeType weight = 1) {
    int xIndex = LocateVex_AML(G, x);
    int yIndex = LocateVex_AML(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return false; // 顶点不存在
    }

    // 检查边是否已存在
    if (Adjacent_AML(G, x, y)) {
        return false; // 边已存在
    }

    // 创建新边
    auto *newEdge = new EdgeNode;
    newEdge->ivex = xIndex;
    newEdge->jvex = yIndex;
    newEdge->weight = weight;
    newEdge->visited = false;

    // 插入到x的边链表中
    newEdge->ilink = G.adjmulist[xIndex].firstedge;
    G.adjmulist[xIndex].firstedge = newEdge;

    // 插入到y的边链表中
    newEdge->jlink = G.adjmulist[yIndex].firstedge;
    G.adjmulist[yIndex].firstedge = newEdge;

    G.edgenum++;
    return true;
}

// RemoveEdge(G,x,y): 如果无向边(x,y)存在，则从图G中删除该边
bool RemoveEdge_AML(AMLGraph &G, VertexType x, VertexType y) {
    int xIndex = LocateVex_AML(G, x);
    int yIndex = LocateVex_AML(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return false; // 顶点不存在
    }

    // 查找边(x,y)
    EdgeNode *p = G.adjmulist[xIndex].firstedge;
    EdgeNode *pre_x = nullptr;

    while (p != nullptr) {
        if ((p->ivex == xIndex && p->jvex == yIndex) || (p->ivex == yIndex && p->jvex == xIndex)) {
            break; // 找到边
        }

        pre_x = p;
        p = (p->ivex == xIndex) ? p->ilink : p->jlink;
    }

    if (p == nullptr) {
        return false; // 边不存在
    }

    // 从x的边链表中删除
    if (pre_x == nullptr) {
        G.adjmulist[xIndex].firstedge = (p->ivex == xIndex) ? p->ilink : p->jlink;
    } else {
        if (pre_x->ivex == xIndex) {
            pre_x->ilink = (p->ivex == xIndex) ? p->ilink : p->jlink;
        } else {
            pre_x->jlink = (p->ivex == xIndex) ? p->ilink : p->jlink;
        }
    }

    // 从y的边链表中删除
    EdgeNode *pre_y = nullptr;
    EdgeNode *q = G.adjmulist[yIndex].firstedge;

    while (q != p && q != nullptr) {
        pre_y = q;
        q = (q->ivex == yIndex) ? q->ilink : q->jlink;
    }

    if (pre_y == nullptr) {
        G.adjmulist[yIndex].firstedge = (p->ivex == yIndex) ? p->ilink : p->jlink;
    } else {
        if (pre_y->ivex == yIndex) {
            pre_y->ilink = (p->ivex == yIndex) ? p->ilink : p->jlink;
        } else {
            pre_y->jlink = (p->ivex == yIndex) ? p->ilink : p->jlink;
        }
    }

    delete p;
    G.edgenum--;
    return true;
}

// FirstNeighbor(G,x): 求图G中顶点x的第一个邻接点，若有则返回顶点号，若x没有邻接点或图中不存在x，则返回-1
int FirstNeighbor_AML(const AMLGraph &G, VertexType x) {
    int xIndex = LocateVex_AML(G, x);

    if (xIndex == -1) {
        return -1; // 顶点不存在
    }

    EdgeNode *p = G.adjmulist[xIndex].firstedge;

    if (p != nullptr) {
        // 返回边上的另一个顶点
        return (p->ivex == xIndex) ? p->jvex : p->ivex;
    }

    return -1; // 没有邻接点
}

// NextNeighbor(G,x,y): 假设图G中顶点y是顶点x的一个邻接点，返回除y外顶点x的下一个邻接点的顶点号，
// 若y是x的最后一个邻接点，则返回-1
int NextNeighbor_AML(const AMLGraph &G, VertexType x, VertexType y) {
    int xIndex = LocateVex_AML(G, x);
    int yIndex = LocateVex_AML(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return -1; // 顶点不存在
    }

    // 查找边(x,y)
    EdgeNode *p = G.adjmulist[xIndex].firstedge;
    while (p) {
        if ((p->ivex == xIndex && p->jvex == yIndex) || (p->ivex == yIndex && p->jvex == xIndex)) {
            break;
        }
        p = (p->ivex == xIndex) ? p->ilink : p->jlink;
    }
    if (!p)
        return -1; // y不是x的邻接点

    // 获取x的下一条边
    p = (p->ivex == xIndex) ? p->ilink : p->jlink;
    // if (!p)
    //     return -1; // 没有下一个邻接点

    // 返回边上的另一个顶点
    return (p->ivex == xIndex) ? p->jvex : p->ivex;
}

// Get_edge_value(G,x,y): 获取图G中边(x,y)对应的权值
EdgeType Get_edge_value_AML(const AMLGraph &G, VertexType x, VertexType y) {
    int xIndex = LocateVex_AML(G, x);
    int yIndex = LocateVex_AML(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return INFINITY; // 顶点不存在
    }

    EdgeNode *p = G.adjmulist[xIndex].firstedge;

    while (p != nullptr) {
        if ((p->ivex == xIndex && p->jvex == yIndex) || (p->ivex == yIndex && p->jvex == xIndex)) {
            return p->weight; // 返回边的权值
        }

        p = (p->ivex == xIndex) ? p->ilink : p->jlink;
    }

    return INFINITY; // 边不存在
}

// Set_edge_value(G,x,y,v): 设置图G中边(x,y)对应的权值为v
bool Set_edge_value_AML(AMLGraph &G, VertexType x, VertexType y, EdgeType v) {
    int xIndex = LocateVex_AML(G, x);
    int yIndex = LocateVex_AML(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return false; // 顶点不存在
    }

    EdgeNode *p = G.adjmulist[xIndex].firstedge;

    while (p != nullptr) {
        if ((p->ivex == xIndex && p->jvex == yIndex) || (p->ivex == yIndex && p->jvex == xIndex)) {
            if (v == INFINITY) {
                // 存在边但需要删除
                return RemoveEdge_AML(G, x, y);
            }

            // 存在边且需要更新权值
            p->weight = v;
            return true;
        }

        p = (p->ivex == xIndex) ? p->ilink : p->jlink;
    }

    if (v == INFINITY) {
        return true; // 边本来就不存在且权值为INFINITY，无需操作
    }

    // 边不存在且需要添加边
    return AddEdge_AML(G, x, y, v);
}

// 以邻接表为例，清空图
void ClearALGraph(ALGraph &G) {
    for (int i = 0; i < G.vexnum; ++i) {
        ArcNode *p = G.vertices[i].firstarc;
        while (p) {
            ArcNode *q = p;
            p = p->nextarc;
            delete q;
        }
        G.vertices[i].firstarc = nullptr;
    }
    G.vexnum = 0;
    G.arcnum = 0;
}


int main() {
    // 邻接矩阵测试
    MGraph mg;
    InitMGraph(mg);
    InsertVertex_M(mg, 'A');
    InsertVertex_M(mg, 'B');
    InsertVertex_M(mg, 'C');
    AddEdge_M(mg, 'A', 'B', 2);
    AddEdge_M(mg, 'B', 'C', 3);
    cout << "邻接矩阵A的邻居: ";
    for (auto v: Neighbors_M(mg, 'A'))
        cout << v << " ";
    cout << endl;

    // 邻接表测试
    ALGraph alg;
    InitALGraph(alg);
    InsertVertex_AL(alg, 'A');
    InsertVertex_AL(alg, 'B');
    InsertVertex_AL(alg, 'C');
    AddEdge_AL(alg, 'A', 'B', 1);
    AddEdge_AL(alg, 'A', 'C', 4);
    cout << "邻接表A的邻居: ";
    for (auto v: Neighbors_AL(alg, 'A'))
        cout << v << " ";
    cout << endl;

    // 十字链表测试
    OLGraph olg;
    InitOLGraph(olg);
    InsertVertex_OL(olg, 'A');
    InsertVertex_OL(olg, 'B');
    InsertVertex_OL(olg, 'C');
    AddEdge_OL(olg, 'A', 'B', 5);
    AddEdge_OL(olg, 'B', 'C', 6);
    cout << "十字链表A的邻居: ";
    for (auto v: Neighbors_OL(olg, 'A'))
        cout << v << " ";
    cout << endl;

    // 邻接多重表测试
    AMLGraph amlg;
    InitAMLGraph(amlg);
    InsertVertex_AML(amlg, 'A');
    InsertVertex_AML(amlg, 'B');
    InsertVertex_AML(amlg, 'C');
    AddEdge_AML(amlg, 'A', 'B', 7);
    AddEdge_AML(amlg, 'A', 'C', 8);
    cout << "邻接多重表A的邻居: ";
    for (auto v: Neighbors_AML(amlg, 'A'))
        cout << v << " ";
    cout << endl;

    // 测试删除边和顶点
    RemoveEdge_M(mg, 'A', 'B');
    DeleteVertex_AL(alg, 'B');
    RemoveEdge_OL(olg, 'A', 'B');
    DeleteVertex_AML(amlg, 'C');

    // 测试FirstNeighbor和NextNeighbor
    int idx = FirstNeighbor_M(mg, 'B');
    if (idx != -1)
        cout << "邻接矩阵B的第一个邻接点: " << mg.vex[idx] << endl;
    idx = NextNeighbor_M(mg, 'B', mg.vex[idx]);
    if (idx != -1)
        cout << "邻接矩阵B的下一个邻接点: " << mg.vex[idx] << endl;

    return 0;
}
