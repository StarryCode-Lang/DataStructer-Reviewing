#ifndef GRAPHOPERATION_H
#define GRAPHOPERATION_H


#include <vector>
using namespace std;

#define MaxVertexNum 100
#define INFINITY numeric_limits<int>::max()
typedef char VertexType; // 顶点的数据类型
typedef int EdgeType; // 边的权值类型
inline bool visited[MaxVertexNum] = {false}; // 访问标记数组
inline int path[MaxVertexNum][MaxVertexNum]; // 记录最短路径的前驱顶点

class Graph {
public:
    int vexnum; // 顶点数
    int arcnum; // 边/弧数（无向图/有向图）
    virtual ~Graph() = default;
};

// 1. 邻接矩阵表示法
struct MGraph : public Graph {
    VertexType vex[MaxVertexNum];
    EdgeType edge[MaxVertexNum][MaxVertexNum];
};

// 2. 邻接表表示法
struct ArcNode {
    int adjvex;
    ArcNode *nextarc;
    EdgeType weight;
};

struct VNode {
    VertexType data;
    ArcNode *firstarc;
};

struct ALGraph : public Graph {
    VNode vertices[MaxVertexNum];
};

// 3. 十字链表表示法
struct ArcBox {
    int tailvex, headvex;
    ArcBox *hlink, *tlink;
    EdgeType weight;
};

struct OLVNode {
    VertexType data;
    ArcBox *firstin, *firstout;
};

struct OLGraph : public Graph {
    OLVNode xlist[MaxVertexNum];
};

// 4. 邻接多重表表示法
struct EdgeNode {
    int ivex, jvex;
    EdgeNode *ilink, *jlink;
    EdgeType weight;
    bool visited;
};

struct AMLNode {
    VertexType data;
    EdgeNode *firstedge;
};

struct AMLGraph : public Graph {
    AMLNode adjmulist[MaxVertexNum];
    int edgenum; // 多重表特有，arcnum可用作边数也可省略
};

void visit(const Graph &G, int i);

// 遍历
void BFSTraverse(const Graph &G);
void BFS(const MGraph &G, int u);
void BFS(const ALGraph &G, int u);
void DFSTraverse(const Graph &G);
void DFS(const MGraph &G, int i);
void DFS(const ALGraph &G, int i);

// 邻接矩阵
void InitMGraph(MGraph &G);
int LocateVex_M(const MGraph &G, VertexType x);
bool Adjacent_M(const MGraph &G, VertexType x, VertexType y);
vector<VertexType> Neighbors_M(const MGraph &G, VertexType x);
bool InsertVertex_M(MGraph &G, VertexType x);
bool DeleteVertex_M(MGraph &G, VertexType x);
bool AddEdge_M(MGraph &G, VertexType x, VertexType y, EdgeType weight = 1);
bool RemoveEdge_M(MGraph &G, VertexType x, VertexType y);
int FirstNeighbor_M(const MGraph &G, VertexType x);
int NextNeighbor_M(const MGraph &G, VertexType x, VertexType y);
EdgeType Get_edge_value_M(const MGraph &G, VertexType x, VertexType y);
bool Set_edge_value_M(MGraph &G, VertexType x, VertexType y, EdgeType v);

// 邻接表
void InitALGraph(ALGraph &G);
int LocateVex_AL(const ALGraph &G, VertexType x);
bool Adjacent_AL(const ALGraph &G, VertexType x, VertexType y);
vector<VertexType> Neighbors_AL(const ALGraph &G, VertexType x);
bool InsertVertex_AL(ALGraph &G, VertexType x);
bool DeleteVertex_AL(ALGraph &G, VertexType x);
bool AddEdge_AL(ALGraph &G, VertexType x, VertexType y, EdgeType weight = 1);
bool RemoveEdge_AL(ALGraph &G, VertexType x, VertexType y);
int FirstNeighbor_AL(const ALGraph &G, VertexType x);
int NextNeighbor_AL(const ALGraph &G, VertexType x, VertexType y);
EdgeType Get_edge_value_AL(const ALGraph &G, VertexType x, VertexType y);
bool Set_edge_value_AL(ALGraph &G, VertexType x, VertexType y, EdgeType v);

// 十字链表
void InitOLGraph(OLGraph &G);
int LocateVex_OL(const OLGraph &G, VertexType x);
bool Adjacent_OL(const OLGraph &G, VertexType x, VertexType y);
vector<VertexType> Neighbors_OL(const OLGraph &G, VertexType x);
bool InsertVertex_OL(OLGraph &G, VertexType x);
bool DeleteVertex_OL(OLGraph &G, VertexType x);
bool AddEdge_OL(OLGraph &G, VertexType x, VertexType y, EdgeType weight = 1);
bool RemoveEdge_OL(OLGraph &G, VertexType x, VertexType y);
int FirstNeighbor_OL(const OLGraph &G, VertexType x);
int NextNeighbor_OL(const OLGraph &G, VertexType x, VertexType y);
EdgeType Get_edge_value_OL(const OLGraph &G, VertexType x, VertexType y);
bool Set_edge_value_OL(OLGraph &G, VertexType x, VertexType y, EdgeType v);

// 邻接多重表
void InitAMLGraph(AMLGraph &G);
int LocateVex_AML(const AMLGraph &G, VertexType x);
bool Adjacent_AML(const AMLGraph &G, VertexType x, VertexType y);
vector<VertexType> Neighbors_AML(const AMLGraph &G, VertexType x);
bool InsertVertex_AML(AMLGraph &G, VertexType x);
bool DeleteVertex_AML(AMLGraph &G, VertexType x);
bool AddEdge_AML(AMLGraph &G, VertexType x, VertexType y, EdgeType weight = 1);
bool RemoveEdge_AML(AMLGraph &G, VertexType x, VertexType y);
int FirstNeighbor_AML(const AMLGraph &G, VertexType x);
int NextNeighbor_AML(const AMLGraph &G, VertexType x, VertexType y);
EdgeType Get_edge_value_AML(const AMLGraph &G, VertexType x, VertexType y);
bool Set_edge_value_AML(AMLGraph &G, VertexType x, VertexType y, EdgeType v);

// 通用打印函数模板
void PrintGraph(const MGraph &G);
void PrintGraph(const ALGraph &G);
void PrintGraph(const OLGraph &G);
void PrintGraph(const AMLGraph &G);

// 打印距离矩阵
void PrintDistanceMatrix(const MGraph &G, int dist[][MaxVertexNum]);

#endif // GRAPHOPERATION_H
