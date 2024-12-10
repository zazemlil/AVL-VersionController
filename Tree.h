#pragma once

#include "Node.h"
#include <iomanip>

class Tree {
private:
	Node* head;
	bool isLastOperationSuccessful;

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
	void clear(Node* p);

	void order(Node* root, int space);

protected:
	bool isLastOpSuccessful();

public:
	Tree();
	~Tree();


	Node*& getHead();

	void insert(int k);
	void remove(int k);
	void clear();
	bool order();
};
