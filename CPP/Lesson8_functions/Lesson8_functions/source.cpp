#include <iostream>
#include <windows.h>
using namespace std;
// підключення функцій
#include "array1functions.h"

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	// при подачі масиву у функцію передається його адреса

	srand(static_cast<unsigned int>(time(0)));

	const int SIZE = 10;
	int arr[SIZE] = { 0 };      // оголошення масиву

	cout << &arr << endl;  // & оператор взяття адреси

	// виклик функцій

	Init(arr, SIZE);
	Print(arr, SIZE);
	
	// Написати функцію, що визначає кількість додатних,
	// від'ємних і нульових елементів переданого їй масиву.

	int count_pos = 0, count_neg = 0, count_zero = 0;

	Counter_Pos_Neg_Zero(arr, SIZE, &count_pos, &count_neg, &count_zero);

	cout << "Positive: " << count_pos << endl;
	cout << "Negative: " << count_neg << endl;
	cout << "Zero: " << count_zero << endl;


	int count_even = 0, count_odd = 0, count_mult5 = 0;

	Counter_Even_Odd_Mult5(arr, SIZE, &count_even, &count_odd, &count_mult5);

	cout << "Even: " << count_even << endl;
	cout << "Odd: " << count_odd << endl;
	cout << "Multiple 5: " << count_mult5 << endl;

	//////////////////////////////////////////////////////////

	/*
	cout << arr << endl;  // arr - особливий покажчик
	int* ptr = nullptr;  // нульовий пакажчик - ссилається на завідомо корректну пам'ять  // 8Бт
	ptr = arr;  // в покажчик записуємо адресу масиву (адреса його нульового елемента)
	// або ptr = &arr[0];
	for (int i = 0; i < SIZE; i++)
	{
		// покрокоаве заповнення даними елементів масиву
		*ptr = i * 2;
		ptr++; // збільшення на 1 адресу
		// покрокове виведення значень елементів масиву
		cout << arr[i] << "   " << *(arr + i) << endl;
	}
	*/

	Insert_Sort(arr, SIZE);
	Print(arr, SIZE);

	cout << "------------------------------------------------------------------------------" << endl;

	const int ROW = 5;
	const int COL = 5;
	int arr2[ROW][COL] = { 0 };

	//Init(&arr2[0][0], ROW * COL);
	//Print(arr2, ROW, COL);
	
	// ДЗ

	InitMatrix(arr2, ROW, COL);
	PrintMatrix(arr2, ROW, COL);

	cout << "Сума = " << SumMatrix(arr2, ROW, COL) << endl;

	int min, max;
	MainDiagMinMax(arr2, ROW, COL, &min, &max);
	cout << "Мінімальне в головній діагоналі: " << min << endl;
	cout << "Максимальне в головній діагоналі: " << max << endl;

	SortRows(arr2, ROW, COL);
	PrintMatrix(arr2, ROW, COL);


	//////////////////////////////

	int num1 = 10;
	int num2 = 15;
	int* ptr_num = &num1;  // покажчик містить адресу, має розмір 8Бт
	*ptr_num = 20;  // розіменування покажчика
	ptr_num = &num2;
	*ptr_num = 30;
	cout << "num1 = " << num1 << endl;
	cout << "num2 = " << num2 << endl;
	//Swap(&num1, &num2);
	//cout << "num1 = " << num1 << endl;
	//cout << "num2 = " << num2 << endl;
	// ПОСИЛАННЯ - псевдонім для змінних
	int& new_num1 = num1;
	int& new_num2 = num2;
	new_num1 = 50;
	new_num2 = 100;
	cout << "num1 = " << num1 << endl;
	cout << "num2 = " << num2 << endl;
	//Swap(num1, num2);
	cout << "num1 = " << num1 << endl;
	cout << "num2 = " << num2 << endl;
	return 0;
}

	return 0;
}