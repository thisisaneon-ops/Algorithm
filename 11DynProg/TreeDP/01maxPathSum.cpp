/*
[124]最大路径和
二叉树中的 路径 被定义为一条节点序列，序列中每对相邻节点之间都存在一条边。
同一个节点在一条路径序列中 至多出现一次 。
该路径 至少包含一个 节点，且不一定经过根节点。
路径和 是路径中各节点值的总和。
给你一个二叉树的根节点 root ，返回其 最大路径和 。
*/
#include<iostream>
using namespace std;

struct TreeNode {
	TreeNode(int v = 0)
		: val(v)
		, left(nullptr)
		, right(nullptr)
	{}
	int val;
	TreeNode* left;
	TreeNode* right;
};

int TreePath(TreeNode* node, int &maxlen) {
	if (node == nullptr) {
		return 0;
	}
	int left = TreePath(node->left, maxlen);
	int right = TreePath(node->right, maxlen);
	int a = left + node->val;
	int b = right + node->val;
	int c = left + right + node->val;
	int d = node->val;
	maxlen = max({ maxlen, a, b, c, d });  // 更新maxlen，maxlen不关心最大值来自整体还是局部
	return max({ a,b,d });  // 只能返回整体的最大值，因为node必须参与且不能横跨node
}

int maxPath(TreeNode* root) {
	if (root == nullptr) {
		return 0;
	}
	int maxlen = root->val;  // 不能初始化为0，防止root->val<0导致错误
	TreePath(root, maxlen);
	return maxlen;
}

int main() {
	return 0;
}