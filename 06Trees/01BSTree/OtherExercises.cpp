#include<iostream>
#include<vector>
#include<queue>
using namespace std;

// 恢复一颗二叉搜索树(数组版本)
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
class Recover {
public:
    void inOrder(TreeNode* node, vector<TreeNode*>& arr) {
        if (node == nullptr) {
            return;
        }
        inOrder(node->left, arr);
        arr.push_back(node);
        inOrder(node->right, arr);
    }
    void recoverTree(TreeNode* root) {
        if (root == nullptr) {
            return;
        }
        vector<TreeNode*> arr;
        inOrder(root, arr);
        TreeNode* node1 = nullptr;
        TreeNode* node2 = nullptr;
        const int n = arr.size();
        if (n < 2) {
            return;
        }
        for (int i = 0; i < n; i++) {
            if (i + 1 < n && node1 == nullptr &&
                arr[i]->val > arr[i + 1]->val) {
                node1 = arr[i];
            }
            if (i != 0 && node1 != nullptr && arr[i]->val < arr[i - 1]->val) {
                node2 = arr[i];
            }
        }
        if (node1 == nullptr || node2 == nullptr) {
            return;
        }
        swap(node1->val, node2->val);
        return;
    }
};
// 双指针找错误节点
class Recover2 {
public:
    TreeNode* node1;
    TreeNode* node2;
    bool flag;
    void DFS(TreeNode* node, TreeNode*& prev) {
        if (node == nullptr) {
            return;
        }
        DFS(node->left, prev);
        if (prev != nullptr) {
            int preval = prev->val;
            int curval = node->val;
            if (flag && preval > curval) {
                node1 = prev;
                flag = false;
            }
            if (!flag && preval > curval) {
                node2 = node;
            }
        }
        prev = node;
        DFS(node->right, prev);
    }
    void recoverTree(TreeNode* root) {
        if (root == nullptr) {
            return;
        }
        TreeNode* prev = nullptr;
        TreeNode* node = root;
        node1 = nullptr;
        node2 = nullptr;
        flag = true;
        DFS(node, prev);
        if (node1 == nullptr || node2 == nullptr) {
            return;
        }
        swap(node1->val, node2->val);
        return;
    }
};

// 利用有序单链表构造平衡二叉树
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};
class SortedListToBST {
public:
    TreeNode* BinarySearch(const vector<int>& v, int start, int end) {
        if (start > end) {
            return nullptr;
        }
        int mid = start + (end - start) / 2;
        int curVal = v[mid];
        TreeNode* node = new TreeNode(curVal);
        TreeNode* left = BinarySearch(v, start, mid - 1);
        TreeNode* right = BinarySearch(v, mid + 1, end);
        node->left = left;
        node->right = right;
        return node;
    }
    TreeNode* sortedListToBST(ListNode* head) {
        // 给了我head头指针，直接利用二分法构造一颗二叉树即可
        // 二分查找思想
        vector<int>v;
        ListNode* node = head;
        while (node != nullptr) {
            v.push_back(node->val);
            node = node->next;
        }
        const int n = v.size();
        return BinarySearch(v, 0, n - 1);
    }
};


//给你二叉树的根结点 root ，请你将它展开为一个单链表：
//展开后的单链表应该同样使用 TreeNode ，其中 right 子指针指向链表中下一个结点，而左子指针始终为 null 。
//展开后的单链表应该与二叉树 先序遍历 顺序相同。
class BSTtoList {
public:
    // V L R
    void preOrder(vector<TreeNode* >& v, TreeNode* node) {
        if (node == nullptr) {
            return;
        }
        v.push_back(node);
        preOrder(v, node->left);
        preOrder(v, node->right);
    }
    void flatten(TreeNode* root) {
        if (root == nullptr) { return; }
        vector<TreeNode* >v;
        preOrder(v, root);
        for (int i = 0; i < v.size() - 1; i++) {
            v[i]->left = nullptr;
            v[i]->right = v[i + 1];
        }
    }
};

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;
    Node() : val(0), left(NULL), right(NULL), next(NULL) {}
    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}
    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {
    }
};
// 满二叉树next指针填充
/*
* 小心两个坑
* 一个没插孩子进队，一个没注意孩子已经进去了
*/
class ConnectSolution {
public:
    Node* connect(Node* root) {
        if (root == nullptr) { return root; }
        queue<Node*>q;
        q.push(root);
        while (!q.empty()) {
            int n = q.size();
            for (int i = 0; i < n; i++) {
                auto front = q.front();
                q.pop();
                if (front->left) { q.push(front->left); }
                if (front->right) { q.push(front->right); }
                //if (q.empty()) { break; }  这是错的，下一层的东西已经进队列了！！很坏啊，一定要小心！
                if (i == n - 1) { break; }
                auto next = q.front();
                front->next = next;
            }
        }
        return root;
    }
};
// O1方法
class O1Connect {
public:
    Node* connect(Node* root) {
        if (root == nullptr) { return root; }
        Node* parent = root;
        while (parent != nullptr) {
            bool flag = true;
            Node* nextParent = parent->left;
            Node* cur = parent->left;
            Node* next = parent->right;
            while (next != nullptr) {
                if (flag) {
                    cur->next = next;
                    cur = next;
                    parent = parent->next;
                    if (parent == nullptr) { break; }
                    next = parent->left;
                    flag = false;
                }
                else {
                    cur->next = next;
                    cur = next;
                    next = parent->right;
                    flag = true;
                }
            }
            parent = nextParent;
        }
        return root;
    }
};
// 明天建议学习带dummy的写法，逻辑会简单一些。