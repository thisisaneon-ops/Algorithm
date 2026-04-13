/*
AVL的本质是一颗二叉平衡搜索树，有以下几个关键知识：

1. 理解掌握左旋右旋的原因、原理以及代码实现
2. 理解掌握左平衡右平衡原因、原理以及代码实现
3. 熟练掌握四种不平衡状态和对应触发状态的对应关系
4. 理解旋转操作参数是什么以及为什么是下旋节点（失衡节点）
5. 能清晰的写出erase函数的每个分支，以及相同功能的合理代码复用

AVL树本身的逻辑思维难点在于旋转操作，其他操作和BST树基本相同，所以掌握起来并非绝对困难，但是掌握指针指向、内存管理、代码复用、鲁棒性训练的好材料。

下面是具体的代码实现：
*/

#include<iostream>
#include<functional>
#include<algorithm>
using namespace std;

template<class T>
class AVL {
	using Comp = function<bool(T, T)>;
private:
	struct TreeNode {
		TreeNode(T init_val = T())
			: val(init_val)
			, left(nullptr)
			, right(nullptr)
			, height(1){
		}
		T val;
		TreeNode* left;
		TreeNode* right;
		int height;
	};
	Comp comp;
	TreeNode* root;
public:
	AVL()
		: root(nullptr)
		, comp([](T a, T b)->bool {return a < b; }) {
	}
	~AVL() {
		destroy(root);
		root = nullptr;
	}
public:
	void insert(const T& val) {
		root = insert(root, val);
	}
	void erase(const T& val) {
		root = erase(root, val);
	}
private:
	TreeNode* insert(TreeNode* node, const T& val) {
		if (node == nullptr) {
			return new TreeNode(val);
		}
		if (comp(node->val, val)) {
			node->right = insert(node->right, val);
			if (height(node->right) - height(node->left) > 1) {
				if (height(node->right->right) > height(node->right->left)){
					node = LeftRotate(node);
				}
				else {
					node = RightBalance(node);
				}
			}
		}
		else if (comp(val, node->val)) {
			node->left = insert(node->left, val);
			if (height(node->left) - height(node->right) > 1) {
				if (height(node->left->left) > height(node->left->right)) {
					node = RightRotate(node);
				}
				else {
					node = LeftBalance(node);
				}
			}
		}
		node->height = max(height(node->left), height(node->right)) + 1;
		return node;
	}
	TreeNode* erase(TreeNode* node, const T& val){
		if (node == nullptr) {
			return nullptr;
		}
		if (comp(node->val, val)){
			node->right = erase(node->right, val);
			if (height(node->left) - height(node->right) > 1) {
				if (height(node->left->left) > height(node->left->right)){
					node = RightRotate(node);
				}
				else {
					node = LeftBalance(node);
				}
			}
		}
		else if (comp(val, node->val)){
			node->left = erase(node->left, val);
			if (height(node->right) - height(node->left) > 1) {
				if (height(node->right->right) > height(node->right->left)) {
					node = LeftRotate(node);
				}
				else {
					node = RightBalance(node);
				}
			}
		}
		else {
			if (node->left && node->right) {
				if (height(node->left) > height(node->right)){
					TreeNode* pre = node->left;
					while (pre->right) {
						pre = pre->right;
					}
					node->val = pre->val;
					node->left = erase(node->left, pre->val);
				}
				else {
					TreeNode* post = node->right;
					while (post->left) {
						post = post->left;
					}
					node->val = post->val;
					node->right = erase(node->right, post->val);
				}
			}
			else {
				TreeNode* child = node->left;
				if (node->right) {
					child = node->right;
				}
				delete node;
				return child;
			}
		}
		node->height = max(height(node->left), height(node->right)) + 1;
		return node;
	}
private:
	TreeNode* LeftRotate(TreeNode* node) {
		TreeNode* child = node->right;
		node->right = child->left;
		child->left = node;
		node->height = max(height(node->left), height(node->right)) + 1;
		child->height = max(height(child->left), height(child->right)) + 1;
		return child;
	}
	TreeNode* RightRotate(TreeNode* node) {
		TreeNode* child = node->left;
		node->left = child->right;
		child->right = node;
		node->height = max(height(node->left), height(node->right)) + 1;
		child->height = max(height(child->left), height(child->right)) + 1;
		return child;
	}
	TreeNode* LeftBalance(TreeNode* node) {
		node->left = LeftRotate(node->left);
		return RightRotate(node);
	}
	TreeNode* RightBalance(TreeNode* node) {
		node->right = RightRotate(node->right);
		return LeftRotate(node);
	}
private:
	void destroy(TreeNode* node){
		if(node == nullptr)
			return;
		destroy(node->left);
		destroy(node->right);
		delete node;
	}
	int height(TreeNode* node){
		if (node == nullptr)
			return 0;
		return node->height;
	}
};

int main(){

	return 0;
}