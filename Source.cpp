#include "Tree.h"

int main() {
	Tree* tree = new Tree();

	tree->insert(3);
	tree->insert(2);
	tree->insert(-1);
	tree->insert(-40);
	tree->insert(10);
	tree->insert(9);
	tree->insert(8);

	tree->inOrder();

	return 0;
}