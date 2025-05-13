#include <iomanip>
#include <iostream>
#include <stack>
#include <vector>
#include "6-0GraphDefinition.h"

using namespace std;

// ���Ϣ�ṹ��
struct Activity {
    int from; // ���
    int to; // �յ�
    int weight; // ����ʱ��
    int ee; // ���翪ʼʱ��
    int el; // ��ٿ�ʼʱ��
    int slack; // ʱ������
};

bool TopologicalOrder(const ALGraph &G, vector<int> &ve, stack<int> &T) {
    vector<int> inDegree(G.vexnum, 0);
    // ͳ�����
    for (int i = 0; i < G.vexnum; i++) {
        for (ArcNode *p = G.vertices[i].firstarc; p; p = p->nextarc) {
            inDegree[p->adjvex]++;
        }
    }

    stack<int> S;
    // ���Ϊ0�Ķ�����ջ
    for (int i = 0; i < G.vexnum; i++) {
        if (inDegree[i] == 0) {
            S.push(i);
        }
    }

    int count = 0;
    ve.assign(G.vexnum, 0); // ��ʼ�����緢��ʱ��

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
    vector<int> ve; // �¼������緢��ʱ��
    vector<int> vl; // �¼�����ٷ���ʱ��
    vector<Activity> acts; // ���Ϣ
    stack<int> T; // ��������ջ

    // 1. �����¼������緢��ʱ��ve[]
    if (!TopologicalOrder(G, ve, T)) {
        cout << "ͼ�д��ڻ����޷�����ؼ�·����" << endl;
        return;
    }

    // 2. ��ʼ���¼�����ٷ���ʱ��vl[]
    vl.assign(G.vexnum, ve[G.vexnum - 1]);

    // 3. �������������vl[]
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

    // 4. �ռ����л��Ϣ
    for (int j = 0; j < G.vexnum; j++) {
        for (ArcNode *p = G.vertices[j].firstarc; p; p = p->nextarc) {
            Activity act{};
            act.from = j;
            act.to = p->adjvex;
            act.weight = p->weight;
            act.ee = ve[j]; // ����翪ʼʱ��
            act.el = vl[p->adjvex] - p->weight; // ���ٿ�ʼʱ��
            act.slack = act.el - act.ee; // ʱ������
            acts.push_back(act);
        }
    }

    // 5. ������
    // 5.1 ����¼����������ٷ���ʱ��
    cout << "\n�¼����������ٷ���ʱ�䣺" << endl;
    cout << setw(8) << "�¼�" << setw(8) << "Ve" << setw(8) << "Vl" << endl;
    cout << "------------------------" << endl;
    for (int i = 0; i < G.vexnum; i++) {
        cout << setw(8) << G.vertices[i].data << setw(8) << ve[i] << setw(8) << vl[i] << endl;
    }

    // 5.2 �����ĸ���ʱ�����
    cout << "\n���ʱ�������" << endl;
    cout << setw(8) << "�" << setw(8) << "����ʱ��" << setw(8) << "e(i)" << setw(8) << "l(i)" << setw(8)
         << "l(i)-e(i)" << endl;
    cout << "----------------------------------------" << endl;

    for (const auto &act: acts) {
        cout << setw(6) << G.vertices[act.from].data << "->" << setw(4) << G.vertices[act.to].data << setw(8)
             << act.weight << setw(8) << act.ee << setw(8) << act.el << setw(8) << act.slack << endl;
    }

    // 5.3 ����ؼ��
    cout << "\n�ؼ����ʱ������Ϊ0�Ļ����" << endl;
    cout << "�\t����ʱ��" << endl;
    cout << "----------------" << endl;
    for (const auto &act: acts) {
        if (act.slack == 0) {
            cout << G.vertices[act.from].data << "->" << G.vertices[act.to].data << "\t" << act.weight << endl;
        }
    }
}

// ��������
int main() {
    ALGraph G;
    G.vexnum = 6;
    G.arcnum = 8;

    // ��ʼ������
    for (int i = 0; i < G.vexnum; i++) {
        G.vertices[i].data = 'A' + i;
        G.vertices[i].firstarc = nullptr;
    }

    // ��ӱߵĸ�������
    auto addEdge = [&](int from, int to, int weight) {
        auto *p = new ArcNode;
        p->adjvex = to;
        p->weight = weight;
        p->nextarc = G.vertices[from].firstarc;
        G.vertices[from].firstarc = p;
    };

    // ���AOE����ı�
    addEdge(0, 1, 3); // A->B
    addEdge(0, 2, 4); // A->C
    addEdge(1, 3, 5); // B->D
    addEdge(2, 3, 6); // C->D
    addEdge(2, 4, 7); // C->E
    addEdge(3, 5, 2); // D->F
    addEdge(4, 5, 5); // E->F
    addEdge(1, 4, 6); // B->E

    cout << "AOE����Ĺؼ�·��������" << endl;
    CriticalPath(G);

    return 0;
}
