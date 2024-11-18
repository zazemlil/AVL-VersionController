#include "VersionControlledTree.h"

void VersionControlledTree::addVersionAction(ActionType action, int key)
{
}

std::tuple<ActionType, int> VersionControlledTree::getVersionAction(std::string s)
{
	return std::tuple<ActionType, int>();
}

VersionControlledTree::VersionControlledTree(std::string versionsFilePath) : Tree()
{
	this->versionsFilePath = versionsFilePath;
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
    if (version <= 0) return false;
    
    std::fstream file(versionsFilePath, std::ios::in | std::ios::out);
    if (!file.is_open()) {
        file.open(versionsFilePath, std::ios::out);
        if (!file.is_open()) return false;
        
        file.close();
        file.open(versionsFilePath, std::ios::in | std::ios::out);
    }
    
    std::string line;
    int currentLine = 1;

    while (std::getline(file, line)) {
        if (line == "") break;
        if (currentLine == version) {
            file.close();
            return true;
        }
        ++currentLine;
    }

    file.close();
    return false;
}
