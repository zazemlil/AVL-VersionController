#include "Tree.h"
#include <cstdlib>

int main() {
	Tree* tree = new Tree(1);
	Tree::insert(tree->getHead(), 3);
	Tree::insert(tree->getHead(), -2);

	Tree::deepShow(tree->getHead());

	return 0;
}