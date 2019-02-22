#include "pch.h"
#include <vector>
#include <memory>
#include <iostream>
#include <exception>
#include <stdexcept>
#include "Node.h"
#include "Tree.h"

template <class T>
std::shared_ptr<Node<T>> Tree<T>::FindLeftChild(std::shared_ptr<Node<T>> parent)
{
	std::shared_ptr<Node<T>> retVal = NULL;
	for (unsigned int i = 0; i < tree.size(); i++)
	{
		if (tree[i]->parent == parent)
		{
			if (tree[i]->data < parent->data)
			{
				retVal = tree[i];
				break;
			}
		}
	}
	return retVal;
}

template <class T>
std::shared_ptr<Node<T>> Tree<T>::FindRightChild(std::shared_ptr<Node<T>> parent)
{
	std::shared_ptr<Node<T>> retVal = NULL;
	for (unsigned int i = 0; i < tree.size(); i++)
	{
		if (tree[i]->parent == parent)
		{
			if (tree[i]->data > parent->data)
			{
				retVal = tree[i];
				break;
			}
		}
	}
	return retVal;
}

template <class T>
std::shared_ptr<Node<T>> Tree<T>::AddFindParent(T data)
{
	if (tree.empty())
	{
		return NULL;
	}
	std::shared_ptr<Node<T>> x = tree[0]; // root
	while (true)
	{
		std::shared_ptr<Node<T>> y = NULL;
		if (data < x->data)
		{
			y = FindLeftChild(x);
		}
		else if (data > x->data)
		{
			y = FindRightChild(x);
		}
		else
		{
			throw std::invalid_argument("Couldn't add node to tree. Node with this data already exists.");
		}

		if (y == NULL) // sub-tree is empty
		{
			return x;
		}
		else
		{
			x = y;
		}
	}
}

template <class T>
std::shared_ptr<Node<T>> Tree<T>::FindMinimum(std::shared_ptr<Node<T>> subTreeRoot)
{
	auto curNode = subTreeRoot;
	auto nextNode = FindLeftChild(curNode);
	while (nextNode != NULL)
	{
		curNode = nextNode;
		nextNode = FindLeftChild(curNode);
	}
	return curNode;
}

template <class T>
std::shared_ptr<Node<T>> Tree<T>::FindMaximum(std::shared_ptr<Node<T>> subTreeRoot)
{
	auto curNode = subTreeRoot;
	auto nextNode = FindRightChild(curNode);
	while (nextNode != NULL)
	{
		curNode = nextNode;
		nextNode = FindRightChild(curNode);
	}
	return curNode;
}

template <class T>
void Tree<T>::PreorderTraversal(std::shared_ptr<Node<T>> node)
{
	if (node != NULL)
	{
		std::cout << node->data << " ";
		PreorderTraversal(FindLeftChild(node));
		PreorderTraversal(FindRightChild(node));
	}
}

template <class T>
void Tree<T>::InorderTraversal(std::shared_ptr<Node<T>> node)
{
	if (node != NULL)
	{
		InorderTraversal(FindLeftChild(node));
		std::cout << node->data << " ";
		InorderTraversal(FindRightChild(node));
	}
}

template <class T>
void Tree<T>::PostorderTraversal(std::shared_ptr<Node<T>> node)
{
	if (node != NULL)
	{
		PostorderTraversal(FindLeftChild(node));
		PostorderTraversal(FindRightChild(node));
		std::cout << node->data << " ";
	}
}

template <class T>
void Tree<T>::TreeUnionPreorderFrom(Tree<T>& unionTo, std::shared_ptr<Node<T>> node)
{
	if (node != NULL)
	{
		if (unionTo.Contains(node->data))
		{
			std::cout << "Couldn't add node with data " << node->data
				<< " : node with that data already exists" << std::endl;
		}
		else
		{
			unionTo.Add(node->data);
		}
		TreeUnionPreorderFrom(unionTo, FindLeftChild(node));
		TreeUnionPreorderFrom(unionTo, FindRightChild(node));
	}
}

