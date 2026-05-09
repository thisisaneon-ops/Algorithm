#include<iostream>
#include<vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) :
        val(x),
        left(left),
        right(right)
    {
    }
};

class Solution {
public:
    void recoverTree(TreeNode* root) {
        if (root == nullptr ||
            (root->left == nullptr && root->right == nullptr)) {
            return;
        }
        vector<TreeNode* > v;
        DFS(v, root);
        TreeNode* node1 = nullptr;
        TreeNode* node2 = nullptr;
        for (int i = 0; i < v.size(); i++) {
            if (i != 0 && node1 == nullptr && v[i]->val < v[i - 1]->val) {
                node1 = v[i - 1];
            }
            if (i != 0 && node1 != nullptr && v[i]->val < v[i - 1]->val) {
                node2 = v[i];
            }
        }
        if (node1 == nullptr || node2 == nullptr) {
            throw std::invalid_argument("invalid input");
        }
        swap(node1->val, node2->val);
        return;
    }
    // LVR
    void DFS(vector<TreeNode* >& v, TreeNode* node) {
        if (node == nullptr) {
            return;
        }
        DFS(v, node->left);
        v.push_back(node);
        DFS(v, node->right);
    }
};