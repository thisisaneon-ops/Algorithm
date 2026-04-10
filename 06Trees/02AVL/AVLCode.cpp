#include<iostream>
#include<functional>
using namespace std;

template<class T>
class AVL
{
	using Comp = function<bool(T, T)>;
private:
	struct TreeNode
	{
		TreeNode(T val = T())
			: val_(val)
			, left_(nullptr)
			, right_(nullptr)
			, height_(1)
		{ }
		T val_;
		TreeNode* left_;
		TreeNode* right_;
		int height_;
	};
	Comp comp_;
	TreeNode* root_;
public:
	// 需要用户自己重载 < 运算符
	AVL(Comp comp = [](T a, T b)->bool {return a < b; })
		: root_(nullptr)
		, comp_(comp)
	{}
	~AVL()
	{
		destroy(root_);
		root_ = nullptr;
	}
public:
	void insert(const T& val)
	{
		root_ = insert(root_, val);
	}
	void erase(const T& val)
	{
		root_ = erase(root_, val);
	}
private:
	TreeNode* insert(TreeNode* node, const T& val)
	{
		if (node == nullptr)
		{
			return new TreeNode(val);
		}
		if (comp_(node->val_, val))
		{
			node->right_ = insert(node->right_, val);
			if (height(node->right_) - height(node->left_) > 1)
			{
				if (height(node->right_->right_) > height(node->right_->left_))
				{
					node = LeftRotate(node);
				}
				else
				{
					node = RightBalance(node);
				}
			}
		}
		else if(comp_(val, node->val_))
		{
			node->left_ = insert(node->left_, val);
			if (height(node->left_) - height(node->right_) > 1)
			{
				if (height(node->left_->left_) > height(node->left_->right_))
				{
					node = RightRotate(node);
				}
				else
				{
					node = LeftBalance(node);
				}
			}
		}
		node->height_ = max(height(node->left_), height(node->right_)) + 1;
		return node;
	}

	TreeNode* erase(TreeNode* node, const T& val)
	{
		if (node == nullptr)
		{
			return nullptr;
		}
		if (comp_(node->val_, val))
		{
			node->right_ = erase(node->right_, val);
			if (height(node->left_) - height(node->right_) > 1)
			{
				if (height(node->left_->left_) > height(node->left_->right_))
				{
					node = RightRotate(node);
				}
				else
				{
					node = LeftBalance(node);
				}
			}
		}
		else if (comp_(val, node->val_))
		{
			node->left_ = erase(node->left_, val);
			if (height(node->right_) - height(node->left_) > 1)
			{
				if (height(node->right_->right_) > height(node->right_->left_))
				{
					node = LeftRotate(node);
				}
				else
				{
					node = RightBalance(node);
				}
			}
		}
		else
		{
			if (node->left_ != nullptr && node->right_ != nullptr)
			{
				if (height(node->left_) > height(node->right_))
				{
					TreeNode* pre = node->left_;
					while (pre->right_ != nullptr)
					{
						pre = pre->right_;
					}
					node->val_ = pre->val_;
					node->left_ = erase(node->left_, pre->val_);
				}
				else
				{
					TreeNode* post = node->right_;
					while (post->left_ != nullptr)
					{
						post = post->left_;
					}
					node->val_ = post->val_;
					node->right_ = erase(node->right_, post->val_);
				}
			}
			else
			{
				TreeNode* child = node->left_;
				if (node->right_ != nullptr)
				{
					child = node->right_;
				}
				delete node;
				return child;
			}
		}
		node->height_ = max(height(node->left_), height(node->right_)) + 1;
		return node;
	}

private:
	int height(TreeNode* node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		return node->height_;
	}
	void destroy(TreeNode* node)
	{
		if (node == nullptr)
		{
			return;
		}
		destroy(node->left_);
		destroy(node->right_);
		delete node;
	}
	TreeNode* LeftRotate(TreeNode* node)
	{
		TreeNode* child = node->right_;
		node->right_ = child->left_;
		child->left_ = node;
		node->height_ = max(height(node->left_), height(node->right_)) + 1;
		child->height_ = max(height(child->left_), height(child->right_)) + 1;
		return child;
	}
	TreeNode* RightRotate(TreeNode* node)
	{
		TreeNode* child = node->left_;
		node->left_ = child->right_;
		child->right_ = node;
		node->height_ = max(height(node->left_), height(node->right_)) + 1;
		child->height_ = max(height(child->left_), height(child->right_)) + 1;
		return child;
	}
	TreeNode* LeftBalance(TreeNode* node)
	{
		node->left_ = LeftRotate(node->left_);
		return RightRotate(node);
	}
	TreeNode* RightBalance(TreeNode* node)
	{
		node->right_ = RightRotate(node->right_);
		return LeftRotate(node);
	}
};

int main() 
{
   
    return 0;
}