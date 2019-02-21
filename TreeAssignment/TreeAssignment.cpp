// TreeAssignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Tree.h"


int main()
{
	Tree<int> t1;
	t1.Add(5);
	t1.Add(3);
	t1.Add(1);
	t1.Add(2);
	t1.Add(4);
	t1.Add(8);
	t1.Add(7);
	t1.Add(6);
	t1.Add(10);
	t1.Add(9);
	t1.Add(11);

	Tree<int> t2;
	t2.Add(12);
	t2.Add(13);

	std::cout << "Before union:" << std::endl;;
	std::cout << "Tree 1 in postorder:" << std::endl;
	t1.PostorderTraversal();
	std::cout << "Tree 2 in inorder:" << std::endl;
	t2.InorderTraversal();
	
	t1.TreeUnionPreorder(t2);

	std::cout << "After union:" << std::endl;
	std::cout << "Tree 1 in postorder:" << std::endl;
	t1.PostorderTraversal();
	std::cout << "Tree 2 in inorder:" << std::endl;
	t2.InorderTraversal();
}
