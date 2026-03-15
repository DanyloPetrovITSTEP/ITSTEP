#include <iostream>
#include <windows.h>
#include <iomanip>
using namespace std;

// Написати функцію, яка приймає два параметри: 
// основу степеня та показник степеня і 
// обчислює ступінь числа на основі отриманих даних.

long long Power(int number, short stepin);   // прототип функції

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	srand(time(NULL));  // вплив на рандомізацію, виходячи з подачі поточного часу

	int number = rand() % 100 + 1;   // rand() % (max - min + 1) + min
	short n = rand() % 5 + 1;

	cout << number << " ^ " << n << " = " << Power(number, n) << endl;

	return 0;
}

long long Power(int number, short stepin)
{
	long long res = 1;
	for (int i = 1; i <= stepin; i++)
	{
		res *= number;
	}
	return res;
}