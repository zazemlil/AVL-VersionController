#pragma once

class Node {
	int key;
	unsigned char height;
	Node* left;
	Node* right;

	friend class Tree;
	friend class FullSaveTree;
public:
	Node();
	Node(int key);
};