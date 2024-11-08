#include "Node.h"

Node::Node() {}

Node::Node(int key) {
	this->key = key;
	this->height = 1;
	this->left = nullptr;
	this->right = nullptr;
}