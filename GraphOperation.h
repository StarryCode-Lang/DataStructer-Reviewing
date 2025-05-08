#ifndef GRAPHOPERATION_H
#define GRAPHOPERATION_H


#include <vector>
using namespace std;

#define MaxVertexNum 100
#define INFINITY numeric_limits<int>::max()
typedef char VertexType; // 顶点的数据类型
typedef int EdgeType; // 边的权值类型

// 结构体定义
// 1. 邻接矩阵表示法
typedef struct {
    VertexType vex[MaxVertexNum]; // 顶点数组
    EdgeType edge[MaxVertexNum][MaxVertexNum]; // 邻接矩阵，存储边的权值
    int vexnum, arcnum; // 图的当前顶点数和边数
} MGraph;

// 2. 邻接表表示法
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

// 3. 十字链表表示法
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

// 4. 邻接多重表表示法
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
void PrintMGraph(const MGraph &G);

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
void PrintALGraph(const ALGraph &G);

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
void PrintOLGraph(const OLGraph &G);

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
void PrintAMLGraph(const AMLGraph &G);


#endif // GRAPHOPERATION_H
