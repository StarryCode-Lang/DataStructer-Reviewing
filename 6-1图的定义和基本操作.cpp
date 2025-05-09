/**
 * �ļ�����graph_operations.cpp
 * ������ʵ��ͼ�Ļ����������������ִ洢��ʽ���ڽӾ����ڽӱ�ʮ��������ڽӶ��ر�
 * �����Ĳ�����Adjacent��Neighbors��InsertVertex��DeleteVertex��AddEdge��RemoveEdge��
 *           FirstNeighbor��NextNeighbor��Get_edge_value��Set_edge_value
 */

#include <iostream>
#include <limits>
#include <vector>
#include "6ͼ�Ķ���.h"


// =============== 1. �ڽӾ����ʾ�� ===============
// ��ʼ���ڽӾ����ʾ��ͼ
void InitMGraph(MGraph &G) {
    G.vexnum = 0;
    G.arcnum = 0;
    // ��ʼ���ڽӾ������бߵ�Ȩֵ��Ϊ����󣬱�ʾ����ͨ
    for (int i = 0; i < MaxVertexNum; i++) {
        for (int j = 0; j < MaxVertexNum; j++) {
            G.edge[i][j] = INFINITY;
        }
        G.edge[i][i] = 0; // �Ի���Ϊ0
    }
}

// ���ڽӾ����ж�λ�����λ��
int LocateVex_M(const MGraph &G, VertexType x) {
    for (int i = 0; i < G.vexnum; i++) {
        if (G.vex[i] == x) {
            return i;
        }
    }
    return -1; // ���㲻����
}

// Adjacent(G,x,y): �ж�ͼG�Ƿ���ڱ�<x,y>��(x,y)
bool Adjacent_M(const MGraph &G, VertexType x, VertexType y) {
    int xIndex = LocateVex_M(G, x);
    int yIndex = LocateVex_M(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return false; // ���㲻����
    }

    return G.edge[xIndex][yIndex] != INFINITY;
}

// Neighbors(G,x): �г�ͼG���붥��x�ڽӵı�
vector<VertexType> Neighbors_M(const MGraph &G, VertexType x) {
    vector<VertexType> neighbors;
    int xIndex = LocateVex_M(G, x);

    if (xIndex == -1) {
        return neighbors; // ���㲻���ڣ����ؿ��б�
    }

    for (int i = 0; i < G.vexnum; i++) {
        if (G.edge[xIndex][i] != INFINITY && i != xIndex) {
            neighbors.push_back(G.vex[i]);
        }
    }

    return neighbors;
}

// InsertVertex(G,x): ��ͼG�в��붥��x
bool InsertVertex_M(MGraph &G, VertexType x) {
    // ���ͼ�Ƿ�����
    if (G.vexnum >= MaxVertexNum) {
        return false;
    }

    // ��鶥���Ƿ��Ѵ���
    if (LocateVex_M(G, x) != -1) {
        return false;
    }

    // ���붥��
    G.vex[G.vexnum] = x;

    // ��ʼ���¶���ı�
    for (int i = 0; i <= G.vexnum; i++) {
        G.edge[G.vexnum][i] = INFINITY;
        G.edge[i][G.vexnum] = INFINITY;
    }
    G.edge[G.vexnum][G.vexnum] = 0; // �Ի���Ϊ0

    G.vexnum++;
    return true;
}

