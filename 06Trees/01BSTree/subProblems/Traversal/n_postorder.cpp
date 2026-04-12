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