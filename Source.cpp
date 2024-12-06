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
        std::cout << "1. ������� ������.\n";
        std::cout << "2. ������� ������.\n";
        std::cout << "3. �������� ����.\n";
        std::cout << "4. ������� ����.\n";
        std::cout << "5. �������� ������.\n";
        std::cout << "6. �������� �������� ������ � ���������� ������� �����������.\n";
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
                std::cout << "������� ����� ������(�� 1 �� " << maxVersion << "):\n";
                if (std::cin >> version) {
                    if (tree->selectVersion(version)) {
                        std::cout << "������ " << version << " �����������.\n";
                    }
                    else {
                        std::cout << "�� ������� ����� ������.\n";
                    }
                }
                else {
                    std::cout << "������ �����. ��������� ����� �����.\n";
                }
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
                /*t->insert(1);
                t->insert(2);
                t->insert(3);
                t->insert(4);
                t->insert(5);
                t->order();

                int v;
                std::cout << "������� ����� ������: ";
                std::cin >> v;
                if (!t->selectVersion(v)) {
                    std::cout << "�� ������� ������� ������.\n";
                }

                t->order();*/
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