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
        std::cout << "1. ������� ������.\n";
        std::cout << "2. �������� �������� ������ � ���������� ������� �����������.\n";
        std::cout << "3. ������� ������.\n";
        std::cout << "4. �������� ����.\n";
        std::cout << "5. ������� ����.\n";
        std::cout << "0. ����� �� ���������.\n";
        std::cout << "����: ";

        std::cin >> selectedItem;

        if (selectedItem.length() == 1) {
            switch (selectedItem[0]) {
            case '1': {
                int version;
                std::cout << "������� ����� ������: ";
                if (std::cin >> version) {
                    if (tree2->selectVersion(version)) {
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
                
                break;
            }
            case '3': {
                tree->order();
                break;
            }
            case '4': {
                int key;
                std::cout << "������� ���� ����: ";
                if (std::cin >> key) {
                    tree->insert(key);
                }
                else {
                    std::cout << "������ �����. ��������� ����� �����.\n";
                }
                break;
            }
            case '5': {
                int key;
                std::cout << "������� ���� ����: ";
                if (std::cin >> key) {
                    tree->remove(key);
                }
                else {
                    std::cout << "������ �����. ��������� ����� �����.\n";
                }
                break;
            }
            case '0': {
                isRunning = false;
                break;
            }
            default: {
                std::cout << "������ ������������ ����� ����.\n";
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