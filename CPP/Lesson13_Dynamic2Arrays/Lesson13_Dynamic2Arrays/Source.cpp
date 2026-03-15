#include <iostream>
#include <windows.h>
#include "Dynamic2DArrays.h"
using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	srand(time(NULL));

	int** p = nullptr;  // вказівник на вказівник
	// майбутній двовимірний динамічний масив

	int rows, cols;

	cout << "Введіть кількість рядків: ";
	cin >> rows;
	cout << "Введіть кількість стовпців: ";
	cin >> cols;

	// виділення пам'яті під масив

	p = Allocate(rows, cols);

	Init(p, rows, cols);
	Print(p, rows, cols);

	cout << "Сума додатних елементів = " << SumPositive(p, rows, cols) << endl;
	cout << "Сума елементів головної діагоналі = " << SumMainDiag(p, rows, cols) << endl;

	int elem;
	cout << "Введіть елемент для пошуку в масиві: ";
	cin >> elem;

	if (SearchForElement(p, rows, cols, elem)) cout << "Елемент знайдено" << endl;
	else cout << "Елемент не знайдено" << endl;
	

	// додати колонку в кінець масиву

	// проміжний масив для вставки даних в нову колонку таблиці

	int* mas = Allocate(rows);
	Init(mas, rows);
	cout << "Масив для вставки:" << endl;
	Print(mas, rows);

	cout << "Новий масив:" << endl;
	AddColEnd(p, rows, cols, mas);
	Print(p, rows, cols);

	delete[] mas;
	mas = nullptr;

	// Видалення першого рядка в таблиці (0 рядок в масиві)
	cout << "Масив після видалення рядка:" << endl;
	RemoveStringStart(p, rows);
	Print(p, rows, cols);


	// Додавання рядка в кінець таблиці
	mas = Allocate(cols);
	Init(mas, cols);
	cout << "Масив для вставки:" << endl;
	Print(mas, cols);

	cout << "Масив після додавання рядка в кінець:" << endl;
	AddRowEnd(p, rows, cols, mas);
	Print(p, rows, cols);
	delete[] mas;
	mas = nullptr;

	cout << "---------------------------------" << endl;
	cout << "---------------------------------" << endl;


	int index;
	cout << "Введіть індекс для вставки рядка: ";
	cin >> index;
	
	mas = Allocate(cols);
	Init(mas, cols);
	cout << "Рядок для вставки в масив: " << endl;
	Print(mas, cols);

	InsertRowAt(p, rows, cols, index, mas);
	cout << "Масив після вставки рядка: " << endl;
	Print(p, rows, cols);
	delete[] mas;
	mas = nullptr;

	cout << "---------------------------------" << endl;
	cout << "---------------------------------" << endl;


	cout << "Введіть індекс рядка для видалення: ";
	cin >> index;
	RemoveRowAt(p, rows, index);
	cout << "Масив після видалення рядка:" << endl;
	Print(p, rows, cols);

	cout << "---------------------------------" << endl;
	cout << "---------------------------------" << endl;


	cout << "Введіть індекс для вставки стовпця: ";
	cin >> index;

	mas = Allocate(rows);
	Init(mas, rows);
	cout << "Стовпець для вставки: " << endl;
	Print(mas, rows);
	
	InsertColAt(p, rows, cols, index, mas);
	cout << "Масив після вставки стовпця:" << endl;
	Print(p, rows, cols);

	delete[] mas;
	mas = nullptr;

	cout << "---------------------------------" << endl;
	cout << "---------------------------------" << endl;


	cout << "Введіть індекс стовпця для видалення: ";
	cin >> index;

	RemoveColAt(p, rows, cols, index);
	cout << "Масив після видалення стовпця:" << endl;
	Print(p, rows, cols);

	Free(p, rows);
	p = nullptr;
	return 0;
}