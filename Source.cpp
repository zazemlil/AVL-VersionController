#include "Tree.h"
#include <iostream>
#include <string>
#include <Windows.h>

enum A
{
	ASD = 'i'
};

int main() {
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Tree* tree = new Tree();

	bool isRunning = true;
	while (isRunning) {
		char selectedItem;
		std::cout << "1. ������� ������.\n";
		std::cout << "2. �������� �������� ������ � ���������� ������� �����������.\n";
		std::cout << "3. ������� ������.\n";
		std::cout << "4. �������� ����.\n";
		std::cout << "5. ������� ����.\n";
		std::cout << "0. ����� �� ���������.\n";
		std::cout << "����: ";

		std::cin >> selectedItem;
		switch (selectedItem)
		{
		case '1': {

			break;
		}
		case '2': {

			break;
		}
		case '3': {
			tree->order();
			break;
		}
		case '4': {
			int key;
			std::cout << "Enter node key: ";
			std::cin >> key;
			tree->insert(key);
			break;
		}
		case '5': {
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