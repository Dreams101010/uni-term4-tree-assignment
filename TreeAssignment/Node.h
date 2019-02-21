#ifndef H_NODE
#define H_NODE

template <class T>
struct Node
{
	T data;
	std::shared_ptr<Node> parent;
};

#endif // !H_NODE