// DeleteVertex(G,x): ��ͼG��ɾ������x
bool DeleteVertex_M(MGraph &G, VertexType x) {
    int xIndex = LocateVex_M(G, x);

    if (xIndex == -1) {
        return false; // ���㲻����
    }

    // ���±���
    for (int i = 0; i < G.vexnum; i++) {
        if (G.edge[xIndex][i] != INFINITY && i != xIndex) {
            G.arcnum--;
        }
        if (G.edge[i][xIndex] != INFINITY && i != xIndex) {
            // ���������ͼ����Ҫ��ȥ�������
            G.arcnum--;
        }
    }

    // ɾ�����㣬������Ķ���ǰ��
    for (int i = xIndex; i < G.vexnum - 1; i++) {
        G.vex[i] = G.vex[i + 1];
    }

    // �����ڽӾ���
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

// AddEdge(G,x,y): ��������(x,y)�������<x,y>�����ڣ�����ͼG����Ӹñ�
bool AddEdge_M(MGraph &G, VertexType x, VertexType y, EdgeType weight) {
    int xIndex = LocateVex_M(G, x);
    int yIndex = LocateVex_M(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return false; // ���㲻����
    }

    if (G.edge[xIndex][yIndex] != INFINITY) {
        return false; // ���Ѵ���
    }

    G.edge[xIndex][yIndex] = weight;
    G.arcnum++;
    return true;
}

// RemoveEdge(G,x,y): ��������(x,y)�������<x,y>���ڣ����ͼG��ɾ���ñ�
bool RemoveEdge_M(MGraph &G, VertexType x, VertexType y) {
    int xIndex = LocateVex_M(G, x);
    int yIndex = LocateVex_M(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return false; // ���㲻����
    }

    if (G.edge[xIndex][yIndex] == INFINITY) {
        return false; // �߲�����
    }

    G.edge[xIndex][yIndex] = INFINITY;
    G.arcnum--;
    return true;
}

// FirstNeighbor(G,x): ��ͼG�ж���x�ĵ�һ���ڽӵ㣬�����򷵻ض���ţ���xû���ڽӵ��ͼ�в�����x���򷵻�-1
int FirstNeighbor_M(const MGraph &G, VertexType x) {
    int xIndex = LocateVex_M(G, x);

    if (xIndex == -1) {
        return -1; // ���㲻����
    }

    for (int i = 0; i < G.vexnum; i++) {
        if (G.edge[xIndex][i] != INFINITY && i != xIndex) {
            return i;
        }
    }

    return -1; // û���ڽӵ�
}

// NextNeighbor(G,x,y):
// ����ͼG�ж���y�Ƕ���x��һ���ڽӵ㣬���س�y�ⶥ��x����һ���ڽӵ�Ķ���ţ���y��x�����һ���ڽӵ㣬�򷵻�-1
int NextNeighbor_M(const MGraph &G, VertexType x, VertexType y) {
    int xIndex = LocateVex_M(G, x);
    int yIndex = LocateVex_M(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return -1; // ���㲻����
    }

    if (G.edge[xIndex][yIndex] == INFINITY) {
        return -1; // y����x���ڽӵ�
    }

    for (int i = yIndex + 1; i < G.vexnum; i++) {
        if (G.edge[xIndex][i] != INFINITY && i != xIndex) {
            return i;
        }
    }

    return -1; // û����һ���ڽӵ�
}

// Get_edge_value(G,x,y): ��ȡͼG�б�(x,y)��<x,y>��Ӧ��Ȩֵ
EdgeType Get_edge_value_M(const MGraph &G, VertexType x, VertexType y) {
    int xIndex = LocateVex_M(G, x);
    int yIndex = LocateVex_M(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return INFINITY; // ���㲻����
    }

    return G.edge[xIndex][yIndex];
}

// Set_edge_value(G,x,y,v): ����ͼG�б�(x,y)��<x,y>��Ӧ��ȨֵΪv
bool Set_edge_value_M(MGraph &G, VertexType x, VertexType y, EdgeType v) {
    int xIndex = LocateVex_M(G, x);
    int yIndex = LocateVex_M(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return false; // ���㲻����
    }

    if (G.edge[xIndex][yIndex] == INFINITY && v != INFINITY) {
        G.arcnum++; // ���ԭ�������ڱߣ���������˱ߣ�������1
    } else if (G.edge[xIndex][yIndex] != INFINITY && v == INFINITY) {
        G.arcnum--; // ���ԭ�����ڱߣ�����ɾ���˱ߣ�������1
    }

    G.edge[xIndex][yIndex] = v;
    return true;
}

// =============== 2. �ڽӱ��ʾ�� ===============
// ��ʼ���ڽӱ��ʾ��ͼ
void InitALGraph(ALGraph &G) {
    G.vexnum = 0;
    G.arcnum = 0;

    for (auto &vertice: G.vertices) {
        vertice.firstarc = nullptr;
    }
}

// ���ڽӱ��ж�λ�����λ��
int LocateVex_AL(const ALGraph &G, VertexType x) {
    for (int i = 0; i < G.vexnum; i++) {
        if (G.vertices[i].data == x) {
            return i;
        }
    }
    return -1; // ���㲻����
}

// Adjacent(G,x,y): �ж�ͼG�Ƿ���ڱ�<x,y>��(x,y)
bool Adjacent_AL(const ALGraph &G, VertexType x, VertexType y) {
    int xIndex = LocateVex_AL(G, x);
    int yIndex = LocateVex_AL(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return false; // ���㲻����
    }

    ArcNode *p = G.vertices[xIndex].firstarc;
    while (p != nullptr) {
        if (p->adjvex == yIndex) {
            return true; // �ߴ���
        }
        p = p->nextarc;
    }

    return false; // �߲�����
}

// Neighbors(G,x): �г�ͼG���붥��x�ڽӵı�
vector<VertexType> Neighbors_AL(const ALGraph &G, VertexType x) {
    vector<VertexType> neighbors;
    int xIndex = LocateVex_AL(G, x);

    if (xIndex == -1) {
        return neighbors; // ���㲻���ڣ����ؿ��б�
    }

    ArcNode *p = G.vertices[xIndex].firstarc;
    while (p != nullptr) {
        neighbors.push_back(G.vertices[p->adjvex].data);
        p = p->nextarc;
    }

    return neighbors;
}

// InsertVertex(G,x): ��ͼG�в��붥��x
bool InsertVertex_AL(ALGraph &G, VertexType x) {
    // ���ͼ�Ƿ�����
    if (G.vexnum >= MaxVertexNum) {
        return false;
    }

    // ��鶥���Ƿ��Ѵ���
    if (LocateVex_AL(G, x) != -1) {
        return false;
    }

    // ���붥��
    G.vertices[G.vexnum].data = x;
    G.vertices[G.vexnum].firstarc = nullptr;

    G.vexnum++;
    return true;
}

// DeleteVertex(G,x): ��ͼG��ɾ������x
bool DeleteVertex_AL(ALGraph &G, VertexType x) {
    int xIndex = LocateVex_AL(G, x);

    if (xIndex == -1) {
        return false; // ���㲻����
    }

    // ɾ����xΪ�������б�
    ArcNode *p = G.vertices[xIndex].firstarc;
    ArcNode *q;
    while (p != nullptr) {
        q = p;
        p = p->nextarc;
        delete q;
        G.arcnum--;
    }

    // ɾ����xΪ�յ�����б�
    for (int i = 0; i < G.vexnum; i++) {
        if (i == xIndex)
            continue;

        p = G.vertices[i].firstarc;
        q = nullptr;

        while (p != nullptr && p->adjvex != xIndex) {
            q = p;
            p = p->nextarc;
        }

        if (p != nullptr) { // �ҵ�����xΪ�յ�ı�
            if (q == nullptr) { // �ǵ�һ����
                G.vertices[i].firstarc = p->nextarc;
            } else {
                q->nextarc = p->nextarc;
            }
            delete p;
            G.arcnum--;
        }
    }

    // �������ж���ı߱��д���xIndex�Ľڵ�ֵ
    for (int i = 0; i < G.vexnum; i++) {
        p = G.vertices[i].firstarc;

        while (p != nullptr) {
            if (p->adjvex > xIndex) {
                p->adjvex--; // �±��1
            }
            p = p->nextarc;
        }
    }

    // ɾ�����㣬������Ķ���ǰ��
    for (int i = xIndex; i < G.vexnum - 1; i++) {
        G.vertices[i] = G.vertices[i + 1];
    }

    G.vexnum--;
    return true;
}

// AddEdge(G,x,y): ��������(x,y)�������<x,y>�����ڣ�����ͼG����Ӹñ�
bool AddEdge_AL(ALGraph &G, VertexType x, VertexType y, EdgeType weight) {
    int xIndex = LocateVex_AL(G, x);
    int yIndex = LocateVex_AL(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return false; // ���㲻����
    }

    // �����Ƿ��Ѵ���
    ArcNode *p = G.vertices[xIndex].firstarc;
    while (p != nullptr) {
        if (p->adjvex == yIndex) {
            return false; // ���Ѵ���
        }
        p = p->nextarc;
    }

    // �����±�
    auto *newArc = new ArcNode;
    newArc->adjvex = yIndex;
    newArc->weight = weight;
    newArc->nextarc = G.vertices[xIndex].firstarc;
    G.vertices[xIndex].firstarc = newArc;

    G.arcnum++;
    return true;
}

// RemoveEdge(G,x,y): ��������(x,y)�������<x,y>���ڣ����ͼG��ɾ���ñ�
bool RemoveEdge_AL(ALGraph &G, VertexType x, VertexType y) {
    int xIndex = LocateVex_AL(G, x);
    int yIndex = LocateVex_AL(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return false; // ���㲻����
    }

    ArcNode *p = G.vertices[xIndex].firstarc;
    ArcNode *q = nullptr;

    // ���ұ�
    while (p != nullptr && p->adjvex != yIndex) {
        q = p;
        p = p->nextarc;
    }

    if (p == nullptr) {
        return false; // �߲�����
    }

    // ɾ����
    if (q == nullptr) { // �ǵ�һ����
        G.vertices[xIndex].firstarc = p->nextarc;
    } else {
        q->nextarc = p->nextarc;
    }

    delete p;
    G.arcnum--;
    return true;
}

// FirstNeighbor(G,x): ��ͼG�ж���x�ĵ�һ���ڽӵ㣬�����򷵻ض���ţ���xû���ڽӵ��ͼ�в�����x���򷵻�-1
int FirstNeighbor_AL(const ALGraph &G, VertexType x) {
    int xIndex = LocateVex_AL(G, x);

    if (xIndex == -1) {
        return -1; // ���㲻����
    }

    if (G.vertices[xIndex].firstarc != nullptr) {
        return G.vertices[xIndex].firstarc->adjvex;
    }

    return -1; // û���ڽӵ�
}

// NextNeighbor(G,x,y):
// ����ͼG�ж���y�Ƕ���x��һ���ڽӵ㣬���س�y�ⶥ��x����һ���ڽӵ�Ķ���ţ���y��x�����һ���ڽӵ㣬�򷵻�-1
int NextNeighbor_AL(const ALGraph &G, VertexType x, VertexType y) {
    int xIndex = LocateVex_AL(G, x);
    int yIndex = LocateVex_AL(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return -1; // ���㲻����
    }

    ArcNode *p = G.vertices[xIndex].firstarc;

    // ���ұ�x->y
    while (p != nullptr && p->adjvex != yIndex) {
        p = p->nextarc;
    }

    if (p == nullptr || p->nextarc == nullptr) {
        return -1; // �߲����ڻ�y�����һ���ڽӵ�
    }

    return p->nextarc->adjvex;
}

// Get_edge_value(G,x,y): ��ȡͼG�б�(x,y)��<x,y>��Ӧ��Ȩֵ
EdgeType Get_edge_value_AL(const ALGraph &G, VertexType x, VertexType y) {
    int xIndex = LocateVex_AL(G, x);
    int yIndex = LocateVex_AL(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return INFINITY; // ���㲻����
    }

    ArcNode *p = G.vertices[xIndex].firstarc;

    while (p != nullptr) {
        if (p->adjvex == yIndex) {
            return p->weight; // ���رߵ�Ȩֵ
        }
        p = p->nextarc;
    }

    return INFINITY; // �߲�����
}

// Set_edge_value(G,x,y,v): ����ͼG�б�(x,y)��<x,y>��Ӧ��ȨֵΪv
bool Set_edge_value_AL(ALGraph &G, VertexType x, VertexType y, EdgeType v) {
    int xIndex = LocateVex_AL(G, x);
    int yIndex = LocateVex_AL(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return false; // ���㲻����
    }

    ArcNode *p = G.vertices[xIndex].firstarc;

    // ���ұ�
    while (p != nullptr && p->adjvex != yIndex) {
        p = p->nextarc;
    }

    if (p == nullptr) {
        if (v == INFINITY) {
            return true; // �߱����Ͳ�������ȨֵΪINFINITY���������
        }

        // �߲���������Ҫ��ӱ�
        return AddEdge_AL(G, x, y, v);
    } else {
        if (v == INFINITY) {
            // ���ڱߵ���Ҫɾ��
            return RemoveEdge_AL(G, x, y);
        }

        // ���ڱ�����Ҫ����Ȩֵ
        p->weight = v;
        return true;
    }
}

// =============== 3. ʮ�������ʾ�� ===============
// ��ʼ��ʮ�������ʾ��ͼ
void InitOLGraph(OLGraph &G) {
    G.vexnum = 0;
    G.arcnum = 0;

    for (auto &i: G.xlist) {
        i.firstin = nullptr;
        i.firstout = nullptr;
    }
}

// ��ʮ�������ж�λ�����λ��
int LocateVex_OL(const OLGraph &G, VertexType x) {
    for (int i = 0; i < G.vexnum; i++) {
        if (G.xlist[i].data == x) {
            return i;
        }
    }
    return -1; // ���㲻����
}

// Adjacent(G,x,y): �ж�ͼG�Ƿ���ڱ�<x,y>��(x,y)
bool Adjacent_OL(const OLGraph &G, VertexType x, VertexType y) {
    int xIndex = LocateVex_OL(G, x);
    int yIndex = LocateVex_OL(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return false; // ���㲻����
    }

    ArcBox *p = G.xlist[xIndex].firstout;
    while (p != nullptr) {
        if (p->headvex == yIndex) {
            return true; // �ߴ���
        }
        p = p->tlink;
    }

    return false; // �߲�����
}

// Neighbors(G,x): �г�ͼG���붥��x�ڽӵı�
vector<VertexType> Neighbors_OL(const OLGraph &G, VertexType x) {
    vector<VertexType> neighbors;
    int xIndex = LocateVex_OL(G, x);

    if (xIndex == -1) {
        return neighbors; // ���㲻���ڣ����ؿ��б�
    }

    ArcBox *p = G.xlist[xIndex].firstout;
    while (p != nullptr) {
        neighbors.push_back(G.xlist[p->headvex].data);
        p = p->tlink;
    }

    return neighbors;
}

// InsertVertex(G,x): ��ͼG�в��붥��x
bool InsertVertex_OL(OLGraph &G, VertexType x) {
    // ���ͼ�Ƿ�����
    if (G.vexnum >= MaxVertexNum) {
        return false;
    }

    // ��鶥���Ƿ��Ѵ���
    if (LocateVex_OL(G, x) != -1) {
        return false;
    }

    // ���붥��
    G.xlist[G.vexnum].data = x;
    G.xlist[G.vexnum].firstin = nullptr;
    G.xlist[G.vexnum].firstout = nullptr;

    G.vexnum++;
    return true;
}

// DeleteVertex(G,x): ��ͼG��ɾ������x
bool DeleteVertex_OL(OLGraph &G, VertexType x) {
    int xIndex = LocateVex_OL(G, x);

    if (xIndex == -1) {
        return false; // ���㲻����
    }

    // ɾ����xΪβ�����л�
    ArcBox *p = G.xlist[xIndex].firstout;
    ArcBox *q;

    while (p != nullptr) {
        // �ӻ�ͷ��������ɾ���û�
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

    // ɾ����xΪͷ�����л�
    p = G.xlist[xIndex].firstin;

    while (p != nullptr) {
        // �ӻ�β��������ɾ���û�
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

    // �������ж���Ļ��д���xIndex�Ķ�����
    for (int i = 0; i < G.vexnum; i++) {
        // ���³���
        p = G.xlist[i].firstout;
        while (p != nullptr) {
            if (p->headvex > xIndex) {
                p->headvex--; // �±��1
            }
            p = p->tlink;
        }

        // �����뻡
        p = G.xlist[i].firstin;
        while (p != nullptr) {
            if (p->tailvex > xIndex) {
                p->tailvex--; // �±��1
            }
            p = p->hlink;
        }
    }

    // ɾ�����㣬������Ķ���ǰ��
    for (int i = xIndex; i < G.vexnum - 1; i++) {
        G.xlist[i] = G.xlist[i + 1];
    }

    G.vexnum--;
    return true;
}

// AddEdge(G,x,y): ��������<x,y>�����ڣ�����ͼG����Ӹñ�
bool AddEdge_OL(OLGraph &G, VertexType x, VertexType y, EdgeType weight) {
    int xIndex = LocateVex_OL(G, x);
    int yIndex = LocateVex_OL(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return false; // ���㲻����
    }

    // �����Ƿ��Ѵ���
    ArcBox *p = G.xlist[xIndex].firstout;
    while (p != nullptr) {
        if (p->headvex == yIndex) {
            return false; // ���Ѵ���
        }
        p = p->tlink;
    }

    // �����»�
    auto *newArc = new ArcBox;
    newArc->tailvex = xIndex;
    newArc->headvex = yIndex;
    newArc->weight = weight;

    // ���뵽����������
    newArc->tlink = G.xlist[xIndex].firstout;
    G.xlist[xIndex].firstout = newArc;

    // ���뵽�뻡������
    newArc->hlink = G.xlist[yIndex].firstin;
    G.xlist[yIndex].firstin = newArc;

    G.arcnum++;
    return true;
}

// RemoveEdge(G,x,y): ��������<x,y>���ڣ����ͼG��ɾ���ñ�
bool RemoveEdge_OL(OLGraph &G, VertexType x, VertexType y) {
    int xIndex = LocateVex_OL(G, x);
    int yIndex = LocateVex_OL(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return false; // ���㲻����
    }

    // ���ұ�x->y
    ArcBox *p = G.xlist[xIndex].firstout;
    ArcBox *pre = nullptr;

    while (p != nullptr && p->headvex != yIndex) {
        pre = p;
        p = p->tlink;
    }

    if (p == nullptr) {
        return false; // �߲�����
    }

    // �ӳ���������ɾ��
    if (pre == nullptr) {
        G.xlist[xIndex].firstout = p->tlink;
    } else {
        pre->tlink = p->tlink;
    }

    // ���뻡������ɾ��
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

// FirstNeighbor(G,x): ��ͼG�ж���x�ĵ�һ���ڽӵ㣬�����򷵻ض���ţ���xû���ڽӵ��ͼ�в�����x���򷵻�-1
int FirstNeighbor_OL(const OLGraph &G, VertexType x) {
    int xIndex = LocateVex_OL(G, x);

    if (xIndex == -1) {
        return -1; // ���㲻����
    }

    if (G.xlist[xIndex].firstout != nullptr) {
        return G.xlist[xIndex].firstout->headvex;
    }

    return -1; // û���ڽӵ�
}

// NextNeighbor(G,x,y):
// ����ͼG�ж���y�Ƕ���x��һ���ڽӵ㣬���س�y�ⶥ��x����һ���ڽӵ�Ķ���ţ���y��x�����һ���ڽӵ㣬�򷵻�-1
int NextNeighbor_OL(const OLGraph &G, VertexType x, VertexType y) {
    int xIndex = LocateVex_OL(G, x);
    int yIndex = LocateVex_OL(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return -1; // ���㲻����
    }

    ArcBox *p = G.xlist[xIndex].firstout;

    // ���ұ�x->y
    while (p != nullptr && p->headvex != yIndex) {
        p = p->tlink;
    }

    if (p == nullptr || p->tlink == nullptr) {
        return -1; // �߲����ڻ�y�����һ���ڽӵ�
    }

    return p->tlink->headvex;
}

// Get_edge_value(G,x,y): ��ȡͼG�б�<x,y>��Ӧ��Ȩֵ
EdgeType Get_edge_value_OL(const OLGraph &G, VertexType x, VertexType y) {
    int xIndex = LocateVex_OL(G, x);
    int yIndex = LocateVex_OL(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return INFINITY; // ���㲻����
    }

    ArcBox *p = G.xlist[xIndex].firstout;

    while (p != nullptr) {
        if (p->headvex == yIndex) {
            return p->weight; // ���رߵ�Ȩֵ
        }
        p = p->tlink;
    }

    return INFINITY; // �߲�����
}

// Set_edge_value(G,x,y,v): ����ͼG�б�<x,y>��Ӧ��ȨֵΪv
bool Set_edge_value_OL(OLGraph &G, VertexType x, VertexType y, EdgeType v) {
    int xIndex = LocateVex_OL(G, x);
    int yIndex = LocateVex_OL(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return false; // ���㲻����
    }

    ArcBox *p = G.xlist[xIndex].firstout;

    // ���ұ�
    while (p != nullptr && p->headvex != yIndex) {
        p = p->tlink;
    }

    if (p == nullptr) {
        if (v == INFINITY) {
            return true; // �߱����Ͳ�������ȨֵΪINFINITY���������
        }

        // �߲���������Ҫ��ӱ�
        return AddEdge_OL(G, x, y, v);
    } else {
        if (v == INFINITY) {
            // ���ڱߵ���Ҫɾ��
            return RemoveEdge_OL(G, x, y);
        }

        // ���ڱ�����Ҫ����Ȩֵ
        p->weight = v;
        return true;
    }
}

// =============== 4. �ڽӶ��ر��ʾ�� ===============
// ��ʼ���ڽӶ��ر��ʾ��ͼ
void InitAMLGraph(AMLGraph &G) {
    G.vexnum = 0;
    G.edgenum = 0;

    for (auto &i: G.adjmulist) {
        i.firstedge = nullptr;
    }
}

// ���ڽӶ��ر��ж�λ�����λ��
int LocateVex_AML(const AMLGraph &G, VertexType x) {
    for (int i = 0; i < G.vexnum; i++) {
        if (G.adjmulist[i].data == x) {
            return i;
        }
    }
    return -1; // ���㲻����
}

// Adjacent(G,x,y): �ж�ͼG�Ƿ���ڱ�(x,y)
bool Adjacent_AML(const AMLGraph &G, VertexType x, VertexType y) {
    int xIndex = LocateVex_AML(G, x);
    int yIndex = LocateVex_AML(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return false; // ���㲻����
    }

    EdgeNode *p = G.adjmulist[xIndex].firstedge;

    while (p != nullptr) {
        if ((p->ivex == xIndex && p->jvex == yIndex) || (p->ivex == yIndex && p->jvex == xIndex)) {
            return true; // �ߴ���
        }

        // ���ŵ�ǰ�������һ����ǰ��
        p = (p->ivex == xIndex) ? p->ilink : p->jlink;
    }

    return false; // �߲�����
}

// Neighbors(G,x): �г�ͼG���붥��x�ڽӵı�
vector<VertexType> Neighbors_AML(const AMLGraph &G, VertexType x) {
    vector<VertexType> neighbors;
    int xIndex = LocateVex_AML(G, x);

    if (xIndex == -1) {
        return neighbors; // ���㲻���ڣ����ؿ��б�
    }

    EdgeNode *p = G.adjmulist[xIndex].firstedge;

    while (p != nullptr) {
        // ȷ����һ������
        int neighborIndex = (p->ivex == xIndex) ? p->jvex : p->ivex;
        neighbors.push_back(G.adjmulist[neighborIndex].data);

        // ���ŵ�ǰ�������һ����ǰ��
        p = (p->ivex == xIndex) ? p->ilink : p->jlink;
    }

    return neighbors;
}

// InsertVertex(G,x): ��ͼG�в��붥��x
bool InsertVertex_AML(AMLGraph &G, VertexType x) {
    // ���ͼ�Ƿ�����
    if (G.vexnum >= MaxVertexNum) {
        return false;
    }

    // ��鶥���Ƿ��Ѵ���
    if (LocateVex_AML(G, x) != -1) {
        return false;
    }

    // ���붥��
    G.adjmulist[G.vexnum].data = x;
    G.adjmulist[G.vexnum].firstedge = nullptr;

    G.vexnum++;
    return true;
}

// DeleteVertex(G,x): ��ͼG��ɾ������x
bool DeleteVertex_AML(AMLGraph &G, VertexType x) {
    int xIndex = LocateVex_AML(G, x);

    if (xIndex == -1) {
        return false; // ���㲻����
    }

    // ɾ��������x��صı�
    EdgeNode *p = G.adjmulist[xIndex].firstedge;

    while (p != nullptr) {
        EdgeNode *q = p;

        // ȷ����һ������
        int otherIndex = (p->ivex == xIndex) ? p->jvex : p->ivex;

        // ����һ������ı�������ɾ����ǰ��
        if (G.adjmulist[otherIndex].firstedge == p) {
            if (p->ivex == otherIndex) {
                G.adjmulist[otherIndex].firstedge = p->ilink;
            } else {
                G.adjmulist[otherIndex].firstedge = p->jlink;
            }
        } else {
            EdgeNode *pre = G.adjmulist[otherIndex].firstedge;

            // ����ǰ��
            while (pre != nullptr) {
                if (pre->ivex == otherIndex && pre->ilink == p) {
                    pre->ilink = p->ilink;
                    break;
                } else if (pre->jvex == otherIndex && pre->jlink == p) {
                    pre->jlink = p->jlink;
                    break;
                }

                // ���ŵ�ǰ�������һ����ǰ��
                pre = (pre->ivex == otherIndex) ? pre->ilink : pre->jlink;
            }
        }

        // ���ŵ�ǰ�������һ����ǰ������Ҫ�ȱ�����һ���ߵ�ָ��
        p = (p->ivex == xIndex) ? p->ilink : p->jlink;

        delete q;
        G.edgenum--;
    }

    // �������б��д���xIndex�Ķ�����
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

            // ���ŵ�ǰ�������һ����ǰ��
            p = (p->ivex == i) ? p->ilink : p->jlink;
        }
    }

    // ɾ�����㣬������Ķ���ǰ��
    for (int i = xIndex; i < G.vexnum - 1; i++) {
        G.adjmulist[i] = G.adjmulist[i + 1];
    }

    G.vexnum--;
    return true;
}

// AddEdge(G,x,y): ��������(x,y)�����ڣ�����ͼG����Ӹñ�
bool AddEdge_AML(AMLGraph &G, VertexType x, VertexType y, EdgeType weight) {
    int xIndex = LocateVex_AML(G, x);
    int yIndex = LocateVex_AML(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return false; // ���㲻����
    }

    // �����Ƿ��Ѵ���
    if (Adjacent_AML(G, x, y)) {
        return false; // ���Ѵ���
    }

    // �����±�
    auto *newEdge = new EdgeNode;
    newEdge->ivex = xIndex;
    newEdge->jvex = yIndex;
    newEdge->weight = weight;
    newEdge->visited = false;

    // ���뵽x�ı�������
    newEdge->ilink = G.adjmulist[xIndex].firstedge;
    G.adjmulist[xIndex].firstedge = newEdge;

    // ���뵽y�ı�������
    newEdge->jlink = G.adjmulist[yIndex].firstedge;
    G.adjmulist[yIndex].firstedge = newEdge;

    G.edgenum++;
    return true;
}

// RemoveEdge(G,x,y): ��������(x,y)���ڣ����ͼG��ɾ���ñ�
bool RemoveEdge_AML(AMLGraph &G, VertexType x, VertexType y) {
    int xIndex = LocateVex_AML(G, x);
    int yIndex = LocateVex_AML(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return false; // ���㲻����
    }

    // ���ұ�(x,y)
    EdgeNode *p = G.adjmulist[xIndex].firstedge;
    EdgeNode *pre_x = nullptr;

    while (p != nullptr) {
        if ((p->ivex == xIndex && p->jvex == yIndex) || (p->ivex == yIndex && p->jvex == xIndex)) {
            break; // �ҵ���
        }

        pre_x = p;
        p = (p->ivex == xIndex) ? p->ilink : p->jlink;
    }

    if (p == nullptr) {
        return false; // �߲�����
    }

    // ��x�ı�������ɾ��
    if (pre_x == nullptr) {
        G.adjmulist[xIndex].firstedge = (p->ivex == xIndex) ? p->ilink : p->jlink;
    } else {
        if (pre_x->ivex == xIndex) {
            pre_x->ilink = (p->ivex == xIndex) ? p->ilink : p->jlink;
        } else {
            pre_x->jlink = (p->ivex == xIndex) ? p->ilink : p->jlink;
        }
    }

    // ��y�ı�������ɾ��
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

// FirstNeighbor(G,x): ��ͼG�ж���x�ĵ�һ���ڽӵ㣬�����򷵻ض���ţ���xû���ڽӵ��ͼ�в�����x���򷵻�-1
int FirstNeighbor_AML(const AMLGraph &G, VertexType x) {
    int xIndex = LocateVex_AML(G, x);

    if (xIndex == -1) {
        return -1; // ���㲻����
    }

    EdgeNode *p = G.adjmulist[xIndex].firstedge;

    if (p != nullptr) {
        // ���ر��ϵ���һ������
        return (p->ivex == xIndex) ? p->jvex : p->ivex;
    }

    return -1; // û���ڽӵ�
}

// NextNeighbor(G,x,y):
// ����ͼG�ж���y�Ƕ���x��һ���ڽӵ㣬���س�y�ⶥ��x����һ���ڽӵ�Ķ���ţ���y��x�����һ���ڽӵ㣬�򷵻�-1
int NextNeighbor_AML(const AMLGraph &G, VertexType x, VertexType y) {
    int xIndex = LocateVex_AML(G, x);
    int yIndex = LocateVex_AML(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return -1; // ���㲻����
    }

    // ���ұ�(x,y)
    EdgeNode *p = G.adjmulist[xIndex].firstedge;
    while (p) {
        if ((p->ivex == xIndex && p->jvex == yIndex) || (p->ivex == yIndex && p->jvex == xIndex)) {
            break;
        }
        p = (p->ivex == xIndex) ? p->ilink : p->jlink;
    }
    if (!p)
        return -1; // y����x���ڽӵ�

    // ��ȡx����һ����
    p = (p->ivex == xIndex) ? p->ilink : p->jlink;
    // if (!p)
    //     return -1; // û����һ���ڽӵ�

    // ���ر��ϵ���һ������
    return (p->ivex == xIndex) ? p->jvex : p->ivex;
}

// Get_edge_value(G,x,y): ��ȡͼG�б�(x,y)��Ӧ��Ȩֵ
EdgeType Get_edge_value_AML(const AMLGraph &G, VertexType x, VertexType y) {
    int xIndex = LocateVex_AML(G, x);
    int yIndex = LocateVex_AML(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return INFINITY; // ���㲻����
    }

    EdgeNode *p = G.adjmulist[xIndex].firstedge;

    while (p != nullptr) {
        if ((p->ivex == xIndex && p->jvex == yIndex) || (p->ivex == yIndex && p->jvex == xIndex)) {
            return p->weight; // ���رߵ�Ȩֵ
        }

        p = (p->ivex == xIndex) ? p->ilink : p->jlink;
    }

    return INFINITY; // �߲�����
}

// Set_edge_value(G,x,y,v): ����ͼG�б�(x,y)��Ӧ��ȨֵΪv
bool Set_edge_value_AML(AMLGraph &G, VertexType x, VertexType y, EdgeType v) {
    int xIndex = LocateVex_AML(G, x);
    int yIndex = LocateVex_AML(G, y);

    if (xIndex == -1 || yIndex == -1) {
        return false; // ���㲻����
    }

    EdgeNode *p = G.adjmulist[xIndex].firstedge;

    while (p != nullptr) {
        if ((p->ivex == xIndex && p->jvex == yIndex) || (p->ivex == yIndex && p->jvex == xIndex)) {
            if (v == INFINITY) {
                // ���ڱߵ���Ҫɾ��
                return RemoveEdge_AML(G, x, y);
            }

            // ���ڱ�����Ҫ����Ȩֵ
            p->weight = v;
            return true;
        }

        p = (p->ivex == xIndex) ? p->ilink : p->jlink;
    }

    if (v == INFINITY) {
        return true; // �߱����Ͳ�������ȨֵΪINFINITY���������
    }

    // �߲���������Ҫ��ӱ�
    return AddEdge_AML(G, x, y, v);
}

// ͨ�ô�ӡ����ģ��
void PrintGraph(const MGraph &G) {
    cout << "���㣺";
    for (int i = 0; i < G.vexnum; ++i)
        cout << G.vex[i] << " ";
    cout << endl << "�ڽӾ���" << endl;
    for (int i = 0; i < G.vexnum; ++i) {
        for (int j = 0; j < G.vexnum; ++j) {
            if (G.edge[i][j] == INFINITY)
                cout << "�� ";
            else
                cout << G.edge[i][j] << " ";
        }
        cout << endl;
    }
}

void PrintGraph(const ALGraph &G) {
    cout << "�ڽӱ�" << endl;
    for (int i = 0; i < G.vexnum; ++i) {
        cout << G.vertices[i].data << ": ";
        ArcNode *p = G.vertices[i].firstarc;
        while (p) {
            cout << G.vertices[p->adjvex].data << "(" << p->weight << ") ";
            p = p->nextarc;
        }
        cout << endl;
    }
}

void PrintGraph(const OLGraph &G) {
    cout << "ʮ������" << endl;
    for (int i = 0; i < G.vexnum; ++i) {
        cout << G.xlist[i].data << "�ĳ���: ";
        ArcBox *p = G.xlist[i].firstout;
        while (p) {
            cout << G.xlist[p->headvex].data << "(" << p->weight << ") ";
            p = p->tlink;
        }
        cout << endl;
    }
}

void PrintGraph(const AMLGraph &G) {
    cout << "�ڽӶ��ر�" << endl;
    for (int i = 0; i < G.vexnum; ++i) {
        cout << G.adjmulist[i].data << ": ";
        EdgeNode *p = G.adjmulist[i].firstedge;
        while (p) {
            int other = (p->ivex == i) ? p->jvex : p->ivex;
            cout << G.adjmulist[other].data << "(" << p->weight << ") ";
            p = (p->ivex == i) ? p->ilink : p->jlink;
        }
        cout << endl;
    }
}


int main() {
    // �ڽӾ���
    MGraph mg;
    InitMGraph(mg);
    InsertVertex_M(mg, 'A');
    InsertVertex_M(mg, 'B');
    InsertVertex_M(mg, 'C');
    InsertVertex_M(mg, 'D');
    InsertVertex_M(mg, 'E');
    AddEdge_M(mg, 'A', 'B', 2);
    AddEdge_M(mg, 'A', 'C', 3);
    AddEdge_M(mg, 'B', 'D', 4);
    AddEdge_M(mg, 'C', 'D', 5);
    AddEdge_M(mg, 'D', 'E', 6);
    PrintGraph(mg);

    cout << "�ڽӾ���A���ھ�: ";
    for (auto v: Neighbors_M(mg, 'A'))
        cout << v << " ";
    cout << endl;
    int idx = FirstNeighbor_M(mg, 'A');
    if (idx != -1)
        cout << "A�ĵ�һ���ڽӵ�: " << mg.vex[idx] << endl;
    idx = NextNeighbor_M(mg, 'A', mg.vex[idx]);
    if (idx != -1)
        cout << "A����һ���ڽӵ�: " << mg.vex[idx] << endl;
    RemoveEdge_M(mg, 'A', 'B');
    DeleteVertex_M(mg, 'E');
    PrintGraph(mg);

    // �ڽӱ�
    ALGraph alg;
    InitALGraph(alg);
    InsertVertex_AL(alg, 'A');
    InsertVertex_AL(alg, 'B');
    InsertVertex_AL(alg, 'C');
    InsertVertex_AL(alg, 'D');
    InsertVertex_AL(alg, 'E');
    AddEdge_AL(alg, 'A', 'B', 2);
    AddEdge_AL(alg, 'A', 'C', 3);
    AddEdge_AL(alg, 'B', 'D', 4);
    AddEdge_AL(alg, 'C', 'D', 5);
    AddEdge_AL(alg, 'D', 'E', 6);
    PrintGraph(alg);

    cout << "�ڽӱ�A���ھ�: ";
    for (auto v: Neighbors_AL(alg, 'A'))
        cout << v << " ";
    cout << endl;
    idx = FirstNeighbor_AL(alg, 'A');
    if (idx != -1)
        cout << "A�ĵ�һ���ڽӵ�: " << alg.vertices[idx].data << endl;
    idx = NextNeighbor_AL(alg, 'A', alg.vertices[idx].data);
    if (idx != -1)
        cout << "A����һ���ڽӵ�: " << alg.vertices[idx].data << endl;
    RemoveEdge_AL(alg, 'A', 'B');
    DeleteVertex_AL(alg, 'E');
    PrintGraph(alg);

    // ʮ������
    OLGraph olg;
    InitOLGraph(olg);
    InsertVertex_OL(olg, 'A');
    InsertVertex_OL(olg, 'B');
    InsertVertex_OL(olg, 'C');
    InsertVertex_OL(olg, 'D');
    InsertVertex_OL(olg, 'E');
    AddEdge_OL(olg, 'A', 'B', 2);
    AddEdge_OL(olg, 'A', 'C', 3);
    AddEdge_OL(olg, 'B', 'D', 4);
    AddEdge_OL(olg, 'C', 'D', 5);
    AddEdge_OL(olg, 'D', 'E', 6);
    PrintGraph(olg);

    cout << "ʮ������A���ھ�: ";
    for (auto v: Neighbors_OL(olg, 'A'))
        cout << v << " ";
    cout << endl;
    idx = FirstNeighbor_OL(olg, 'A');
    if (idx != -1)
        cout << "A�ĵ�һ���ڽӵ�: " << olg.xlist[idx].data << endl;
    idx = NextNeighbor_OL(olg, 'A', olg.xlist[idx].data);
    if (idx != -1)
        cout << "A����һ���ڽӵ�: " << olg.xlist[idx].data << endl;
    RemoveEdge_OL(olg, 'A', 'B');
    DeleteVertex_OL(olg, 'E');
    PrintGraph(olg);

    // �ڽӶ��ر�
    AMLGraph amlg;
    InitAMLGraph(amlg);
    InsertVertex_AML(amlg, 'A');
    InsertVertex_AML(amlg, 'B');
    InsertVertex_AML(amlg, 'C');
    InsertVertex_AML(amlg, 'D');
    InsertVertex_AML(amlg, 'E');
    AddEdge_AML(amlg, 'A', 'B', 2);
    AddEdge_AML(amlg, 'A', 'C', 3);
    AddEdge_AML(amlg, 'B', 'D', 4);
    AddEdge_AML(amlg, 'C', 'D', 5);
    AddEdge_AML(amlg, 'D', 'E', 6);
    PrintGraph(amlg);

    cout << "�ڽӶ��ر�A���ھ�: ";
    for (auto v: Neighbors_AML(amlg, 'A'))
        cout << v << " ";
    cout << endl;
    idx = FirstNeighbor_AML(amlg, 'A');
    if (idx != -1)
        cout << "A�ĵ�һ���ڽӵ�: " << amlg.adjmulist[idx].data << endl;
    idx = NextNeighbor_AML(amlg, 'A', amlg.adjmulist[idx].data);
    if (idx != -1)
        cout << "A����һ���ڽӵ�: " << amlg.adjmulist[idx].data << endl;
    RemoveEdge_AML(amlg, 'A', 'B');
    DeleteVertex_AML(amlg, 'E');
    PrintGraph(amlg);

    return 0;
}
