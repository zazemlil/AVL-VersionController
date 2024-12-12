#include <iostream>
#include <string>
#include <Windows.h>
#include <chrono>
#include <random>
#include <vector>
#include <filesystem>
#include <fstream>

#include "Tree.h"
#include "VersionControlledTree.h"
#include "FullSaveTree.h"

std::fstream getFileStream(std::ios_base::openmode params)
{
    std::fstream file("test.xls", params);
    if (!file.is_open()) {
        file.open("test.xls", std::ios::out);
        file.close();
        file.open("test.xls", params);
    }
    return file;
}

int main() {
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	VersionControlledTree* tree = new VersionControlledTree("AVLversions.txt");
    //FullSaveTree* tree = new FullSaveTree("FullVersions.txt");

    bool isRunning = true;

    while (isRunning) {
        std::string selectedItem;
        std::cout << "1. ������� ���������� ������.\n"; // "1. ������� ������. \n";
        std::cout << "2. ������� ������� ������.\n";
        std::cout << "3. �������� ����.\n";
        std::cout << "4. ������� ����.\n";
        std::cout << "5. �������� ������.\n";
        //std::cout << "6. �������� �������� ������ � ���������� ������� �����������.\n";
        std::cout << "0. ����� �� ���������.\n";
        std::cout << "����: ";

        std::cin >> selectedItem;

        if (selectedItem.length() == 1) {
            switch (selectedItem[0]) {
            case '1': {
                int maxVersion = tree->getLastVersionNumber();
                if (maxVersion == 0) {
                    std::cout << "��� ����������� ������.\n";
                    break;
                }
                int version;
                Tree* selectedTree = new Tree();
                std::cout << "������� ����� ������(�� 1 �� " << maxVersion << "):\n";
                if (std::cin >> version) {
                    if (tree->selectVersion(version, selectedTree)) {
                        //std::cout << "������ " << version << " �����������.\n";
                        selectedTree->order();
                        selectedTree->clear();
                    }
                    else {
                        std::cout << "�� ������� ����� ������.\n";
                    }
                }
                else {
                    std::cout << "������ �����. ��������� ����� �����.\n";
                }
                delete selectedTree;
                break;
            }
            case '2': {
                if (!tree->order()) {
                    std::cout << "������ ������.\n";
                }
                break;
            }
            case '3': {
                int key;
                std::cout << "������� ���� ����: ";
                if (std::cin >> key) {
                    if (tree->insert(key)) {
                        std::cout << "���� " << key << " ������� ��������.\n";
                    }
                    else {
                        std::cout << "����� ���� ��� ����������.\n";
                    }
                }
                else {
                    std::cout << "������ �����. ��������� ����� �����.\n";
                }
                break;
            }
            case '4': {
                int key;
                std::cout << "������� ���� ����: ";
                if (std::cin >> key) {
                    if (tree->remove(key)) {
                        std::cout << "���� " << key << " ������� ������.\n";
                    }
                    else {
                        std::cout << "������ ����� �� ����������.\n";
                    }
                }
                else {
                    std::cout << "������ �����. ��������� ����� �����.\n";
                }
                break;
            }
            case '5': {
                tree->clear();
                std::cout << "������ �������.\n";
                break;
            }
            case '6': {
                std::remove("compAVLversions.txt");
                std::remove("compFullVersions.txt");
                VersionControlledTree* tree1;
                FullSaveTree* tree2;

                long versionControlledTime = 0, fullSaveTime = 0;
                srand(time(NULL));

                std::fstream file = getFileStream(std::ios::out);
                file << "������� �������� ��� ���������� ������:" << '\n';
                file << "���-�� ������" << '\t' << "VersionControlledTree time, ms" << '\t' 
                                                << "FullSaveTree time, ms" << '\t' 
                                                << "VersionControlledTree mem, KB" << '\t' 
                                                << "FullSaveTree mem, KB" << '\n';

                int currKeysCount = 200, step = 10000;
                for (int i = 0; i < 10; i++) {
                    tree1 = new VersionControlledTree("compAVLversions.txt");
                    tree2 = new FullSaveTree("compFullVersions.txt");
                    for (int j = 0; j < currKeysCount-1; j++) {
                        int key = rand();

                        //std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
                        tree1->insert(key);
                        //std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                        //auto result = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                        //versionControlledTime += result.count();

                        /*start = std::chrono::steady_clock::now();
                        tree2->insert(key);
                        end = std::chrono::steady_clock::now();
                        result = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                        fullSaveTime += result.count();*/
                    }
                    
                    bool r = false;
                    while (!r) {
                        int key = rand();
                        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
                        r = tree1->insert(key);
                        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                        auto result = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                        versionControlledTime = result.count();
                    }
                    

                    std::cout << "������� ����� �������� ��� ���������� " << currKeysCount << " ������:\n"
                        << "\tVersionControlledTree = " << versionControlledTime / double(1000) << " msec\n"
                        << "\tFullSaveTree = " << fullSaveTime / double(1000) << " msec\n";
                    std::cout << "������ ������: \n"
                        << "\tVersionControlledTree = " << std::filesystem::file_size("compAVLversions.txt") / (double)1024 / currKeysCount << " ��\n"
                        << "\tFullSaveTree = " << std::filesystem::file_size("compFullVersions.txt") / (double)1024 / currKeysCount << " ��\n\n";

                    file << currKeysCount << '\t' << std::to_string(versionControlledTime) << '\t'
                        << std::to_string(fullSaveTime) << '\t'
                        << std::to_string(std::filesystem::file_size("compAVLversions.txt") / (double)1024) << '\t'
                        << std::to_string(std::filesystem::file_size("compFullVersions.txt") / (double)1024) << '\n';

                    currKeysCount += step;
                    versionControlledTime = 0, fullSaveTime = 0;
                    
                    std::remove("compAVLversions.txt");
                    std::remove("compFullVersions.txt");
                    delete tree1;
                    delete tree2;
                    tree1 = nullptr;
                    tree2 = nullptr;
                }
                file << '\n';

            //    file << "������� �������� ��� ��������:" << '\n';
            //    file << "���-�� ������" << '\t' << "VersionControlledTree time, ms" << '\t' 
            //                                    << "FullSaveTree time, ms" << '\t'
            //                                    << "VersionControlledTree mem, KB" << '\t' 
            //                                    << "FullSaveTree mem, KB" << '\n';

            //    currKeysCount = 200, step = 100;
            //    for (int i = 0; i < 9; i++) {
            //        tree1 = new VersionControlledTree("compAVLversions.txt");
            //        tree2 = new FullSaveTree("compFullVersions.txt");
            //        std::vector<int> keys;
            //        for (int k = 0; k < currKeysCount; k++) {
            //            int key = rand();
            //            tree1->insert(key);
            //            tree2->insert(key);
            //            keys.push_back(key);
            //        }
            //        for (int j = 0; j < currKeysCount; j++) {
            //            int currIndex = rand() % (currKeysCount - j);
            //            int currKey = keys[currIndex];
            //            keys.erase(std::next(keys.begin(), currIndex));

            //            std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
            //            tree1->remove(currKey);
            //            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            //            auto result = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            //            versionControlledTime += result.count();

            //            start = std::chrono::steady_clock::now();
            //            tree2->remove(currKey);
            //            end = std::chrono::steady_clock::now();
            //            result = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            //            fullSaveTime += result.count();
            //        }
            //        std::cout << "������� ����� �������� ��� �������� " << currKeysCount << " ������������ ������:\n"
            //            << "\tVersionControlledTree = " << versionControlledTime / double(1000) / currKeysCount << " msec\n" 
            //            << "\tFullSaveTree = " << fullSaveTime / double(1000) / currKeysCount << " msec\n";
            //        std::cout << "������ ������: \n"
            //            << "\tVersionControlledTree = " << std::filesystem::file_size("compAVLversions.txt") / (double)1024 / currKeysCount << " ��\n"
            //            << "\tFullSaveTree = " << std::filesystem::file_size("compFullVersions.txt") / (double)1024 / currKeysCount << " ��\n\n";


            //        /*file << currKeysCount << '\t' << std::to_string(versionControlledTime / double(1000) / currKeysCount) << '\t'
            //            << std::to_string(fullSaveTime / double(1000) / currKeysCount) << '\t' 
            //            << std::to_string(std::filesystem::file_size("compAVLversions.txt") / (double)1024 / currKeysCount) << '\t'
            //            << std::to_string(std::filesystem::file_size("compFullVersions.txt") / (double)1024 / currKeysCount) << '\n';*/

            //        file << currKeysCount << '\t' << std::to_string(versionControlledTime / double(1000)) << '\t'
            //            << std::to_string(fullSaveTime / double(1000)) << '\t'
            //            << std::to_string(std::filesystem::file_size("compAVLversions.txt") / (double)1024) << '\t'
            //            << std::to_string(std::filesystem::file_size("compFullVersions.txt") / (double)1024) << '\n';

            //        currKeysCount += step;
            //        versionControlledTime = 0, fullSaveTime = 0;

            //        std::remove("compAVLversions.txt");
            //        std::remove("compFullVersions.txt");
            //        delete tree1;
            //        delete tree2;
            //        tree1 = nullptr;
            //        tree2 = nullptr;
            //        keys.clear();
            //        keys.shrink_to_fit();
            //    }

            //    file << '\n';

            //    file << "������� �������� ������ ���:" << '\n';
            //    file << "���-�� ������" << '\t' << "VersionControlledTree time, ms" << '\t' 
            //                                    << "FullSaveTree time, ms" << '\t'
            //                                    << "VersionControlledTree mem, KB" << '\t' 
            //                                    << "FullSaveTree mem, KB" << '\n';

            //    currKeysCount = 200, step = 100;
            //    for (int i = 0; i < 9; i++) {
            //        tree1 = new VersionControlledTree("compAVLversions.txt");
            //        tree2 = new FullSaveTree("compFullVersions.txt");
            //        std::vector<int> keys;
            //        for (int k = 0; k < currKeysCount; k++) {
            //            int key = rand();
            //            tree1->insert(key);
            //            tree2->insert(key);
            //            keys.push_back(key);
            //        }
            //        for (int j = 0; j < currKeysCount; j++) {
            //            int currIndex = rand() % (currKeysCount - j);
            //            int currKey = keys[currIndex];
            //            keys.erase(std::next(keys.begin(), currIndex));
            //            Tree* selectedTree = new Tree();

            //            std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
            //            tree1->selectVersion(currKey, selectedTree);
            //            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            //            auto result = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            //            versionControlledTime += result.count();
            //            delete selectedTree;
            //            selectedTree = nullptr;

            //            selectedTree = new Tree();
            //            start = std::chrono::steady_clock::now();
            //            tree2->selectVersion(currKey, selectedTree);
            //            end = std::chrono::steady_clock::now();
            //            result = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            //            fullSaveTime += result.count();
            //            delete selectedTree;
            //            selectedTree = nullptr;
            //        }
            //        std::cout << "������� ����� �������� ��� ������ " << currKeysCount << " ������������ ������(������):\n"
            //            << "\tVersionControlledTree = " << versionControlledTime / double(1000) / currKeysCount << " msec\n"
            //            << "\tFullSaveTree = " << fullSaveTime / double(1000) / currKeysCount << " msec\n";
            //        std::cout << "������ ������: \n"
            //            << "\tVersionControlledTree = " << std::filesystem::file_size("compAVLversions.txt") / (double)1024 / currKeysCount << " ��\n"
            //            << "\tFullSaveTree = " << std::filesystem::file_size("compFullVersions.txt") / (double)1024 / currKeysCount << " ��\n\n";

            //        /*file << currKeysCount << '\t' << std::to_string(versionControlledTime / double(1000) / currKeysCount) << '\t'
            //            << std::to_string(fullSaveTime / double(1000) / currKeysCount) << '\t' 
            //            << std::to_string(std::filesystem::file_size("compAVLversions.txt") / (double)1024 / currKeysCount) << '\t'
            //            << std::to_string(std::filesystem::file_size("compFullVersions.txt") / (double)1024 / currKeysCount) << '\n';*/

            //        file << currKeysCount << '\t' << std::to_string(versionControlledTime / double(1000)) << '\t'
            //            << std::to_string(fullSaveTime / double(1000)) << '\t'
            //            << std::to_string(std::filesystem::file_size("compAVLversions.txt") / (double)1024) << '\t'
            //            << std::to_string(std::filesystem::file_size("compFullVersions.txt") / (double)1024) << '\n';

            //        currKeysCount += step;
            //        versionControlledTime = 0, fullSaveTime = 0;

            //        std::remove("compAVLversions.txt");
            //        std::remove("compFullVersions.txt");
            //        delete tree1;
            //        delete tree2;
            //        tree1 = nullptr;
            //        tree2 = nullptr;
            //        keys.clear();
            //        keys.shrink_to_fit();
            //    }
            //    
                file.close();
                break;
            }
            case '0': {
                isRunning = false;
                break;
            }
            default: {
                std::cout << "������ ������ ���� �� ����������.\n";
                break;
            }
            }
        }
        else {
            std::cout << "������: ���������� ������ ���� �����.\n";
        }

        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << '\n';
        system("Pause");
        system("cls");
    }
	return 0;
}