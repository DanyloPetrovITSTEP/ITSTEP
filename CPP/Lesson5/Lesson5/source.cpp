#include <iostream>;
#include <windows.h>;
using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	// цикл while (цикл з передумовою)

	int number;
	cout << "введи число" << endl;
	cin >> number;

	while (number != 0)
	{
		cout << "введи число" << endl;
		cin >> number;
	}

	// while(true)  вічний цикл

	// цикл do while (цикл з післяумовою)

	int number;

	do  // виконує дії циклу хоса б  1 раз
	{
		cout << "введи число" << endl;
		cin >> number;
	} while (number != 0);



	// Масив (ARRAY) - це набір однотипних змінних під 1 ім'ям

	const int SIZE = 10;  // розмір масиву в елементах
	int a[SIZE] = { 0 };  // оголошення масиву (виділення пам'яті на 40Бт)
	// ініціалізація нулями

	for (int i = 0; i < SIZE; i++)
	{
		cout << "введи " << i + 1 << " число: " << endl;
		cin >> a[i];  // i - індекс елемента

	}

	cout << endl;

	for (int i = 0; i < SIZE; i++)
		cout << "a[" << i + 1 << "] = " << a[i] << endl;




	return 0;
}