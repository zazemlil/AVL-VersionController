#include "Tree.h"
#include "VersionControlledTree.h"

#include <iostream>
#include <string>
#include <Windows.h>

int main() {
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Tree* tree = new Tree();
	VersionControlledTree* tree2 = new VersionControlledTree("AVLversions.txt");

    bool isRunning = true;

    while (isRunning) {
        std::string selectedItem;
        std::cout << "1. Выбрать версию.\n";
        std::cout << "2. Сравнить контроль версий с алгоритмом полного копирования.\n";
        std::cout << "3. Вывести дерево.\n";
        std::cout << "4. Добавить узел.\n";
        std::cout << "5. Удалить узел.\n";
        std::cout << "0. Выход из программы.\n";
        std::cout << "Ввод: ";

        std::cin >> selectedItem;

        if (selectedItem.length() == 1) {
            switch (selectedItem[0]) {
            case '1': {
                int version;
                std::cout << "Введите номер версии: ";
                if (std::cin >> version) {
                    if (tree2->selectVersion(version)) {
                        std::cout << "Версия " << version << " установлена.\n";
                    }
                    else {
                        std::cout << "Не удалось найти версию.\n";
                    }
                }
                else {
                    std::cout << "Ошибка ввода. Ожидается целое число.\n";
                }
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
                std::cout << "Введите ключ узла: ";
                if (std::cin >> key) {
                    tree->insert(key);
                }
                else {
                    std::cout << "Ошибка ввода. Ожидается целое число.\n";
                }
                break;
            }
            case '5': {
                int key;
                std::cout << "Введите ключ узла: ";
                if (std::cin >> key) {
                    tree->remove(key);
                }
                else {
                    std::cout << "Ошибка ввода. Ожидается целое число.\n";
                }
                break;
            }
            case '0': {
                isRunning = false;
                break;
            }
            default: {
                std::cout << "Введен неправильный пункт меню.\n";
                break;
            }
            }
        }
        else {
            std::cout << "Ошибка: необходимо ввести одну цифру.\n";
        }

        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << '\n';
        system("Pause");
        system("cls");
    }
	return 0;
}