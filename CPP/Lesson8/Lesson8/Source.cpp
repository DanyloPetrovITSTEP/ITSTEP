#include <iostream>
#include <windows.h>
using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int a = 10;  // змінна а
	cout << a << endl;  // значення змінної
	cout << &a << endl; // взяття адреси
	cout << sizeof(a) << endl; // розмір змінної в Бт
	// Pointer(ptr) (покажчик, вказівник) - це змінна для збереження адреси іншої змінної
	int* b = &a;
	cout << b << endl;  // адреса змінної a

	return 0;
}