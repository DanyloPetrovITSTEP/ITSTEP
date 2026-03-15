#include <iostream>
#include <windows.h>
#include "2DDynamicStrings.h"
#include <conio.h>
using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));


	// динамічний двовимірний масив (список) рядків (студентів)

	char** students_list = nullptr;  // покажчик на список студентів

	// меню побудоване на кодах клавіш

	char menu[7][50] = {
	"1. Add ",
	"2. Delete ",
	"3. Find ",
	"4. Print ",
	"5. Sort ",
	"6. Edit ",
	"7. Exit "
	};

	int count = 0; // кількість студентів

	while (true)
	{
		system("cls");
		// функція меню
		Menu(menu, 7);

		int user_choice = _getch();  // код клавіши (ціле число)

		switch (user_choice)
		{
		case '1':
			// фукнція додавання студента;
			students_list = AddStudents(students_list, count);
			break;
		case '2':
			// функція видалення студента;
			students_list = DeleteStudent(students_list, count);
			break;
		case '3':
			// функція пошуку студента;
			FindStudent(students_list, count);
			break;
		case '4':
			// функція виводу списку студентів на екран;
			Print(students_list, count);
			break;
		case '5':
			// функція сортування студентів;
			SortStudents(students_list, count);
			break;
		case '6':
			// функція редагування даних;
			EditStudent(students_list, count);
			break;
		case '7':
			// exit;
			for (int i = 0; i < count; i++) {
				delete[] students_list[i];
			}
			delete[] students_list;
			return 0;
			break;
		}
	}
}