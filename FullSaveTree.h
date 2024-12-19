#pragma once

#include <string>
#include <fstream>
#include <iostream>

#include "Tree.h"

#define MARKER "#"

class FullSaveTree : public Tree {
	std::string versionsFilePath;
	int lastVersionNumber;
	std::streampos lastVersionIndex, prevVersionIndex;

	std::fstream getFileStream(std::ios_base::openmode params);
	std::fstream getFileStream(std::string path, std::ios_base::openmode params);

	void serialize(Node* root, std::string& data);
	//void deSerialize(Node*& root, std::fstream& file);
	void deSerialize(Node*& root, std::string& data);

public:
	FullSaveTree(std::string versionsFilePath);

	bool insert(int k);
	bool remove(int k);
	void clear();
	//bool selectVersion(int version);
	bool selectVersion(int version, Tree* selectedTree);

	int getLastVersionNumber();
};