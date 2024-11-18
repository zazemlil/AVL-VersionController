#include "VersionControlledTree.h"

void VersionControlledTree::addVersionAction(int key, ActionType action)
{
}

std::tuple<int, ActionType> VersionControlledTree::getVersionAction(std::string s)
{
	return std::tuple<int, ActionType>();
}

VersionControlledTree::~VersionControlledTree()
{
}

void VersionControlledTree::setVersionsFilePath(std::string path)
{
	versionsFilePath = path;
}

std::string VersionControlledTree::getVersionsFilePath()
{
	return versionsFilePath;
}

bool VersionControlledTree::insert(int k)
{
	return false;
}

bool VersionControlledTree::remove(int k)
{
	return false;
}

bool VersionControlledTree::selectVersion(int version)
{
	return false;
}
