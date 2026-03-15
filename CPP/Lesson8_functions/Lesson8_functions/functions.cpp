#include <iostream>
#include <iomanip>
using namespace std;
// описи функцій

template <typename T>
void Swap(T* first, T* second)
{
	T temp;
	temp = *first;
	*first = *second;
	*second = temp;
}

void Init(int *a, int size)
{
	for (int i = 0; i < size; i++)
	{
		*a = rand() % 100 - 50;
		a++;
	}
}
void Print(int array[], int size)
{
	for (int i = 0; i < size; i++)
		cout << array[i] << "   ";
	cout << endl;
}
void Print(int array[][5], int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << setw(5) << array[i][j];
		}
		cout << endl;
	}
}
int Sum(int array[], int size)
{
	int sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum += array[i];
	}
	return sum;
}
double Average(int array[], int size)
{
	if (size == 0)
	{
		return 0;
	}
	int sum = Sum(array, size);
	return static_cast<double>(sum) / size;
}
int EvenSum(int array[], int size)
{
	int sum = 0;
	for (int i = 0; i < size; i++)
	{
		if (array[i] % 2 == 0)
		{
			sum += array[i];
		}
	}
	return sum;
}
void BubbleSort(int array[], int size)
{
	int counter = 0;
	short flag = 1;
	for (int i = 0; i < size; i++)
	{
		flag = 1;
		for (int j = 0; j < (size-1-i); j++)
		{
			if (array[j] > array[j + 1])
			{
				int temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
				flag = 0;
			}
		}
		if (flag == 1)
		{
			break;
		}
	}
}
int ArrayIndex(int array[], int size, int number)
{
	for (int i = 0; i < size; i++)
	{
		if (array[i] == number)
		{
			return i;
		}
	}
	return -1;
}
int ArrayMax(int array[], int size)
{
	int max = array[0];
	for (int i = 0; i < size; i++)
	{
		if (array[i] > max)
		{
			max = array[i];
		}
	}
	return max;
}
int ArrayMin(int array[], int size)
{
	int min = array[0];
	for (int i = 0; i < size; i++)
	{
		if (array[i] < min)
		{
			min = array[i];
		}
	}
	return min;
}
void ArrayReverse(int array[], int size)
{
	for (int i = 0; i < size/2; i++)
	{
		int temp = array[i];
		array[i] = array[size-1-i];
		array[size-1-i] = temp;
	}
}
bool isPrime(int number)
{
	if (number < 2)
	{
		return false;
	}
	for (int i = 2; i < number; i++)
	{
		if (number % i == 0)
		{
			return false;
		}
	}
	return true;
}
int ArrayNumOfPrime(int array[], int size)
{
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (isPrime(array[i]))
		{
			count++;
		}
	}
	return count;
}
void Counter_Pos_Neg_Zero(int array[], int size, int* pos, int* neg, int* zero)
{
	for (int i = 0; i < size; i++)
	{
		if (array[i] > 0)
		{
			*pos = *pos + 1;
		}
		else if (array[i] < 0)
		{
			*neg = *neg + 1;
		}
		else
		{
			*zero = *zero + 1;
		}
	}
}
void Counter_Even_Odd_Mult5(int array[], int size, int* even, int* odd, int* mult5)
{
	for (int i = 0; i < size; i++)
	{
		if (array[i] % 2 == 0)
		{
			*even = *even + 1;
		}
		else
		{
			*odd = *odd + 1;
		}
		if (array[i] % 5 == 0)
		{
			*mult5 = *mult5 + 1;
		}
	}
}
void SortArr(int array[], int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - 1 - i; j++)
		{
			if (array[j] > array[j + 1])
			{
				Swap(&array[j], &array[j+1]);
			}
		}
	}
}
void SortArray_byChoice(int array[], int size, int choice)
{
	int temp;
	if (choice == 1)
	{
		for (int i = 0; i < size - 1; i++)
		{
			for (int j = i + 1; j < size; j++)
			{
				if (array[i] > array[j])
				{
					temp = array[i];
					array[i] = array[j];
					array[j] = temp;
				}
			}
		}
	}
	else if (choice == 2)
	{
		for (int i = 0; i < size - 1; i++)
		{
			for (int j = i + 1; j < size; j++)
			{
				if (array[i] < array[j])
				{
					temp = array[i];
					array[i] = array[j];
					array[j] = temp;
				}
			}
		}
	}
}
void SortArray_HalfdownHalfhigh(int array[], int size)
{
	int temp;
	for (int i = 0; i < size / 2; i++)
	{
		int max_index = i;
		for (int j = i + 1; j < size / 2; j++)
		{
			if (array[j] > array[max_index])
			{
				max_index = j;
			}
		}
		temp = array[i];
		array[i] = array[max_index];
		array[max_index] = temp;
	}
	for (int i = size / 2; i < size - 1; i++) {
		int min_index = i;
		for (int j = i + 1; j < size; j++) {
			if (array[j] < array[min_index]) {
				min_index = j;
			}
		}
		temp = array[i];
		array[i] = array[min_index];
		array[min_index] = temp;
	}
}
void SortArray_BetweenNegElem(int array[], int size)
{
	int first = -1;
	int last = -1;
	int temp;
	for (int i = 0; i < size; i++)
	{
		if (array[i] < 0)
		{
			first = i;
			break;
		}
	}
	for (int i = size - 1; i >= 0; i--)
	{
		if (array[i] < 0) {
			last = i;
			break;
		}
	}
	if (first == -1 || last == -1 || last - first <= 1) return;
	for (int i = first + 1; i < last; i++) {
		int min_index = i;

		for (int j = i + 1; j < last; j++) {
			if (array[j] < array[min_index]) {
				min_index = j;
			}
		}
		temp = array[i];
		array[i] = array[min_index];
		array[min_index] = temp;
	}
}
void Insert_Sort(int array[], int size) // метод вставки
{
	for (int i = 1; i < size; i++)
	{
		int key = array[i];
		int j = i - 1;
		while (j >= 0 && array[j] > key)
		{
			array[j + 1] = array[j];
			j--;
		}
		array[j + 1] = key;
	}
}
void InitMatrix(int array[][5], int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			array[i][j] = rand() % 100 - 50;
		}
	}
}
void PrintMatrix(int array[][5], int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << setw(5) << array[i][j];
		}
		cout << endl;
	}
}
int SumMatrix(int array[][5], int rows, int cols)
{
	int sum = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			sum += array[i][j];
		}
	}
	return sum;
}
void MainDiagMinMax(int array[][5], int rows, int cols, int* min, int* max)
{
	*min = array[0][0];
	*max = array[0][0];
	int number;
	if (rows < cols)
		number = rows;
	else
		number = cols;

	for (int i = 1; i < number; i++)
	{
		if (array[i][i] < *min) *min = array[i][i];
		if (array[i][i] > *max) *max = array[i][i];
	}
}
void SortRows(int array[][5], int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		Insert_Sort(array[i], cols);
	}
}