#include "Tree.h"
#include "VersionControlledTree.h"
#include "FullSaveTree.h"

#include <iostream>
#include <string>
#include <Windows.h>

int main() {
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	//VersionControlledTree* tree = new VersionControlledTree("AVLversions.txt");
    FullSaveTree* tree = new FullSaveTree("FullVersions.txt");

    bool isRunning = true;

    while (isRunning) {
        std::string selectedItem;
        std::cout << "1. Выбрать версию.\n";
        std::cout << "2. Вывести дерево.\n";
        std::cout << "3. Добавить узел.\n";
        std::cout << "4. Удалить узел.\n";
        std::cout << "5. Очистить дерево.\n";
        std::cout << "6. Сравнить контроль версий с алгоритмом полного копирования.\n";
        std::cout << "0. Выход из программы.\n";
        std::cout << "Ввод: ";

        std::cin >> selectedItem;

        if (selectedItem.length() == 1) {
            switch (selectedItem[0]) {
            case '1': {
                int maxVersion = tree->getLastVersionNumber();
                if (maxVersion == 0) {
                    std::cout << "Нет сохраненных версий.\n";
                    break;
                }
                int version;
                std::cout << "Введите номер версии(от 1 до " << maxVersion << "):\n";
                if (std::cin >> version) {
                    if (tree->selectVersion(version)) {
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
                if (!tree->order()) {
                    std::cout << "Дерево пустое.\n";
                }
                break;
            }
            case '3': {
                int key;
                std::cout << "Введите ключ узла: ";
                if (std::cin >> key) {
                    if (tree->insert(key)) {
                        std::cout << "Ключ " << key << " успешно добавлен.\n";
                    }
                    else {
                        std::cout << "Такой ключ уже существует.\n";
                    }
                }
                else {
                    std::cout << "Ошибка ввода. Ожидается целое число.\n";
                }
                break;
            }
            case '4': {
                int key;
                std::cout << "Введите ключ узла: ";
                if (std::cin >> key) {
                    if (tree->remove(key)) {
                        std::cout << "Ключ " << key << " успешно удален.\n";
                    }
                    else {
                        std::cout << "Такого ключа не существует.\n";
                    }
                }
                else {
                    std::cout << "Ошибка ввода. Ожидается целое число.\n";
                }
                break;
            }
            case '5': {
                tree->clear();
                std::cout << "Дерево удалено.\n";
                break;
            }
            case '6': {
                /*t->insert(1);
                t->insert(2);
                t->insert(3);
                t->insert(4);
                t->insert(5);
                t->order();

                int v;
                std::cout << "Введите номер версии: ";
                std::cin >> v;
                if (!t->selectVersion(v)) {
                    std::cout << "Не удалось выбрать версию.\n";
                }

                t->order();*/
                break;
            }
            case '0': {
                isRunning = false;
                break;
            }
            default: {
                std::cout << "Такого пункта меню не существует.\n";
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