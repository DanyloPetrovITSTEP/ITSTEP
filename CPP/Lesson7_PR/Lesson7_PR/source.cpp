#include <iostream>
#include <windows.h>
using namespace std;

int SumBetween(int number1, int number2)
{
	if (number1 > number2)
	{
		int temp = number1;
		number1 = number2;
		number2 = temp;
	}
	if (number1 == number2)
	{
		cout << "Початкове і кінцеве числа однакові. Суму чисел між ними порахувати неможливо!" << endl;
		return 0;
	}
	else if (number2 - number1 == 1)
	{
		cout << "Між числами є тільки одне число, суму порахувати неможливо!" << endl;
		return 0;
	}
	else
	{
		int sum = 0;
		for (int i = number1 + 1; i < number2; i++)
		{
			sum += i;
		}
		return sum;
	}
}


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	// Написати функцію, яка отримує як параметри 2 цілих числа і повертає суму чисел з діапазону між ними.





	return 0;
}