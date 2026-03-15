#include <iostream>
#include <windows.h>
#include <iomanip>
using namespace std;

void Menu(char menu[][50], int row) {
	cout << "Students list: " << endl;

	for (int i = 0; i < row; i++)
		cout << menu[i] << endl;
}

char** AddStudents(char** old_list, int& old_count) {
	system("cls");

	int count;
	cout << "How many students you want to add? " << endl;
	cin >> count;
	cin.get();

	int new_count = old_count + count;  // нова кількість студентів

	char** new_list = new char* [new_count];

	for (int i = 0; i < old_count; i++) {
		new_list[i] = old_list[i];  // перезапис адрес рядків
	}

	// додавання нових студентів

	char str[100];  // буферний масив для вводу даних про студента

	for (int i = old_count; i < new_count; i++) {
		cout << i + 1 << " Enter information: " << endl;
		cin.getline(str, 100);

		int length = strlen(str) + 1;  // реальна довжина рядка

		new_list[i] = new char[length];

		strcpy_s(new_list[i], length, str);
	}

	old_count = new_count;
	delete[] old_list;
	
	return new_list;
}

void Print(char** list, int count) {
	system("cls");
	cout << "Students List: " << endl;

	for (int i = 0; i < count; i++) {
		cout << i + 1 << ". " << list[i] << endl;
	}
	cout << endl;

	system("pause"); // stop
}

char** DeleteStudent(char** list, int& size) {
	system("cls");

	if (size == 0 || list == nullptr) {
		cout << "List is empty, no students to delete." << endl;
		system("pause");
		return list;
	}

	int index;
	cout << "Enter student's number to delete: ";
	cin >> index;

	if (index < 1 || index > size) {
		cout << "Your number is out of size of the list!" << endl;
		system("pause");
		return list;
	}

	index--;
	delete[] list[index];

	for (int i = index; i < size - 1; i++) {
		list[i] = list[i + 1];
	}

	size--;
	if (size == 0) {
		delete[] list;
		system("pause");
		return nullptr;
	}

	char** new_list = new char* [size];
	for (int i = 0; i < size; i++) {
		new_list[i] = list[i];
	}
	delete[] list;

	cout << "Student deleted from the list." << endl;
	system("pause");
	return new_list;
}

void FindStudent(char** list, int size) {
	system("cls");

	if (size == 0 || list == nullptr) {
		cout << "List is empty, so program can not find student!" << endl;
		system("pause");
		return;
	}

	char name[100];
	cout << "Enter student name to find: ";
	cin.get();
	cin.getline(name, 100);

	bool found = false;

	for (int i = 0; i < size; i++) {
		if (strcmp(list[i], name) == 0) {
			cout << "Student is found at position: " << i + 1 << endl;
			found = true;
		}
	}
	if (!found) cout << "Student not found." << endl;

	system("pause");
}

void SortStudents(char** list, int size) {
	system("cls");

	if (size < 2) {
		cout << "Nothing to sort." << endl;
		system("pause");
		return;
	}

	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (strcmp(list[j], list[j + 1]) > 0) {
				char* temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
	}

	cout << "List sorted!" << endl;
	system("pause");
}

void EditStudent(char** list, int size) {
	system("cls");

	if (size == 0) {
		cout << "List is empty, no students to edit!" << endl;
		system("pause");
		return;
	}

	int index;
	cout << "Enter student number to edit: ";
	cin >> index;

	if (index < 1 || index > size) {
		cout << "Your number is out of size of the list!" << endl;
		system("pause");
		return;
	}
	index--;

	char new_name[100];
	cout << "Enter new student name: ";
	cin.get();
	cin.getline(new_name, 100);

	delete[] list[index];

	int length = strlen(new_name) + 1;
	list[index] = new char[length];

	strcpy_s(list[index], length, new_name);

	cout << "Student info updated!" << endl;
	system("pause");
}