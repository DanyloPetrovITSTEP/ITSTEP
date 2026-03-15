#include <iostream>
#include <windows.h>
#include "dynamicArray.h"
using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	srand(static_cast<unsigned int>(time(0)));

	// Динамічна пам'ять

	int* ptr = new int(5); // виділення динамічної пам'яті та ініціалізація 5

	cout << *ptr << endl;

	*ptr = *ptr * 5;

	cout << *ptr << endl;

	delete ptr; // вивільнення динам.пам'яті за адресою в ptr
	
	ptr = nullptr;

	// Дінамічний масив

	int* p = nullptr;

	int size = 0;

	cout << "Введіть розмір масиву: ";
	cin >> size;

	p = Allocate(size);

	Init(p, size);
	Print(p, size);


	int sum_odd = 0;

	SumOdd(p, size, &sum_odd);
	cout << "Сума непарних чисел дорівнює: " << sum_odd << endl;

	cout << "Кількість елементів, більших за середнє арифметичне в масиві: " << CountAboveAverage(p, size) << endl;
	SwapMinMax(p, size);
	Print(p, size);


	// Додавання number в кінець динамічного масиву

	int number = 0;
	cout << "Enter number: ";
	cin >> number;

	p = AppEnd(p, &size, number);
	Print(p, size);

	// Додавання number в місце в масиві, вказане користувачем (індекс)
	
	int index = 0;
	cout << "Enter index: ";
	cin >> index;

	InsertByIndex(p, size, number, index);
	Print(p, size);
	

	p = DeleteLastElement(p, size);
	Print(p, size);

	cout << "Введіть індекс для видалення: ";
	cin >> index;
	DeleteByIndex(p, size, index);
	Print(p, size);

	int size2 = 0;
	cout << "Введіть розмір другого масиву: ";
	cin >> size2;
	int* arr2 = Allocate(size2);

	Init(arr2, size2);
	cout << "Другий масив: ";
	Print(arr2, size2);
	cout << "Введіть індекс: ";
	cin >> index;
	InsertArray(p, size, arr2, size2, index);
	cout << "Масив, після додавання в нього другого масиву: ";
	Print(p, size);

	// вивільнення пам'яті під масив
	Free(p);
	Free(arr2);
	p = nullptr;
	return 0;
}