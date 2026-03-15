#include <iostream>
#include <windows.h>
using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    // Завдання 1
    
    short grade1,grade2,grade3,grade4,grade5;
    
    cout << "Введи 5 оцінок студента через пробіл: " << endl;
    cin >> grade1 >> grade2 >> grade3 >> grade4 >> grade5;
    short afmean = (grade1 + grade2 + grade3 + grade4 + grade5) / 5;
    if (afmean >= 4)
    {
        cout << "Студент отримує доступ до іспиту.";
    }
    else
    {
        cout << "Студент не отримує доступ до іспиту.";
    }
    

    // Завдання 2

    int number;

    cout << "Введіть число: ";
    cin >> number;

    if (number % 2 == 0)
    {
        cout << number * 3 << endl;
    }
    else
    {
        cout << double(number) / 2 << endl;
    }

    return 0;
}