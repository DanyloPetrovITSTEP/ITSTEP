#include <iostream>
#include <windows.h>
#include <iomanip>
using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	srand(time(NULL));

	// Завдання 1
	
	const int SIZE1 = 10;
	const int SIZE2 = 5;
	int main_arr[SIZE1] = { 0 };
	int arr1[SIZE2] = { 0 };
	int arr2[SIZE2] = { 0 };

	for (int i = 0; i < SIZE1; i++)
	{
		main_arr[i] = rand() % 101 - 25;  // rand() % (max - min + 1) + min
		// -25..75
	}

	for (int i = 0; i < SIZE1; i++)
	{
		cout << "main_arr[" << i << "] = " << main_arr[i] << endl;
	}

	short j = 0;
	for (int i = 0; i < SIZE1; i++)
	{
		if (i < 5)
		{
			arr1[i] = main_arr[i];
		}
		else
		{
			arr2[j] = main_arr[i];
			j++;
		}
	}

	for (int i = 0; i < SIZE2; i++)
	{
		cout << "arr1[" << i << "] = " << arr1[i] << endl;
	}
	for (int i = 0; i < SIZE2; i++)
	{
		cout << "arr2[" << i << "] = " << arr2[i] << endl;
	}
	
	//Завдання 2
	
	const int SIZE = 5;
	int arr1[SIZE] = { 0 };
	int arr2[SIZE] = { 0 };
	int suma_arr[SIZE] = { 0 };

	for (int i = 0; i < SIZE; i++)
	{
		arr1[i] = rand() % 101 - 25;  // rand() % (max - min + 1) + min
		// -25..75
	}
	for (int i = 0; i < SIZE; i++)
	{
		arr2[i] = rand() % 101 - 25;  // rand() % (max - min + 1) + min
		// -25..75
	}

	for (int i = 0; i < SIZE; i++)
	{
		suma_arr[i] = arr1[i] + arr2[i];
	}
	
	// Завдання 3
	
	const int SIZE1 = 3;
	const int SIZE2 = 5;
	int arr[SIZE1][SIZE2] = { 0 };

	for (int i = 0; i < SIZE1; i++)
	{
		for (int j = 0; j < SIZE2; j++)
		{
			arr[i][j] = rand() % 101 - 25;
		}
	}

	int suma = 0;
	short min = arr[0][0];
	short max = arr[0][0];

	for (int i = 0; i < SIZE1; i++)
	{
		for (int j = 0; j < SIZE2; j++)
		{
			suma += arr[i][j];

			if (arr[i][j] < min)
				min = arr[i][j];
			if (arr[i][j] > max)
				max = arr[i][j];
		}
	}

	double arithMean = double(suma) / (SIZE1 * SIZE2);

	cout << "Сума всіх елементів масиву: " << suma << endl;
	cout << "Мінімальний елемент масиву: " << min << endl;
	cout << "Максимальний елемент масиву: " << max << endl;
	cout << "Середнє арифметичне: " << arithMean;
	
	//Завдання 4
	
	const int rows = 3;
	const int cols = 4;
	int arr[rows][cols] = { 0 };

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			arr[i][j] = rand() % 51 - 50;
		}
	}

	int rowSum[rows] = { 0 };
	int colSum[cols] = { 0 };
	int totalSum = 0;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			rowSum[i] += arr[i][j];
			colSum[j] += arr[i][j];
			totalSum += arr[i][j];
		}
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << setw(4) << arr[i][j] << "  ";
		}
		cout << "| " << rowSum[i] << endl;
	}
	cout << "------------------------------" << endl;
	for (int i = 0; i < cols; i++)
	{
		cout << setw(4) << colSum[i] << "  ";
	}
	cout << "| " << totalSum << endl;


	return 0;
}