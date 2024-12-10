#include "FullSaveTree.h"

std::fstream FullSaveTree::getFileStream(std::ios_base::openmode params)
{
    std::fstream file(versionsFilePath, params);
    if (!file.is_open()) {
        file.open(versionsFilePath, std::ios::out);
        file.close();
        file.open(versionsFilePath, params);
    }
    return file;
}

std::fstream FullSaveTree::getFileStream(std::string path, std::ios_base::openmode params)
{
    std::fstream file(path, params);
    if (!file.is_open()) {
        file.open(path, std::ios::out);
        file.close();
        file.open(path, params);
    }
    return file;
}

void FullSaveTree::serialize(Node* root, std::fstream& file)
{
    if (root == NULL) {
        file << MARKER << ' ';
        return;
    }
    file << root->key << ' ';
    serialize(root->left, file);
    serialize(root->right, file);
}

void FullSaveTree::deSerialize(Node*& root, std::fstream& file)
{
    std::string s = "";
    file >> s;
    if (s == "" || s == "\n" || s[0] == MARKER) return;

    int val = stoi(s);

    root = new Node(val);
    deSerialize(root->left, file);
    deSerialize(root->right, file);
}

FullSaveTree::FullSaveTree(std::string versionsFilePath)
{
    this->versionsFilePath = versionsFilePath;
    std::fstream file = getFileStream(std::ios::in | std::ios::out);
    lastVersionNumber = std::count(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), '\n');
    file.close();
    clear();
}

bool FullSaveTree::insert(int k)
{
    Tree::insert(k);
    if (isLastOpSuccessful()) {
        std::fstream file = getFileStream(std::ios::out | std::ios::app);
        lastVersionNumber++;
        serialize(this->getHead(), file);
        file << '\n';
        file.close();
        return true;
    }
    return false;
}

bool FullSaveTree::remove(int k)
{
    Tree::remove(k);
    if (isLastOpSuccessful()) {
        std::fstream file = getFileStream(std::ios::out | std::ios::app);
        lastVersionNumber++;
        serialize(this->getHead(), file);
        file << '\n';
        file.close();
        return true;
    }
    return false;
}

void FullSaveTree::clear()
{
    Tree::clear();
    std::fstream file = getFileStream(std::ios::out | std::ios::app);
    serialize(this->getHead(), file);
    file << '\n';
    lastVersionNumber++;
    file.close();
}

//bool FullSaveTree::selectVersion(int version)
//{
//    if (version < 1 || lastVersionNumber < version) {
//        return false;
//    }
//    Tree::clear();
//
//    std::fstream file = getFileStream(std::ios::in);
//
//    std::string s = "";
//    int k = 1;
//    while (std::getline(file, s))
//    {
//        if (k == version) break;
//        k++;
//    }
//    file.close();
//
//    file = getFileStream("tempTest.txt", std::ios::out);
//    file << s;
//    file.close();
//
//    file = getFileStream("tempTest.txt", std::ios::in);
//    deSerialize(this->getHead(), file);
//    file.close();
//    std::remove("tempTest.txt");
//
//    file = getFileStream(std::ios::out | std::ios::app);
//    serialize(this->getHead(), file);
//    file << '\n';
//    lastVersionNumber++;
//    file.close();
//
//    return true;
//}

bool FullSaveTree::selectVersion(int version, Tree* selectedTree)
{
    if (version < 1 || lastVersionNumber < version) {
        return false;
    }
    selectedTree->clear();

    std::fstream file = getFileStream(std::ios::in);

    std::string s = "";
    int k = 1;
    while (std::getline(file, s))
    {
        if (k == version) break;
        k++;
    }
    file.close();

    file = getFileStream("tempTest.txt", std::ios::out);
    file << s;
    file.close();

    file = getFileStream("tempTest.txt", std::ios::in);
    deSerialize(selectedTree->getHead(), file);
    file.close();
    std::remove("tempTest.txt");

    return true;
}

int FullSaveTree::getLastVersionNumber()
{
    return lastVersionNumber;
}
