#include <iostream>
#include <windows.h>
using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "Обчислення швидкості бігу:" << endl;
    cout << "Введіть дистанцію в метрах: ";
    double distance;
    cin >> distance;
    double time_input;
    cout << "Введіть час хв.сек: ";
    cin >> time_input;
    cout << "--------------------" << endl;

    int minutes = (int)time_input;
    int seconds = (int)((time_input - minutes) * 100 + 0.5);
    int total_secs = minutes * 60 + seconds;
    double speed = (distance / 1000) / (total_secs / 3600.0);

    cout << "Дистанція " << distance << " м." << endl;
    cout << "Час: " << minutes << " хв. " << seconds << " сек. = " << total_secs << " сек." << endl;
    cout << "Ви бігли зі швидкістю " << speed << " км/год.";


    return 0;
}