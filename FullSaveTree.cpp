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
    int val;
    if (!fscanf(file, "%d ", &val) || val == MARKER)
        return;

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
}
