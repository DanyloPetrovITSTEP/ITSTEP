#include <iostream>;
#include <windows.h>;
using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	// Завдання 1

	int number;

	cout << "Введіть число від якого буде знайдено куб: ";
	cin >> number;
	int cube = number;
	for (int i = 1; i <= 2; i++)
	{
		cube *= number;
	}
	cout << cube;


	// Завдання 2

	int number;
	int arithMean = 0;
	short count = 0;

	cout << "Зараз програмі потрібно буде, щоб Ви ввели числа для розрахунку середнього арифметичного." << endl;

	do
	{
		cout << "Введіть будь яке число (0 для виходу): ";
		cin >> number;
		if (number != 0)
		{
			count++;
			arithMean += number;
		}
	} while (number != 0);
	if (count > 0)
		cout << "Середнє арифметичне введених чисел дорівнює: " << double(arithMean) / count << endl;
	else
		cout << "Ви не ввели жодного числа!" << endl;

	return 0;

	// Завдання 3

	int number1, number2;
	
	cout << "Введіть перше число: ";
	cin >> number1;
	cout << "Введіть друге число: ";
	cin >> number2;
	cout << "Числа, на які обидва числа діляться без залишку:" << endl;

	int minNumber;
	if (number1 < number2)
		minNumber = number1;
	else
		minNumber = number2;
	
	for (int i = 1; i <= minNumber; i++)
	{
		if (number1 % i == 0 && number2 % i == 0)
			cout << i << endl;
	}
}