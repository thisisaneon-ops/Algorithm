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