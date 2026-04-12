int height(TreeNode* head)
{
    if(head == nullptr)
    {
        return 0;
    }
    int left = height(head->left);
    int right = height(head->right);
    return max(left, right) + 1;
}