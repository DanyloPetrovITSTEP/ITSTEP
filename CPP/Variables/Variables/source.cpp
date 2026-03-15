#include <iostream>
#include <windows.h>
using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "Привіт, введи два цілих числа:" << endl;

    int number1, number2;

    cout << "Введи перше число: ";
    cin >> number1;   // команда вводу потоку даних в змінну
    cout << "Введи друге число: ";
    cin >> number2;

    cout << "Сума чисел = " << number1 + number2 << endl;
    cout << "Різниця чисел = " << number1 - number2 << endl;
    cout << "Добуток чисел = " << number1 * number2 << endl;
    cout << "Частка чисел = " << double(number1) / number2 << endl;
    // значення виразу набуває більшого типу
    // ! можна під час виразу змінювати тип даних через функції

    return 0;
}
