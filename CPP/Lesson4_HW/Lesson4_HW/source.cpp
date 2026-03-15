#include <iostream>
#include <windows.h>
using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	// Завдання 1
	
	cout << "Зараз програма обчислить середнє арифметичне цілих чисел від 1 до 1000!";
	double arithMean = 0;
	for (int i = 1; i < 1001; i++)
	{
		arithMean += i;
	}
	arithMean = arithMean / 1000;
	cout << "Середнє арифметичне цілих чисел від 1 до 1000 дорівнює: " << arithMean << endl;
	

	// Завдання 2
	
	long long math_product = 1;
	int initialnum;

	cout << "Введіть ціле число, яке буде початковим для знаходження добутку чисел від числа до 20: ";
	cin >> initialnum;
	if (initialnum > 20)
	{
		for (int i = initialnum; i >= 20; i--)
		{
			math_product = math_product * i;
		}
		cout << "Добуток чисел від " << initialnum << " до 20 дорівнює: " << math_product << endl;
	}
	else if (initialnum == 20)
	{
		cout << "Ви ввели 20, як і число до якого програма перебирає числа, через це добуток дорівнює 20." << endl;
	}
	else
	{
		for (int i = initialnum; i <= 20; i++)
		{
			math_product = math_product * i;
		}
		cout << "Добуток чисел від " << initialnum << " до 20 дорівнює: " << math_product << endl;
	}
	

	// Завдання 3

	short number;

	cout << "Введіть цифру для якої програма виведе таблицю множення від 1 до 9: ";
	cin >> number;
	if (number < 1 || number > 9)
	{
		for (;;)
		{
			cout << "Введіть число від 1 до 9: ";
			cin >> number;
			if (number >= 1 && number <= 9)
			{
				break;
			}
			else
			{
				cout << "Число повинне бути від 1 до 9 щоб програма видала таблицю множення для цього числа." << endl;
			}
		}
	}
	for (int i = 1; i <= 9; i++)
	{
			cout << i << ") " << number << " * " << i << " дорівнює " << number * i << endl;
	}


	return 0;
}