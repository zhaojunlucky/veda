#pragma once
namespace veda
{
	template <class T>
	struct BaseTreeNode
	{
		T data;

		BaseTreeNode(){}
		BaseTreeNode(T data)
		{
			this->data = data;
		}

		bool operator==(const BaseTreeNode& other)
		{
			return (this == &other || this->data == other.data);
		}
	};

	template <class T>
	struct BinaryTreeNode : public BaseTreeNode < T >
	{
		BinaryTreeNode* left;
		BinaryTreeNode* right;

		BinaryTreeNode()
		{
			left = right = 0;
		}

		BinaryTreeNode(T data)
			:BaseTreeNode(data)
		{
			left = right = 0;
		}

		bool operator==(const BinaryTreeNode& other)
		{
			return (this == &other ||
				(this->data == other.data && this->left == other.left && this->right == other.right));
		}
		
	};
}