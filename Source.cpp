#include "Tree.h"
#include "VersionControlledTree.h"
#include "FullSaveTree.h"

#include <iostream>
#include <string>
#include <Windows.h>
#include <chrono>
#include <random>
#include <vector>
#include <filesystem>

int main() {
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	VersionControlledTree* tree = new VersionControlledTree("AVLversions.txt");
    //FullSaveTree* tree = new FullSaveTree("FullVersions.txt");

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
                VersionControlledTree* tree1 = new VersionControlledTree("compAVLversions.txt");
                FullSaveTree* tree2 = new FullSaveTree("compFullVersions.txt");

                int valueCount = 1000;
                long versionControlledTime = 0, fullSaveTime = 0;
                std::vector<int> keys;
                srand(time(NULL));

                for (int i = 0; i < valueCount; i++) {
                    int key = rand();
                    keys.push_back(key);

                    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
                    tree1->insert(key);
                    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                    auto result = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                    versionControlledTime += result.count();

                    start = std::chrono::steady_clock::now();
                    tree2->insert(key);
                    end = std::chrono::steady_clock::now();
                    result = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                    fullSaveTime += result.count();
                }
                std::cout << "Время вставки " << valueCount << " рандомных ключей:\n";
                std::cout << "\tVersionControlledTree = " << versionControlledTime << " micsec\n";
                std::cout << "\tFullSaveTree = " << fullSaveTime << " micsec\n";
                std::cout << "Размер файлов: \n"
                    << "\tVersionControlledTree = " << std::filesystem::file_size("compAVLversions.txt") / 1024 << " КБ\n"
                    << "\tFullSaveTree = " << std::filesystem::file_size("compFullVersions.txt") / 1024 << " КБ\n\n";

                versionControlledTime = 0, fullSaveTime = 0;
                for (int i = 0; i < valueCount; i++) {
                    int currIndex = rand() % (valueCount - i);
                    int currKey = keys[currIndex];
                    keys.erase(std::next(keys.begin(), currIndex));

                    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
                    tree1->remove(currKey);
                    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                    auto result = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                    versionControlledTime += result.count();

                    start = std::chrono::steady_clock::now();
                    tree2->remove(currKey);
                    end = std::chrono::steady_clock::now();
                    result = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                    fullSaveTime += result.count();
                }
                std::cout << "Время удаления " << valueCount << " существующих ключей в рандомном порядке:\n";
                std::cout << "\tVersionControlledTree = " << versionControlledTime << " micsec\n";
                std::cout << "\tFullSaveTree = " << fullSaveTime << " micsec\n";
                std::cout << "Размер файлов: \n"
                    << "\tVersionControlledTree = " << std::filesystem::file_size("compAVLversions.txt") / 1024 << " КБ\n"
                    << "\tFullSaveTree = " << std::filesystem::file_size("compFullVersions.txt") / 1024 << " КБ\n\n";

                tree1->selectVersion(valueCount + 1);
                tree2->selectVersion(valueCount + 1);

                versionControlledTime = 0, fullSaveTime = 0;
                std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
                tree1->clear();
                std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                auto result = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                versionControlledTime += result.count();

                start = std::chrono::steady_clock::now();
                tree2->clear();
                end = std::chrono::steady_clock::now();
                result = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                fullSaveTime += result.count();

                std::cout << "Время удаления всего дерева (" << valueCount  << " узлов):\n";
                std::cout << "\tVersionControlledTree = " << versionControlledTime << " micsec\n";
                std::cout << "\tFullSaveTree = " << fullSaveTime << " micsec\n";
                std::cout << "Размер файлов: \n"
                    << "\tVersionControlledTree = " << std::filesystem::file_size("compAVLversions.txt") / 1024 << " КБ\n"
                    << "\tFullSaveTree = " << std::filesystem::file_size("compFullVersions.txt") / 1024 << " КБ\n\n";


                versionControlledTime = 0, fullSaveTime = 0;
                for (int i = 1; i <= valueCount; i++) {
                    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
                    tree1->selectVersion(i);
                    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                    auto result = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                    versionControlledTime += result.count();

                    start = std::chrono::steady_clock::now();
                    tree2->selectVersion(i);
                    end = std::chrono::steady_clock::now();
                    result = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                    fullSaveTime += result.count();
                }
                std::cout << "Среднее время выбора версии:\n";
                std::cout << "\tVersionControlledTree = " << versionControlledTime/valueCount << " micsec\n";
                std::cout << "\tFullSaveTree = " << fullSaveTime/valueCount << " micsec\n";
                std::cout << "Размер файлов: \n"
                    << "\tVersionControlledTree = " << std::filesystem::file_size("compAVLversions.txt") / 1024 << " КБ\n"
                    << "\tFullSaveTree = " << std::filesystem::file_size("compFullVersions.txt") / 1024 << " КБ\n\n";


                std::remove("compAVLversions.txt");
                std::remove("compFullVersions.txt");
                delete tree1;
                delete tree2;
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