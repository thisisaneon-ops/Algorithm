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