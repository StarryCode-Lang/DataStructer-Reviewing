#include <iostream>
#include <memory>
#include <queue>
#include <vector>
using namespace std;

// 树节点
struct TreeNode {
    int val;
    shared_ptr<TreeNode> left, right;

    explicit TreeNode(int v) : val(v) {
    }
};

// 从层序数组构建树
shared_ptr<TreeNode> BuildTreeFromLevelOrder(const vector<int> &data) {
    if (data.empty() || data[0] == NULL) return nullptr;

    auto root = make_shared<TreeNode>(data[0]);
    queue<shared_ptr<TreeNode> > q;
    q.push(root);
    size_t i = 1;

    while (i < data.size()) {
        auto node = q.front();
        q.pop();

        if (i < data.size() && data[i] != NULL) {
            node->left = make_shared<TreeNode>(data[i]);
            q.push(node->left);
        }
        ++i;

        if (i < data.size() && data[i] != NULL) {
            node->right = make_shared<TreeNode>(data[i]);
            q.push(node->right);
        }
        ++i;
    }
    return root;
}

// 返回分层遍历结果
vector<vector<int> > LevelOrderByLevel(const shared_ptr<TreeNode> &root) {
    vector<vector<int> > res;
    if (!root) return res;

    queue<shared_ptr<TreeNode> > q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();
        vector<int> level;

        for (int i = 0; i < levelSize; ++i) {
            auto node = q.front();
            q.pop();
            level.push_back(node->val);
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }

        res.push_back(level);
    }
    return res;
}

// 打印二维数组结果
void PrintLevels(const vector<vector<int> > &levels) {
    cout << "[";
    for (size_t i = 0; i < levels.size(); ++i) {
        cout << "[";
        for (size_t j = 0; j < levels[i].size(); ++j) {
            cout << levels[i][j];
            if (j + 1 < levels[i].size()) cout << ",";
        }
        cout << "]";
        if (i + 1 < levels.size()) cout << ",";
    }
    cout << "]\n";
}

int main() {
    // LeetCode 样式的输入
    vector<int> data = {3, 9, 20, NULL, NULL, 15, 7};
    auto root = BuildTreeFromLevelOrder(data);
    auto levels = LevelOrderByLevel(root);
    PrintLevels(levels);
    return 0;
}
