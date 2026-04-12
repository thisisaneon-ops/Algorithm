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