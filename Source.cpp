#include "Tree.h"

int main() {
	Tree* tree = new Tree();
	tree->setHead(Tree::insert(tree->getHead(), 3));
	tree->setHead(Tree::insert(tree->getHead(), 2));
	tree->setHead(Tree::insert(tree->getHead(), -1));
	tree->setHead(Tree::insert(tree->getHead(), -40));
	tree->setHead(Tree::insert(tree->getHead(), 10));
	tree->setHead(Tree::insert(tree->getHead(), 9));
	tree->setHead(Tree::insert(tree->getHead(), 8));

	Tree::inOrder(tree->getHead());

	return 0;
}