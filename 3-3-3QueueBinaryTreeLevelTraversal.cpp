#include <iostream>
#include <queue>
#include <memory>
using namespace std;

// 二叉树节点结构
struct TreeNode {
    int val;
    shared_ptr<TreeNode> left;
    shared_ptr<TreeNode> right;
    
    // 构造函数
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 创建一个示例二叉树
shared_ptr<TreeNode> createSampleTree() {
    auto root = make_shared<TreeNode>(1);
    root->left = make_shared<TreeNode>(2);
    root->right = make_shared<TreeNode>(3);
    root->left->left = make_shared<TreeNode>(4);
    root->left->right = make_shared<TreeNode>(5);
    root->right->left = make_shared<TreeNode>(6);
    root->right->right = make_shared<TreeNode>(7);
    return root;
}

// 使用队列进行层序遍历
void levelOrderTraversal(const shared_ptr<TreeNode>& root) {
    if (!root) {
        cout << "树为空" << endl;
        return;
    }
    
    queue<shared_ptr<TreeNode>> q;
    q.push(root);
    
    cout << "层序遍历结果: ";
    
    while (!q.empty()) {
        auto node = q.front();
        q.pop();
        
        cout << node->val << " ";
        
        if (node->left) {
            q.push(node->left);
        }
        
        if (node->right) {
            q.push(node->right);
        }
    }
    
    cout << endl;
}

// 分层输出层序遍历结果
void levelOrderTraversalByLevel(const shared_ptr<TreeNode>& root) {
    if (!root) {
        cout << "树为空" << endl;
        return;
    }
    
    queue<shared_ptr<TreeNode>> q;
    q.push(root);
    
    cout << "分层输出层序遍历结果:" << endl;
    
    int level = 0;
    while (!q.empty()) {
        int size = q.size();  // 当前层的节点数
        level++;
        
        cout << "第 " << level << " 层: ";
        
        for (int i = 0; i < size; i++) {
            auto node = q.front();
            q.pop();
            
            cout << node->val << " ";
            
            if (node->left) {
                q.push(node->left);
            }
            
            if (node->right) {
                q.push(node->right);
            }
        }
        
        cout << endl;
    }
}

int main() {
    auto tree = createSampleTree();
    
    levelOrderTraversal(tree);
    levelOrderTraversalByLevel(tree);
    
    return 0;
}
