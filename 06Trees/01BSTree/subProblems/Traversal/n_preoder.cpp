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