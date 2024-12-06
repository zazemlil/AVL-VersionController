#pragma once

#include "Tree.h"

#include <string>
#include <fstream>

#define MARKER '#'

class FullSaveTree : public Tree {
	std::string versionsFilePath;
	int lastVersionNumber;

	std::fstream getFileStream(std::ios_base::openmode params);

	void serialize(Node* root, std::fstream& file);
	void deSerialize(Node*& root, std::fstream& file);

public:
	FullSaveTree(std::string versionsFilePath);

	bool insert(int k);
	bool remove(int k);
	void clear();
	bool selectVersion(int version);
};