#include "Tree.h"
#include <iostream>

Tree::Tree() {
	this->head = nullptr;
}

Tree::~Tree() {
	delete head;
}

Tree::Node* Tree::getHead() {
	return this->head;
}

void Tree::setHead(Node* p) {
	this->head = p;
}

unsigned char Tree::getHeight(Node* p) {
	return p ? p->height : 0;
}

int Tree::bFactor(Node* p)
{
	return getHeight(p->right) - getHeight(p->left);
}

void Tree::fixHeight(Node* p)
{
	unsigned char hl = getHeight(p->left);
	unsigned char hr = getHeight(p->right);
	p->height = (hl > hr ? hl : hr) + 1;
}

Tree::Node* Tree::rotateRight(Node* p)
{
	Node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixHeight(p);
	fixHeight(q);
	return q;
}

Tree::Node* Tree::rotateLeft(Node* q)
{
	Node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixHeight(q);
	fixHeight(p);
	return p;
}

Tree::Node* Tree::balance(Node* p)
{
	fixHeight(p);
	if (bFactor(p) == 2)
	{
		if (bFactor(p->right) < 0)
			p->right = rotateRight(p->right);
		return rotateLeft(p);
	}
	if (bFactor(p) == -2)
	{
		if (bFactor(p->left) > 0)
			p->left = rotateLeft(p->left);
		return rotateRight(p);
	}
	return p;
}

Tree::Node* Tree::insert(Node* p, int k)
{
	if (!p) {
		Node* n = new Node();
		n->key = k;
		n->height = 1;
		n->left = nullptr;
		n->right = nullptr;
		return n;
	}
	if (k < p->key)
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k);
	return balance(p);
}

Tree::Node* Tree::findMin(Node* p)
{
	return p->left ? findMin(p->left) : p;
}

Tree::Node* Tree::removeMin(Node* p)
{
	if (p->left == 0)
		return p->right;
	p->left = removeMin(p->left);
	return balance(p);
}

Tree::Node* Tree::remove(Node* p, int k) // удаление ключа k из дерева p
{
	if (!p) return 0;
	if (k < p->key)
		p->left = remove(p->left, k);
	else if (k > p->key)
		p->right = remove(p->right, k);
	else //  k == p->key 
	{
		Node* q = p->left;
		Node* r = p->right;
		delete p;
		if (!r) return q;
		Node* min = findMin(r);
		min->right = removeMin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}

void Tree::inOrder(Node* p) {
	if (p == 0) return;
	inOrder(p->left);
	std::cout << p->key << "\n";
	inOrder(p->right);
}