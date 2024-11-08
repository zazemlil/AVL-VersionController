#include "Tree.h"
#include <iostream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;


int main() {
	Tree* tree = new Tree();

	bool isRunning = true;
	while (isRunning) {
		char selectedItem;
		std::cout << "1. Select version\n";
		std::cout << "2. Output tree\n";
		std::cout << "3. Add node\n";
		std::cout << "4. Delete node\n";
		std::cout << "0. Exit\n";
		std::cout << "Enter: ";

		std::cin >> selectedItem;
		switch (selectedItem)
		{
		case '1': {
			std::string path = "./AVLversions/";
			int i = 0;
			for (const auto& entry : fs::directory_iterator(path)) {
				std::cout << i << ") " << entry.path().filename() << std::endl;
				i++;
			}
			std::cout << "Enter: ";
			int selected;
			std::cin >> selected;
			std::string fileName = "";
			if (selected <= i and selected >= 0) {
				i = 0;
				for (const auto& entry : fs::directory_iterator(path)) {
					if (selected == i) {
						fileName = entry.path().filename().string();
						break;
					}
					i++;
				}

				std::cout << fileName << "\n";
			}
			else {
				std::cout << "empty\n";
			}
			break;
		}
		case '2': {
			tree->order();
			break;
		}
		case '3': {
			int key;
			std::cout << "Enter node key: ";
			std::cin >> key;
			tree->insert(key);
			break;
		}
		case '4': {
			int key;
			std::cout << "Enter node key: ";
			std::cin >> key;
			tree->remove(key);
			break;
		}
		case '0': {
			isRunning = false;
			break;
		}
		default:
			std::cout << "...\n";
			break;
		}

		system("Pause");
		system("cls");
	}
	return 0;
}