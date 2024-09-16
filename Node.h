#pragma once

struct Node
{
	int key;
	unsigned char height;
	Node* left;
	Node* right;

	Node(int key);
	void printData();
};