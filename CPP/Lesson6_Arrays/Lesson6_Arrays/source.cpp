#include <iostream>
#include <windows.h>
#include <iomanip>
using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	// Масив (ARRAY) - це набір однотипних змінних під 1 ім'ям
	// Суму елементів, що знаходяться між першим і останнім від'ємними 	елементами.
	// Добуток елементів, що знаходяться між min і max елементами

	srand(time(NULL));  // вплив на рандомізацію, виходячи з подачі поточного часу
	const int SIZE = 20;  // розмір масиву в елементах
	int a[SIZE] = { 0 };  // оголошення масиву (виділення пам'яті на 80Бт)
	// ініціалізація нулями

	for (int i = 0; i < SIZE; i++)
	{
		a[i] = rand() % 101 - 50;  // rand() % (max - min + 1) + min
		// -50..50
	}

	cout << endl;

	for (int i = 0; i < SIZE; i++)
		cout << "a[" << i + 1 << "] = " << a[i] << endl;


	cout << endl;

	int suma = 0;
	short index_f_neg = -1, index_l_neg = -1;

	for (int i = 0; i < SIZE; i++)
	{
		if (a[i] < 0)
		{
			index_f_neg = i;
			break;
		}
	}
	for (int i = 0; i < SIZE; i++)
	{
		if (a[i] < 0)
			index_l_neg = i;

	}
	if (index_f_neg == -1 && index_l_neg == -1)
	{
		cout << "відсутні негативні елементи у масиві" << endl;
	}
	else if (index_f_neg == index_l_neg)
	{
		cout << "один негативний елемент у масиві" << endl;
	}
	else if ((index_l_neg - index_f_neg) == 1)
	{
		cout << "суму знайти неможливо, адже між першим і останнім від'ємними елементами нічого немає" << endl;
	}
	else
	{

		for (int i = index_f_neg + 1; i < index_l_neg; i++)
		{
			suma += a[i];

		}

		cout << "сума елементів, що знаходяться між першим і останнім від'ємними елементами = "
			<< suma << endl;

	}

	long long product = 1;

	int max_element = a[0], min_element = a[0], min_index = 0, max_index = 0;

	for (int i = 1; i < SIZE; i++)
	{
		if (a[i] > max_element)
		{
			max_element = a[i];
			max_index = i;
		}
		if (a[i] < min_element)
		{
			min_element = a[i];
			min_index = i;
		}
	}
	int temp;
	if (max_index < min_index)   // нормалізація даних
	{
		temp = max_index;
		max_index = min_index;
		min_index = temp;
	}

	if (max_index - min_index == 1)
	{
		cout << "добуток знайти неможливо, адже між макс та мін елементами нічого немає" << endl;
	}
	else
	{
		for (int i = min_index + 1; i < max_index; i++)
		{
			product *= a[i];

		}

		cout << "добуток елементів, що знаходяться між макс і мін елементами = "
			<< product << endl;
	}




	return 0;
}