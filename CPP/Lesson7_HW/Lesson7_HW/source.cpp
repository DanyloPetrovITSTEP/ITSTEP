#include <iostream>
#include <windows.h>
using namespace std;

const int arrSize = 3;
void Array(int arr[][arrSize], int firstNum)
{
	int number = firstNum;

	for (int i = 0; i < arrSize; i++) {
		for (int j = 0; j < arrSize; j++) {
			arr[i][j] = number;
			number *= 2;
		}
	}
}

int isPerfect(int number)
{
	int sum = 0;

	for (int i = 1; i <= number / 2; i++)
	{
		if (number % i == 0) sum += i;
	}

	if (sum == number) return 1;
	else return 0;
}

void Card(int number)
{
	int rank = (number - 1) % 9;
	int mark = (number - 1) / 9;

	switch (rank)
	{
	case 0: cout << 6;  break;
	case 1: cout << 7;  break;
	case 2: cout << 8;  break;
	case 3: cout << 9;  break;
	case 4: cout << 10; break;
	case 5: cout << 'J'; break;
	case 6: cout << 'Q'; break;
	case 7: cout << 'K'; break;
	case 8: cout << 'A'; break;
	}

	switch (mark)
	{
	case 0: cout << " трефа"; break;
	case 1: cout << " бубна"; break;
	case 2: cout << " серце"; break;
	case 3: cout << " піка"; break;
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	// Завдання 1

	int arr[arrSize][arrSize] = { 0 };
	int number;

	cout << "Введіть число, яке буде записано в масив: ";
	cin >> number;

	Array(arr, number);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << arr[i][j] << "\t";
		}
		cout << endl;
	}

	
	// Завдання 2

	int number1, number2;

	cout << "Введіть початкове і граничне числа через пробіл: ";
	cin >> number1 >> number2;
	if (number1 > number2)
	{
		int temp = number2;
		number2 = number1;
		number1 = temp;
	}

	for (int i = number1; i <= number2; i++)
	{
		if (isPerfect(i) == 1)
		{
			cout << i << " ";
		}
	}

	// Завдання 3

	int number;

	cout << "Введіть номер гральної карти: ";
	cin >> number;
	
	if (number < 1 || number > 36) {
		cout << "Помилка! Введено невірне число!" << endl;
		return 0;
	}
	Card(number);	


	return 0;
}