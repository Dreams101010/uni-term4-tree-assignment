// TreeAssignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <memory>
#include <exception>
#include <stdexcept>
#include "Tree.h"

std::shared_ptr<std::vector<int>> InitVector()
{
	int count = 0;
	std::cout << "Enter number of elements:";
	std::cin >> count;
	if (count <= 0)
	{
		throw std::invalid_argument("Cannot init vector with <= 0 elements");
	}
	auto vec = std::shared_ptr<std::vector<int>>(new std::vector<int>(count));
	std::cout << "Enter vector elements:" << std::endl;
	for (int i = 0; i < count; i++)
	{
		int value = 0;
		std::cin >> value;
		vec->operator[](i) = value;
	}
	return vec;
}

void Driver()
{
	try
	{
		std::cout << "Initializing sequence 1..." << std::endl;
		auto v1 = InitVector();
		auto t1 = Tree<int>(v1);

		std::cout << "Initializing sequence 2 ..." << std::endl;
		auto v2 = InitVector();
		auto t2 = Tree<int>(v2);

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
	catch (std::exception e)
	{
		std::cout << "Exception occured: " << e.what() << std::endl;
	}
}

int main()
{
	Driver();
}
