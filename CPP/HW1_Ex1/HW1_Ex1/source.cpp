#include <iostream>
#include <windows.h>
using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int input_seconds;
	
	cout << "Введи число в секундах, яке потрібно перевести: ";
	cin >> input_seconds;

	int hours = input_seconds / 3600;
	int remainder = input_seconds - hours * 3600;
	int minutes = remainder / 60;
	int seconds = remainder - minutes * 60;
	
	cout << "З введених секунд отримано: " << hours << " годин " << minutes << " хвилин " << seconds << " секунд." << endl;

	return 0;
}
