#include <iostream>
#include <windows.h>
#include "strFunctions.h"
using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	// Рядки string
	// Рядок - це масив символів, який завершується нуль-термінатором
	/*
	char arr[5] = {'H', 'e', 'l', 'l', 'o'}; // масив символів
	char str[6] = { 'H', 'e', 'l', 'l', 'o', '\0'}; // рядок

	// \0 - невидимий символ кінця рядка

	// cout << arr << endl;   // вивід масиву та інших кодів до \0

	cout << str << endl;
	// відбувається вивід потоку символів до \0

	char str1[] = "Hello World!"; // рядок
	cout << str1 << endl;

	char str2[25]; // порожній рядок = порожній масив символів
	cout << "Як тебе звати?: ";
	cin >> str2; // {'B', 'o', 'b', '\0', '\0', '\0' ...}
	cout << str2 << endl;

	// пробіл = кінець рядка!!!

	char str3[50];
	cout << "Запишіть своє ім'я та прізвище через пробіл: ";

	cin.get(); // ловить 1 символ ('\n' після попереднього cin)
	cin.getline(str3, 50); // ловить потік символів до ENTER
	cout << str3 << endl;
	*/

	char str1[100], str2[100];
	cout << "Введіть текст: " << endl;
	cin.getline(str1, 100);
	cout << str1 << endl;

	// довжина рядка

	int length = my_strlen(str1);
	cout << length << endl;

	/*
	// заміна пробілів на зірочки
	ReplaceSpacesWithStars(str1);
	cout << str1 << endl;
	*/
	// конкатенація
	cout << "Введіть другий текст: ";
	cin.getline(str2, 100);
	my_strcat(str1, str2);
	cout << str1 << endl;
	

	cout << "Кількість слів в тексті: " << CountWords(str1) << endl;

	CopyString(str2, str1);
	cout << "Скопійований рядок: " << str2 << endl;

	StringReverse(str2);
	cout << "Реверс скопійованого рядка: " << str2 << endl;

	return 0;
}