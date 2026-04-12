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