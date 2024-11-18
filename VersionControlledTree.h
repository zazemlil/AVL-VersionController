#pragma once

#include "Tree.h"
#include "ActionType.h"
#include <tuple>

class VersionControlledTree : public Tree {
	std::string versionsFilePath;

	void addVersionAction(int key, ActionType action);
	std::tuple<int, ActionType> getVersionAction(std::string s);

public:
	VersionControlledTree() : Tree() {};
	~VersionControlledTree();

	void setVersionsFilePath(std::string path);
	std::string getVersionsFilePath();

	bool insert(int k);
	bool remove(int k);
	bool selectVersion(int version);
};
