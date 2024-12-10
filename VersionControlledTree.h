#pragma once

#include "Tree.h"
#include "ActionType.h"

#include <string>
#include <tuple>
#include <fstream>

class VersionControlledTree : public Tree {
	std::string versionsFilePath;
	int lastVersionNumber;

	std::fstream getFileStream(std::ios_base::openmode params);

	void writeVersionAction(ActionType action, int key);
	std::tuple<ActionType, int> readVersionAction(std::string s);
	
public:
	VersionControlledTree(std::string versionsFilePath);

	void setVersionsFilePath(std::string path);
	std::string getVersionsFilePath();

	bool insert(int k);
	bool remove(int k);
	void clear();
	//bool selectVersion(int version, bool writeThisVersionAction = true);
	bool selectVersion(int version, Tree* selectedTree);

	int getLastVersionNumber();
};
