#include <iostream>;
#include <windows.h>;
using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	// цикл for

// for(змінна = початкове цілочисельне значення; умова межі циклу; крок)

	for (int i = 0; i < 10; i++)
	{ // тіло цикла
		cout << i << endl;
	}


	return 0;
}