#ifndef H_TREE
#define H_TREE

#include <vector>
#include <memory>
#include "Node.h"

template <class T>
class Tree
{
	std::vector<std::shared_ptr<Node<T>>> tree;
	std::shared_ptr<Node<T>> FindLeftChild(std::shared_ptr<Node<T>> parent);
	std::shared_ptr<Node<T>> FindRightChild(std::shared_ptr<Node<T>> parent);
	std::shared_ptr<Node<T>> AddFindParent(T data);
	std::shared_ptr<Node<T>> FindMinimum(std::shared_ptr<Node<T>> subTreeRoot);
	std::shared_ptr<Node<T>> FindMaximum(std::shared_ptr<Node<T>> subTreeRoot);
	void PreorderTraversal(std::shared_ptr<Node<T>> node);
	void InorderTraversal(std::shared_ptr<Node<T>> node);
	void PostorderTraversal(std::shared_ptr<Node<T>> node);
	void TreeUnionPreorderFrom(Tree<T>& unionTo, std::shared_ptr<Node<T>> node);
	void TreeUnionPreorderFrom(Tree<T>& unionTo); // add element from this tree to other
	std::shared_ptr<Node<T>> GetNode(T data);
	T Remove(std::shared_ptr<Node<T>> ptr);
	void RemoveNodeFromVector(std::shared_ptr<Node<T>> node);

public:
	Tree();
	Tree(std::vector<T> vec);
	Tree(std::shared_ptr<std::vector<T>> vec);
	void Add(T data);
	bool IsEmpty();
	bool Contains(T data);
	T Remove(T data);
	void PreorderTraversal();
	void InorderTraversal();
	void PostorderTraversal();
	void TreeUnionPreorder(Tree<T>& other);
};

#endif // !H_TREE

