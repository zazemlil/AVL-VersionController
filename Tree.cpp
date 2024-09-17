#include "Tree.h"

Tree::Tree(int key) {
	this->head = new Node(key);
}

Tree::~Tree() {
	delete head;
}

Node* Tree::getHead() {
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

Node* Tree::rotateRight(Node* p)
{
	Node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixHeight(p);
	fixHeight(q);
	return q;
}

Node* Tree::rotateLeft(Node* q)
{
	Node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixHeight(q);
	fixHeight(p);
	return p;
}

Node* Tree::balance(Node* p)
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

Node* Tree::insert(Node* p, int k)
{
	if (!p) return new Node(k);
	if (k < p->key)
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k);
	return balance(p);
}

Node* Tree::findMin(Node* p) 
{
	return p->left ? findMin(p->left) : p;
}

Node* Tree::removeMin(Node* p)
{
	if (p->left == 0)
		return p->right;
	p->left = removeMin(p->left);
	return balance(p);
}

Node* Tree::remove(Node* p, int k) // удаление ключа k из дерева p
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

void Tree::deepShow(Node* p) {
	if (p == 0) return;
	deepShow(p->left);
	p->printData();
	deepShow(p->right);
}