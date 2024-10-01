#pragma once
#include "Node.h"

class Tree {
private:
	struct Node
	{
		int key;
		unsigned char height;
		Node* left;
		Node* right;
	};
	Node* head;

	static unsigned char getHeight(Node* p);
	static int bFactor(Node* p);
	static void fixHeight(Node* p);
	static Node* rotateRight(Node* p);
	static Node* rotateLeft(Node* q);
	static Node* balance(Node* p);
	static Node* findMin(Node* p);
	static Node* removeMin(Node* p);

public:
	Tree();
	~Tree();

	Node* getHead();
	void setHead(Node* p);
	static Node* insert(Node* p, int k);
	static Node* remove(Node* p, int k);
	static void inOrder(Node* p);
};
