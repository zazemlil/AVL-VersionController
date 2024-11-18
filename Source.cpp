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
		std::cout << "1. Выбрать версию.\n";
		std::cout << "2. Сравнить контроль версий с алгоритмом полного копирования.\n";
		std::cout << "3. Вывести дерево.\n";
		std::cout << "4. Добавить узел.\n";
		std::cout << "5. Удалить узел.\n";
		std::cout << "0. Выход из программы.\n";
		std::cout << "Ввод: ";

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