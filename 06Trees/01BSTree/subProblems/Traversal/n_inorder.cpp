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