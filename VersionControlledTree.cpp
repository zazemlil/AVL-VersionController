#include "VersionControlledTree.h"

void VersionControlledTree::writeVersionAction(ActionType action, int key)
{
    std::fstream file = getFileStream(std::ios::out | std::ios::app);
    file << char(action) << key << '\n';
    lastVersionNumber++;
    file.close();
}

std::tuple<ActionType, int> VersionControlledTree::readVersionAction(std::string s)
{
    ActionType action = ActionType(s[0]);

    std::string numberPart = s.substr(1);

    size_t pos = 0;
    int number = std::stoi(numberPart, &pos);

    return std::make_tuple(action, number);
}

std::fstream VersionControlledTree::getFileStream(std::ios_base::openmode params)
{
    std::fstream file(versionsFilePath, params);
    if (!file.is_open()) {
        file.open(versionsFilePath, std::ios::out);
        file.close();
        file.open(versionsFilePath, params);
    }
    return file;
}

VersionControlledTree::VersionControlledTree(std::string versionsFilePath) : Tree()
{
	this->versionsFilePath = versionsFilePath;
    writeVersionAction(T_CLEAR_TREE, 0);
    std::fstream file = getFileStream(std::ios::in | std::ios::out);
    lastVersionNumber = std::count(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), '\n');
    file.close();
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
    Tree::insert(k);
    if (isLastOpSuccessful()) {
        writeVersionAction(T_INSERT, k);
        return true;
    }
	return false;
}

bool VersionControlledTree::remove(int k)
{
    Tree::remove(k);
    if (isLastOpSuccessful()) {
        writeVersionAction(T_REMOVE, k);
        return true;
    }
    return false;
}

void VersionControlledTree::clear()
{
    Tree::clear();
    writeVersionAction(T_CLEAR_TREE, 0);
}

bool VersionControlledTree::selectVersion(int version, bool writeThisVersionAction)
{
    if (version <= 0) return false;
    
    std::fstream file = getFileStream(std::ios::in | std::ios::out);
    int size = std::count(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), '\n');
    if (version > size) return false;
    file.close();

    file = getFileStream(std::ios::in | std::ios::out);
    std::string line;
    int currentLineNumber = 1;
    Tree::clear();
    while (std::getline(file, line)) {
        ActionType a;
        int k;
        std::tie(a, k) = readVersionAction(line);
        switch (a)
        {
        case T_INSERT:
            Tree::insert(k);
            break;
        case T_REMOVE:
            Tree::remove(k);
            break;
        case T_CLEAR_TREE:
            Tree::clear();
            break;
        case T_VERSION_SELECTED:
            Tree::clear();
            selectVersion(k, false);
            break;
        }
        if (currentLineNumber == version) {
            file.close();
            if (writeThisVersionAction) writeVersionAction(T_VERSION_SELECTED, version);
            return true;
        }
        ++currentLineNumber;
    }
    return false;
}

int VersionControlledTree::getLastVersionNumber()
{
    return lastVersionNumber;
}