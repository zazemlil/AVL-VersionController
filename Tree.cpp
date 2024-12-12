#include <iostream>
#include "Tree.h"

Tree::Tree() {
	this->head = nullptr;
}

Tree::~Tree() {
	delete head;
}

Node*& Tree::getHead()
{
	return head;
}

bool Tree::isLastOpSuccessful()
{
	return isLastOperationSuccessful;
}

unsigned char Tree::getHeight(Node* p) {
	return p ? p->height : 0;
}

int Tree::bFactor(Node* p) {
	return getHeight(p->right) - getHeight(p->left);
}

void Tree::fixHeight(Node* p) {
	unsigned char hl = getHeight(p->left);
	unsigned char hr = getHeight(p->right);
	p->height = (hl > hr ? hl : hr) + 1;
}

Node* Tree::rotateRight(Node* p) {
	Node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixHeight(p);
	fixHeight(q);
	return q;
}

Node* Tree::rotateLeft(Node* q) {
	Node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixHeight(q);
	fixHeight(p);
	return p;
}

Node* Tree::balance(Node* p) {
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

Node* Tree::insert(Node* p, int k) {
	if (!p) {
		Node* n = new Node();
		n->key = k;
		n->height = 1;
		n->left = nullptr;
		n->right = nullptr;
		isLastOperationSuccessful = true;
		return n;
	}
	if (k < p->key)
		p->left = insert(p->left, k);
	else if (k > p->key)
		p->right = insert(p->right, k);
	return balance(p);
}

void Tree::insert(int k) {
	isLastOperationSuccessful = false;
	this->head = insert(this->head, k);
}

Node* Tree::findMin(Node* p) {
	return p->left ? findMin(p->left) : p;
}

Node* Tree::removeMin(Node* p) {
	if (p->left == 0)
		return p->right;
	p->left = removeMin(p->left);
	return balance(p);
}

Node* Tree::remove(Node* p, int k) {
	if (!p) return 0;
	if (k < p->key)
		p->left = remove(p->left, k);
	else if (k > p->key)
		p->right = remove(p->right, k);
	else //  k == p->key 
	{
		isLastOperationSuccessful = true;
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

void Tree::remove(int k) {
	isLastOperationSuccessful = false;
	this->head = remove(this->head, k);
}

void Tree::clear(Node*& p)
{
	if (p == nullptr) return;
	clear(p->left);
	clear(p->right);
	delete p;
	p = nullptr;
}

void Tree::clear() {
	clear(this->head);
	head = nullptr;
}

void Tree::order(Node* root, int space) {
	if (root == nullptr)
		return;
	isLastOperationSuccessful = true;
	space += 10;

	order(root->right, space);

	std::cout << std::endl;
	for (int i = 10; i < space; i++)
		std::cout << " ";
	std::cout << root->key << "\n";

	order(root->left, space);
}

bool Tree::order() {
	isLastOperationSuccessful = false;
	order(this->head, 0);
	if (isLastOperationSuccessful) return true;
	return false;
}