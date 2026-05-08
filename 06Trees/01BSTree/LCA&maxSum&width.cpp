#include<iostream>
#include<vector>
#include<queue>
#include<utility>
using namespace std;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
};

#ifdef DEBUG
// 二叉树的公共祖先
TreeNode* LCAhelper(TreeNode* node, TreeNode* p, TreeNode* q) {
	if (node == nullptr || node == p || node == q) { return node; }
	TreeNode* left = LCAhelper(node->left, p, q);
	TreeNode* right = LCAhelper(node->right, p, q);
	if ((left == p && right == q) || (left == q && right == p)) { return node; }
	if (left != nullptr) { return left; }
	return right;
}
TreeNode* BTLCA(TreeNode* root, TreeNode* p, TreeNode* q) {
	return LCAhelper(root, p, q);
}
// 二叉树的最大路径和
// 原则：规定状态：只管当前层，node必选，其他灵活选择！
int Sum(TreeNode* node, int& maxSum) {
	if (node == nullptr) { return 0; }
	int left = Sum(node->left, maxSum) + node->val;
	int right = Sum(node->right, maxSum) + node->val;
	maxSum = std::max({ maxSum, node->val, left, right, left + right - node->val });
	return std::max({ node->val, left, right });
}
int maxPathSum(TreeNode* root) {
	int maxSum = root->val;
	Sum(root, maxSum);
	return maxSum;
}
// 按层遍历的更好写法
vector<vector<int>>LevelOrder(TreeNode* root) {
	vector<vector<int>>ret;
	queue<TreeNode*>q;
	if (root == nullptr) { return ret; }
	q.push(root);
	int level = 0;
	while (!q.empty()) {
		int curLevelSize = q.size();
		ret.push_back(vector<int>());
		for (int i = 0; i < curLevelSize; i++) {
			auto front = q.front();
			q.pop();
			ret[ret.size() - 1][i] = front->val;
			if (front->left) { q.push(front->left); }
			if (front->right) { q.push(front->right); }
		}
	}
	return ret;
}
// 最大宽度
int widthOfBinaryTree(TreeNode* root) {
	long long maxWidth = 0;
	using Pair = pair<TreeNode*, int>;
	queue<Pair>q;
	if (root == 0) { return 0; }
	q.emplace(root, 0);
	while (!q.empty()) {
		long long width = 0;
		long long curSize = q.size();
		long long firstIdx = q.front().second;
		for (long long i = 0; i < curSize; i++) {
			auto front = q.front();
			q.pop();
			long long fatherIdx = front.second;
			width = fatherIdx - firstIdx + 1;
			if (front.first->left) { q.emplace(front.first->left, 2 * fatherIdx + 1); }  // 注意 公式用的坐标是当前层这个人的相对坐标
			if (front.first->right) { q.emplace(front.first->right, 2 * fatherIdx + 2); }
		}
		maxWidth = max(maxWidth, width);
	}
	return maxWidth;
}
#endif // DEBUG

// LCA
class LCASolution {
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		return LCA(root, p, q);
	}
	TreeNode* LCA(TreeNode* node, TreeNode* p, TreeNode* q) {
		if (node == nullptr || node == p || node == q) {
			return node;
		}
		TreeNode* left = LCA(node->left, p, q);
		TreeNode* right = LCA(node->right, p, q);
		if ((left == p && right == q) || (left == q && right == p)) {
			return node;
		}
		if (left != nullptr) {
			return left;
		}
		return right;
	}
};
// maxSum
class maxSumSolution {
public:
	int maxSum(TreeNode* root) {
		int ret = root->val;
		maxSum(root, ret);
		return ret;
	}
	int maxSum(TreeNode* node, int& maxsum) {
		if (node == nullptr) { return 0; }
		int left = maxSum(node->left, maxsum);
		int right = maxSum(node->right, maxsum);
		maxsum = max({ maxsum, left + node->val, right + node->val, node->val, left + right + node->val });
		return max({ left + node->val, right + node->val, node->val });
	}
};
// maxWidth(Pay no attention to signed integer Overflow)
class maxWidthSolutionWithoutOverFlow {
public:
	int maxWidth(TreeNode* root) {
		if (root == nullptr) { return 0; }
		using Pair = pair<TreeNode*, int>;
		queue<Pair>q;
		q.emplace(root, 0);
		int maxWidth = 0;
		while (!q.empty()) {
			int curLevelSize = q.size();
			int startIdx = q.front().second;
			int curWidth = 0;
			for (int i = 0; i < curLevelSize; i++) {
				auto front = q.front();
				auto [node, index] = front;
				curWidth = index - startIdx + 1;
				q.pop();
				if (node->left) { q.emplace(node->left, 2 * index + 1 ); }
				if (node->right) { q.emplace(node->right, 2 * index + 2 ); }
			}
			maxWidth = max(maxWidth, curWidth);
		}
		return maxWidth;
	}
};
class maxWidthSolutionConsideringOverFlow {
public:
	int maxWidth(TreeNode* root) {
		if (root == nullptr) { return 0; }
		using Pair = pair<TreeNode*, long long>;
		queue<Pair>q;
		queue<Pair>q;
		q.emplace(root, 0);
		long long maxWidth = 0;
		while (!q.empty()) {
			int curLevelSize = q.size();
			long long startIdx = q.front().second;
			long long curWidth = 0;
			for (int i = 0; i < curLevelSize; i++) {
				auto front = q.front();
				auto [node, index] = front;
				curWidth = index - startIdx + 1;
				q.pop();
				if (node->left) { q.emplace(node->left, 2 * (index - startIdx)+1); }
				if (node->right) { q.emplace(node->right, 2 * (index - startIdx) + 2); }
			}
			maxWidth = max(maxWidth, curWidth);
		}
		return maxWidth;
	}
};