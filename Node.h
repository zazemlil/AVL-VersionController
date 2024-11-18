#pragma once

class Node {
	int key;
	unsigned char height;
	Node* left;
	Node* right;

	friend class Tree;
public:
	Node();
	Node(int key);
};