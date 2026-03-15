#include <iostream>
#include <iomanip>
using namespace std;

// виділяє динамічну пам'ять під одновимірний масив
int* Allocate(int size)
{
	return new int[size];
}
void Free(int* pointer) // вивільняє пам'ять
{
	delete[] pointer;
}
void Init(int* pointer, int size)
{
	for (int i = 0; i < size; i++)
	{
		*pointer = rand() % 100;
		pointer++;
	}
}
void Print(int* pointer, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << *pointer << "  ";
		pointer++;
	}
	cout << endl;
}
int DynamicArrMaxInd(int* arr, int size)
{
	int maxIndex = 0;
	for (int i = 0; i < size; i++)
	{
		if (arr[i] > arr[maxIndex])
		{
			maxIndex = i;
		}
	}
	return maxIndex;
}
int DynamicArrMinInd(int* arr, int size)
{
	int minIndex = 0;
	for (int i = 0; i < size; i++)
	{
		if (arr[i] < arr[minIndex])
		{
			minIndex = i;
		}
	}
	return minIndex;
}
void SumOdd(int* pointer, int size, int* sum_odd)
{
	for (int i = 0; i < size; i++)
	{
		if (pointer[i] % 2 != 0)
		{
			*sum_odd = *sum_odd + pointer[i];
		}
	}
}
int* DeleteLastElement(int* pointer, int& size)
{
	if (size <= 0) return pointer;

	int new_size = size - 1;
	int* new_array = new int[new_size];

	for (int i = 0; i < new_size; i++)
	{
		new_array[i] = pointer[i];
	}
	size = new_size;
	delete[] pointer;
	return new_array;
}
int CountAboveAverage(int* arr, int size)
{
	double sum = 0;
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		sum += arr[i];
	}
	double average = sum / size;
	for (int i = 0; i < size; i++)
	{
		if (arr[i] > average)
		{
			count++;
		}
	}
	return count;
}
void SwapMinMax(int* arr, int size)
{
	int min = DynamicArrMinInd(arr, size);
	int max = DynamicArrMaxInd(arr, size);
	int temp = arr[min];
	arr[min] = arr[max];
	arr[max] = temp;
}
int* AppEnd(int* arr, int* size, int number)
{
	int* new_p = new int[*size + 1];

	*size = *size + 1;
	for (int i = 0; i < *size - 1; i++)
	{
		new_p[i] = arr[i];
	}
	new_p[*size - 1] = number;
	Free(arr);
	arr = new_p;
	return arr;
}
void InsertByIndex(int*& arr, int& size, int number, int index)
{
	if (index < 0 || index >= size)
	{
		cout << "error index" << endl;
		return;
	}
	size++;
	int* new_p = new int[size]; // Allocate(size);
	/*
	for (int i = 0; i < index; i++)
	{
		new_p[i] = arr[i];
	}
	new_p[index] = number;
	for (int i = index + 1; i < size; i++)
	{
		new_p[i] = arr[i - 1];
	}
	*/

	int k = 0; // зсув

	for (int i = 0; i < size; i++)
	{
		if (i == index)
		{
			k = 1;
			new_p[i] = number;
		}
		else new_p[i] = arr[i - k];
	}

	Free(arr);
	arr = new_p;
}
void InsertArray(int*& arr1, int& size1, int* arr2, int size2, int index) {
	if (index < 0 || index > size1) {
		cout << "Помилка в позиціюванні.";
		return;
	}
	int* newArr = new int[size1 + size2];

	for (int i = 0; i < index; i++) {
		newArr[i] = arr1[i];
	}
	for (int i = 0; i < size2; i++) {
		newArr[index + i] = arr2[i];
	}
	for (int i = index; i < size1; i++) {
		newArr[i + size2] = arr1[i];
	}

	delete[] arr1;
	arr1 = newArr;
	size1 += size2;
}
void DeleteByIndex(int*& arr, int& size, int index) {
	if (index < 0 || index >= size) {
		cout << "Помилка в позиціюванні.";
		return;
	}

	int* newArr = new int[size - 1];

	for (int i = 0, j = 0; i < size; i++) {
		if (i == index) continue;
		newArr[j++] = arr[i];
	}

	delete[] arr;
	arr = newArr;
	size--;
}