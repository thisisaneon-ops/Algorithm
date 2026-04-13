// 429 思想和二叉树完全一致，只是把左右节点换成了顺序遍历数组vector


/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        vector<vector<int>>v;
        if(root == nullptr){
            return v;
        }
        queue<Node*>q;
        q.push(root);
        while(!q.empty()){
            int cur_size = q.size();
            vector<int>level;
            for(int k = 0 ; k < cur_size; k++){
                Node* front = q.front();
                q.pop();
                level.push_back(front->val);
                for(auto u : front->children){
                    q.push(u);
                }
            }
            v.push_back(level);
        }
        return v;
    }
};