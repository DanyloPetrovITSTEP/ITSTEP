// Компіляція
	
// 1) препроцесор: готує текст для подальших етапів (#директиви, забирає зайве)
// 2) компілятор: перевіряє і перекладає на мову машинних кодів (*.obj)
// 3) лінкер: збирає все разом
// 4) запуск (*.exe)


#include <iostream>
#include <windows.h>
using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	// побітове представлення числової змінної

	unsigned int number;    // 00000000 00000000 00000000 00000000
	cout << "Enter your number: " << endl;
	cin >> number;

	unsigned int digit; // цифра числа
	unsigned int mask;

	// завдання: вивести число побітово без незначущих нулів
	bool start = false;
	if (number <= 0) {
		cout << 0;
	}
	else {
		for (int i = 31; i >= 0; i--) {
			mask = 1 << i;  // 00000000 00000000 00000100 00000000
			// 00000000 00000000 00000101 11011100
			// 00000000 00000000 00000100 00000000
			digit = number & mask; // 1 або 0
			if (digit != 0) {
				start = true;
			}
			if (start == true) {
				cout << (digit >> i);
			}
		}
	}




	return 0;
}