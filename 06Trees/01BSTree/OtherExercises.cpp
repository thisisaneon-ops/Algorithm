#include<iostream>
#include<vector>
#include<stack>
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

/*


                                ？？？


*/



class Connect2 {
public:
    Node* connect(Node* root) {
        if (root == nullptr) { return root; }
        queue<Node* >q;
        q.push(root);
        while (!q.empty()) {
            const int n = q.size();
            for (int i = 0; i < n; i++) {
                auto front = q.front();
                q.pop();
                if (front->left) { q.push(front->left); }
                if (front->right) { q.push(front->right); }
                if (i == n - 1) { break; }
                auto next = q.front();
                front->next = next;
            }
        }
        return root;
    }
};

/*
* 路径数字之和
给你一个二叉树的根节点 root ，树中每个节点都存放有一个 0 到 9 之间的数字。
每条从根节点到叶节点的路径都代表一个数字：

例如，从根节点到叶节点的路径 1 -> 2 -> 3 表示数字 123 。
计算从根节点到叶节点生成的 所有数字之和 。

叶节点 是指没有子节点的节点。
*/
class SumNumbers {
public:
    void DFS(TreeNode* node, int& sum, int num) {
        if (node == nullptr) {
            return;
        }
        if (node->left == nullptr && node->right == nullptr) {
            sum += num * 10 + node->val;
            return;
        }
        DFS(node->left, sum, num * 10 + node->val);
        DFS(node->right, sum, num * 10 + node->val);
    }
    int sumNumbers(TreeNode* root) {
        int sum = 0;
        int num = 0;
        DFS(root, sum, num);
        return sum;
    }
};


/*
实现一个二叉搜索树迭代器类BSTIterator ，表示一个按中序遍历二叉搜索树（BST）的迭代器：
BSTIterator(TreeNode root) 初始化 BSTIterator 类的一个对象。BST 的根节点 root 会作为构造函数的一部分给出。指针应初始化为一个不存在于 BST 中的数字，且该数字小于 BST 中的任何元素。
boolean hasNext() 如果向指针右侧遍历存在数字，则返回 true ；否则返回 false 。
int next()将指针向右移动，然后返回指针处的数字。
注意，指针初始化为一个不存在于 BST 中的数字，所以对 next() 的首次调用将返回 BST 中的最小元素。
你可以假设 next() 调用总是有效的，也就是说，当调用 next() 时，BST 的中序遍历中至少存在一个下一个数字。
*/
class BSTIterator {
private:
    // L V R
    void DFS(vector<int>& nums, TreeNode* node) {
        if (node == nullptr) {
            return;
        }
        DFS(nums, node->left);
        nums.push_back(node->val);
        DFS(nums, node->right);
    }
    vector<int>nums;
    int idx = 0;
public:
    BSTIterator(TreeNode* root) {
        DFS(nums, root);
    }
    int next() {
        return nums[idx++];
    }
    bool hasNext() {
        int n = nums.size();
        return idx < n;
    }
};
// 写另一种方法之前，我们先回顾一下迭代的写法
// VLR
void preOrder(TreeNode* root) {
    if (root == nullptr) { return; }
    stack<TreeNode* >s;
    s.push(root);
    while (!s.empty()) {
        auto top = s.top();
        cout << top->val << endl;
        s.pop();
        if (top->right) {
            s.push(top->right);
        }
        if (top->left) {
            s.push(top->left);
        }
    }
}
// LVR
void inOrder(TreeNode* root) {
    if (root == nullptr) { return; }
    stack<TreeNode* > s;
    TreeNode* node = root;
    while (node != nullptr){
        s.push(node);
        node = node->left;
    }
    while (!s.empty()) {
        auto top = s.top();
        s.pop();
        cout << top->val << endl;
        if (top->right != nullptr) {
            auto right = top->right;
            while(right != nullptr){
                s.push(right);
                right = right->left;
            }
        }
    }
}
// 好的我们开始重写这个题：
class BSTIterator {
private:
    stack<TreeNode*>s;
public:
    BSTIterator(TreeNode* root) {
        TreeNode* node = root;
        while (node != nullptr){
            s.push(node);
            node = node->left;
        }
    }
    int next() {
        auto top = s.top();
        s.pop();
        if (top->right) {
            TreeNode* right = top->right;
            while (right) {
                s.push(right);
                right = right->left;
            }
        }
        return top->val;
    }
    bool hasNext() {
        return !s.empty();
    }
};