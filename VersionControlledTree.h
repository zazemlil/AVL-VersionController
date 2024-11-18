#pragma once

#include "Tree.h"
#include "ActionType.h"

#include <string>
#include <tuple>
#include <fstream>

class VersionControlledTree : public Tree {
	std::string versionsFilePath;

	void addVersionAction(ActionType action, int key);
	std::tuple<ActionType, int> getVersionAction(std::string s);

public:
	VersionControlledTree(std::string versionsFilePath);

	void setVersionsFilePath(std::string path);
	std::string getVersionsFilePath();

	bool insert(int k);
	bool remove(int k);
	bool selectVersion(int version);
};
