#include<iostream>
#include<stack>
#include<functional>
using namespace std;

class BSTree
{
    using Comp = function<bool(int, int)>;
public:
    BSTree()
        : root(nullptr)
        , comp([](int a, int b)->bool{return a < b;})
    {}
    ~BSTree()
    {
        destroy(root);
        root = nullptr;
    }
// 迭代接口
public:
    void n_insert(int val)
    {
        TreeNode* parent = nullptr;
        TreeNode* cur = root;
        if(cur == nullptr)
        {
            root = new TreeNode(val);
        }
        while(cur != nullptr)
        {
            if(comp(cur->val, val))
            {
                parent = cur;
                cur = cur->right;
            }
            else if(comp(val, cur->val))
            {
                parent = cur;
                cur = cur->left;
            }
            else
            {
                return;
            }
        }
        if(comp(parent->val, val))
        {
            parent->right = new TreeNode(val);
        }
        else
        {
            parent->left = new TreeNode(val);
        }
    }
    void n_erase(int val)
    {
        TreeNode* parent = nullptr;
        TreeNode* cur = root;
        if(cur == nullptr)
        {
            return;
        }
        while(cur != nullptr)
        {
            if(comp(cur->val, val))
            {
                parent = cur;
                cur = cur->right;
            }
            else if(comp(val, cur->val))
            {
                parent = cur;
                cur = cur->left;
            }
            else
            {
                break;
            }
        }
        if(cur == nullptr)
        {
            return;
        }
        if(cur->left && cur->right)
        {
            parent = cur;
            TreeNode* pre = cur->left;
            while(pre->right != nullptr)
            {
                parent = pre;
                pre = pre->right;
            }
            cur->val = pre->val;
            cur = pre;
        }
        TreeNode* child = cur->left;
        if(cur->right != nullptr)
        {
            child = cur->right;
        }
        if(parent == nullptr)
        {
            delete root;
            root = child;
            return;
        }
        if(parent->left == cur)
        {
            parent->left = child;
            delete cur;
        }
        else
        {
            parent->right = child;
            delete cur;
        }
    }
    bool n_query(int val)
    {
        TreeNode* cur = root;
        while(cur != nullptr)
        {
            if(comp(cur->val, val))
            {
                cur = cur->right;
            }
            else if(comp(val, cur->val))
            {
                cur = cur->left;
            }
            else
            {
                return true;
            }
        }
        return false;
    }
    void n_preOrder()
    {
        if(root == nullptr)
        {
            return;
        }
        TreeNode* node = root;
        stack<TreeNode* >s;
        s.push(node);
        while(!s.empty())
        {
            TreeNode* top = s.top();
            s.pop();
            cout << top->val << " ";
            if(top->right != nullptr)
            {
                s.push(top->right);
            }
            if(top->left != nullptr)
            {
                s.push(top->left);
            }
        }
    }
    void n_inOrder()
    {
        if(root == nullptr)
        {
            return;
        }
        TreeNode* node = root;
        stack<TreeNode*>s;
        while(node != nullptr)
        {
            s.push(node);
            node = node->left;
        }
        while(!s.empty())
        {
            TreeNode* top = s.top();
            s.pop();
            cout << top->val << " ";
            if(top->right != nullptr)
            {
                TreeNode* pre = top->right;
                while(pre != nullptr)
                {
                    s.push(pre);
                    pre = pre->left;
                }
            }
        }
    }
    void n_postOrder()
    {
        if(root == nullptr)
        {
            return;
        }
        TreeNode* node = root;
        stack<TreeNode*>ops;
        stack<TreeNode*>prs;
        ops.push(node);
        while(!ops.empty())
        {
            TreeNode* top = ops.top();
            ops.pop();
            prs.push(top);
            if(top->left != nullptr)
            {
                ops.push(top->left);
            }
            if(top->right != nullptr)
            {
                ops.push(top->right);
            }
        }
        while(!prs.empty())
        {
            TreeNode* top = prs.top();
            prs.pop();
            cout << top->val << " ";
        }
    }
// 递归主接口
public:
    void destroy(TreeNode* node)  // 必须后序，否则后面的节点找不到
    {
        if(node == nullptr)
        {
            return;
        }
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
    void insert(int val)
    {
        root = insert(root, val);
    }
    void erase(int val)
    {
        root = erase(root, val);
    }
    bool query(int val)
    {
        return query(root, val);
    }
    void preOrder()
    {
        preOrder(root);
    }
    void inOrder()
    {
        inOrder(root);
    }
    void postOrder()
    {
        postOrder(root);
    }
    int height()
    {
        return height(root);
    }
    int count()
    {
        return count(root);
    }
// 常见习题接口
public:
    // 获取区间子节点  [i, j] 内的所有元素
    vector<int> findsec(vector<int>&vecs, int i, int j)
    {
        if(i > j)
        {
            return;
        }
        findsec(vecs, i, j, root);
        return vecs;
    }
    // 获取区间子节点  （i, j） 内的所有元素
    vector<int> findsec2(vector<int>&vecs, int i, int j)
    {
        if(i > j)
        {
            return;
        }
        findsec2(vecs, i, j, root);
        return vecs;
    }
    // 判断一颗树是否为BST树  -- 中序递增
    bool isBST()
    {
        TreeNode* pre = nullptr;
        return isBST(root, pre);
    }
    // 判断子树
    bool isChild(TreeNode* father, TreeNode* child)
    {
        TreeNode* f = father;
        while(f != nullptr)
        {
            if(comp(f->val, child->val))
            {
                f = f->right;
            }
            else if(comp(child->val, f->val))
            {
                f = f->left;
            }
            else
            {
                break;
            }
        }
        if(f == nullptr)
        {
            return false;
        }
        return isSame(f, child);
    }
    // LCA
    TreeNode* LCA(TreeNode* p, TreeNode* q)
    {
        if(p->val > q->val)
        {
            return LCA(q, p);
        }
        return LCA(root, p->val, q->val);
    }
    // reverse镜像翻转
    void reverse()
    {
        reverse(root);
    }
    // symmetric判断对称
    bool isSymmetric()
    {
        if(root == nullptr)
        {
            return true;
        }
        return isSym(root->left, root->right);
    }
    // 利用preOrder和inOrder重建二叉树
    TreeNode* rebuild(vector<int>& pre, vector<int>& in)
    {
        return rebuild(pre, i, j, in, p, q);
    }
    // isBalance
    bool isBalance()
    {
        return isBalance(root);
    }
    // 找导数第K个点
    TreeNode* FindLastK(int k)
    {
        int i = 0;
        return FindKth(root, i, k);
    }
// 递归辅助接口
private:
    TreeNode* insert(TreeNode* node, int val)
    {
        if(node == nullptr)
        {
            return new TreeNode(val);
        }
        if(comp(node->val, val))
        {
            node->right = insert(node->right, val);
            return node;
        }
        else if(comp(val, node->val))
        {
            node->left = insert(node->left, val);
            return node;
        }
        else
        {
            return node;
        }
    }
    TreeNode* erase(TreeNode* node, int val)
    {
        if(node == nullptr)
        {
            return nullptr;
        }
        if(comp(node->val, val))
        {
            node->right = erase(node->right, val);
            return node;
        }
        else if(comp(val, node->val))
        {
            node->left = erase(node->left, val);
            return node;
        }
        else
        {
            if(node->left && node->right)
            {
                TreeNode* pre = node->left;
                while(pre->right != nullptr)
                {
                    pre = pre->right;
                }
                node->val = pre->val;
                node->left = erase(node->left, pre->val);
                return node;
            }
            if(node->left != nullptr)
            {
                TreeNode* child = node->left;
                delete node;
                return child;
            }
            else
            {
                TreeNode* child = node->right;
                delete node;
                return child;
            }
        }
    }
    bool query(TreeNode* node, int val)
    {
        if(node == nullptr)
        {
            return false;
        }
        if(comp(node->val, val))
        {
            return query(node->left, val);
        }
        else if(comp(node->right, val))
        {
            return query(node->right, val);
        }
        else
        {
            return true;
        }
    }
    void preOrder(TreeNode* node)
    {
        if(node == nullptr)
        {
            return;
        }
        cout << node->val << " ";
        preOrder(node->left);
        preOrder(node->right);  
    }
    void inOrder(TreeNode* node)
    {
        if(node == nullptr)
        {
            return;
        }
        inOrder(node->left);
        cout << node->val << " ";
        inOrder(node->right);
    }
    void postOrder(TreeNode* node)
    {
        if(node == nullptr)
        {
            return;
        }
        postOrder(node->left);
        postOrder(node->right);
        cout << node->val << " ";
    }
    int height(TreeNode* node)
    {
        if(node == nullptr)
        {
            return 0;
        }
        int left_height = height(node->left);
        int right_height = height(node->right);
        return max(left_height, right_height) + 1;
    }
    int count(TreeNode* node)
    {
        if(node == nullptr)
        {
            return 0;
        }
        int leftTotal = count(node->left);
        int rightTotal = count(node->right);
        return leftTotal + rightTotal + 1;
    }
// 练习递归接口
private:
    // [i, j]
    void findsec(vector<int>&vecs, int i, int j, TreeNode* node)
    {
        if(node == nullptr)
        {
            return;
        }
        if(!comp(node->val, j))
        {
            findsec(vecs, i, j, node->left);
        }
        if(!comp(node->val, i) && !comp(j, node->val))
        {
            vecs.push_back(node->val);
        }
        if(!comp(i, node->val))
        {
            findsec(vecs, i, j, node->right);
        }
    }
    // （i, j）
    void findsec2(vector<int>&vecs, int i, int j, TreeNode* node)
    {
        if(node == nullptr)
        {
            return;
        }
        if(!comp(node->val, j))
        {
            findsec(vecs, i, j, node->left);
        }
        if(comp(i, node->val) && comp(node->val, j))
        {
            vecs.push_back(node->val);
        }
        if(!comp(i, node->val))
        {
            findsec(vecs, i, j, node->right);
        }
    }
    // isBST 无剪枝
    bool isBST(TreeNode* node, TreeNode*& pre)
    {
        if(node == nullptr)
        {
            return true;
        }
        bool A = isBST(node->left, pre);
        if(pre != nullptr && !comp(pre->val, node->val))
        {
            return false;
        }
        pre = node;
        bool B = isBST(node->right, pre);
        return A && B;
    }
    // isBST  有剪枝的写法
    bool isBST(TreeNode* node, TreeNode*& pre)
    {
        if(node == nullptr)
        {
            return true;
        }
        if(!isBST(node->left, pre))
        {
            return false;
        }
        if(pre != nullptr && !comp(pre->val, node->val))
        {
            return false;
        }
        pre = node;
        return isBST(node->right, pre);
    }
    // isChildTree-Helper
    bool isSame(TreeNode* father, TreeNode* child)
    {
        if(father == nullptr && child == nullptr)
        {
            return true;
        }
        if(father == nullptr)
        {
            return false;
        }
        if(child == nullptr)
        {
            return true;
        }
        if(!isSame(father->left, child->left))
        {
            return false;
        }
        if(comp(father->val, child->val) || comp(child->val, father->val))
        {
            return false;
        }
        return isSame(father->right, child->right);
    }
    TreeNode* LCA(TreeNode* node, int lower, int upper)
    {
        if(node == nullptr)
        {
            return nullptr;
        }
        if(comp(lower, node->val) && comp(node->val, upper))
        {
            return node;
        }
        if(!comp(lower, node->val))
        {
            return LCA(node->right, lower, upper);
        }
        if(!comp(node->val, upper))
        {
            return LCA(node->left, lower, upper);
        }
    }
    // reverse
    void reverse(TreeNode* node)
    {
        if(node == nullptr)
        {
            return;
        }
        swap(node->left, node->right);
        reverse(node->left);
        reverse(node->right);
    }
    // isSym
    bool isSym(TreeNode* left, TreeNode* right)
    {
        if(left == nullptr && right == nullptr)
        {
            return true;
        }   
        if(left == nullptr)
        {
            return false;
        }
        if(right == nullptr)
        {
            return false;
        }
        if(comp(left->val, right->val) || comp(right->val, left->val))
        {
            return false;
        }
        return isSym(left->right, right->left) && isSym(left->left, right->right);
    }
    // isSym  有剪枝的写法
    bool isSym(TreeNode* left, TreeNode* right)
    {
        if(left == nullptr && right == nullptr)
        {
            return true;
        }   
        if(left == nullptr)
        {
            return false;
        }
        if(right == nullptr)
        {
            return false;
        }
        if(!isSym(left->left, right->right))
        {
            return false;
        }
        if(comp(left->val, right->val) || comp(right->val, left->val))
        {
            return false;
        }
        return isSym(left->right, right->left);
    }
    // rebuild
    TreeNode* rebuild(vector<int>& pre, int i ,int j, vector<int>& in, int p, int q)
    {
        if(i > j || p > q)
        {
            return nullptr; 
        }
        TreeNode* root = new TreeNode(pre[i]);
        int pos = p;
        for(; pos <= q; pos++)
        {
            if(pre[i] == in[pos])
            {
                break;
            }
        }
        root->left = rebuild(pre, i + 1, i + pos - p, in, p, pos - 1);
        root->right = rebuild(pre, i + pos - p + 1, j, in, pos + 1, q);
        return root;
    }
    // isBalance
    bool isBalance(TreeNode* node)
    {
        if(node == nullptr)
        {
            return true;
        }
        if(!isBalance(node->left))
        {
            return false;
        }
        int left = height(node->left);
        int right = height(node->right);
        if(abs(left - right) > 1)
        {
            return false;
        }
        return isBalance(node->right);
    }
    int isBalance(TreeNode* node, bool& flag)
    {
        if(node == nullptr)
        {
            return 0;
        }
        int left = isBalance(node->left, flag);
        int right = isBalance(node->right, flag);
        if(abs(left - right) > 1)
        {
            flag = false;
        }
        return max(left, right) + 1;
    }
    // FindKth TreeNode
    TreeNode* FindKth(TreeNode* node, int& i, int k)
    {
        if(node == nullptr)
        {
            return nullptr;
        }
        TreeNode* right = FindKth(node->right, i, k);  // 体会递归回溯的思想，相当于派通讯兵去右子树探测情况
        if(right != nullptr)  // 有结果直接返回
        {
            return right;
        }
        i++;
        if(i == k)
        {
            return node;
        }
        return FindKth(node->left, i, k);
    }

private:
    struct TreeNode
    {
        TreeNode()
            : val(0)
            , left(nullptr)
            , right(nullptr)
        { }
        int val;
        TreeNode* left;
        TreeNode* right;
    };
    TreeNode* root;
    Comp comp;
};

int main()
{
    return 0;
}
