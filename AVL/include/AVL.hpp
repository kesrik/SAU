#ifndef AVL_HPP
#define AVL_HPP

#include "Node.hpp"

class AVL
{
private:
	Node *root;
	Node *ArrayAdd(Node *, const int &, int *, const int &);
	Node *SwapWithLeftChild(Node *);
	Node *SwapWithRightChild(Node *);
	void NodeUp(Node *);
	void NodeDown(Node *);
	void NodeStall(Node *);
	void DecreaseArrayLength(Node *) ;
	bool DeleteNode(Node *&);
	void preorder(Node *);
	int Height(Node *);

public:
	AVL();
	bool isEmpty() const;
	void ArrAdd(const int &, int *, const int &);
	void preorder();
	int Height();
	void Clear();
	~AVL();
};

#endif