template <class T>
void Tree<T>::TreeUnionPreorderFrom(Tree<T>& unionTo) // add element from this tree to other
{
	if (IsEmpty())
	{
		return;
	}
	else
	{
		TreeUnionPreorderFrom(unionTo, tree[0]);
	}
}

template <class T>
std::shared_ptr<Node<T>>Tree<T>::GetNode(T data)
{
	if (tree.empty())
	{
		return NULL;
	}
	std::shared_ptr<Node<T>> curNode = tree[0];
	while (curNode != NULL)
	{
		if (data == curNode->data)
		{
			return curNode;
		}
		else if (data < curNode->data)
		{
			curNode = FindLeftChild(curNode);
		}
		else // greater
		{
			curNode = FindRightChild(curNode);
		}
	}
	return NULL;
}

template <class T>
T Tree<T>::Remove(std::shared_ptr<Node<T>> ptr)
{
	// TODO: check if pointer is actually in vector
	if (ptr == NULL)
	{
		throw std::invalid_argument("Pointer was null.");
	}
	std::shared_ptr<Node<T>> leftChild = FindLeftChild(ptr);
	std::shared_ptr<Node<T>> rightChild = FindRightChild(ptr);
	T retVal = ptr->data;
	if (leftChild != NULL && rightChild != NULL)
	{
		auto nextNode = FindMinimum(rightChild); // minimum is either a leaf or has a single child
		T valueOfNextNode = Remove(nextNode);
		ptr->data = valueOfNextNode;
		// we need to remove nextNode for case when it is not a leaf (but has a single child)
		// consider the following tree sequence: 10 9 15 14 12 13 (remove 10)
	}
	else if (leftChild != NULL || rightChild != NULL) // only one of them
	{
		if (leftChild != NULL)
		{
			leftChild->parent = ptr->parent;
		}
		else // rightChild != NULL
		{
			rightChild->parent = ptr->parent;
		}
		RemoveNodeFromVector(ptr);
	}
	else
	{
		RemoveNodeFromVector(ptr);
	}
	return retVal;
}

template <class T>
void Tree<T>::RemoveNodeFromVector(std::shared_ptr<Node<T>> node)
{
	bool found = false;
	unsigned int idx = 0;
	for (unsigned int i = 0; i < tree.size(); i++)
	{
		if (tree[i] == node)
		{
			idx = i;
			found = true;
			break;
		}
	}
	if (!found)
	{ 
		throw std::invalid_argument("Couldn't find node in internal vector.");
	}
	auto iter = tree.cbegin();
	iter += idx;
	tree.erase(iter);
}

template <class T>
Tree<T>::Tree() {}

template <class T>
Tree<T>::Tree(std::vector<T> vec)
{
	for (int i : vec)
	{
		Add(i);
	}
}

template <class T>
Tree<T>::Tree(std::shared_ptr<std::vector<T>> vec)
{
	for (unsigned int i = 0; i < vec->size(); i++)
	{
		Add(vec->at(i));
	}
}

template <class T>
void Tree<T>::Add(T data)
{
	std::shared_ptr<Node<T>> node(new Node<T>());
	node->data = data;
	node->parent = AddFindParent(data);
	tree.push_back(node);
}

template <class T>
bool Tree<T>::IsEmpty()
{
	return tree.empty();
}

template <class T>
bool Tree<T>::Contains(T data)
{
	return GetNode(data) != NULL;
}

template <class T>
T Tree<T>::Remove(T data)
{
	return Remove(GetNode(data));
}

template <class T>
void Tree<T>::PreorderTraversal()
{
	if (tree.empty())
	{
		return;
	}
	PreorderTraversal(tree[0]);
	std::cout << std::endl;
}

template <class T>
void Tree<T>::InorderTraversal()
{
	if (tree.empty())
	{
		return;
	}
	InorderTraversal(tree[0]);
	std::cout << std::endl;
}

template <class T>
void Tree<T>::PostorderTraversal()
{
	if (tree.empty())
	{
		return;
	}
	PostorderTraversal(tree[0]);
	std::cout << std::endl;
}

// to invert call order
// so we call this function for object where we will union to
template <class T>
void Tree<T>::TreeUnionPreorder(Tree<T>& other)
{
	other.TreeUnionPreorderFrom(*this);
}

template Tree<int>;