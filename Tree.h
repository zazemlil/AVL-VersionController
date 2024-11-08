#pragma once

#include "Node.h"
#include <iomanip>

class Tree {
private:
	Node* head;

	unsigned char getHeight(Node* p);
	int bFactor(Node* p);
	void fixHeight(Node* p);
	Node* rotateRight(Node* p);
	Node* rotateLeft(Node* q);
	Node* balance(Node* p);
	Node* findMin(Node* p);
	Node* removeMin(Node* p);

	Node* insert(Node* p, int k);
	Node* remove(Node* p, int k);
	void inOrder(Node* p);

	void order(Node* root, int space);

public:
	Tree();
	~Tree();

	void insert(int k);
	void remove(int k);
	void inOrder();
	void order();
};
