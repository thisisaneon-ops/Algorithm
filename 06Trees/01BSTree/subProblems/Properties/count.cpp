int CountNode(TreeNode* head)
{
    if(head == nullptr)
    {
        return 0;
    }
    int left = CountNode(head->left);
    int right = CountNode(head->right);
    return left + right + 1;
}