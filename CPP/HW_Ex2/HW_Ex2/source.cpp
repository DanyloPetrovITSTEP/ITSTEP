#include <iostream>
#include <windows.h>
using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    double money_input;
    cout << "¬вед≥ть дробове число €ку буде переведено в грошовий вар≥ант (через крапку, наприклад, 12.5): ";
    cin >> money_input;

    int hryvnias = (int)money_input;
    int kopeck = (int)((money_input - hryvnias) * 100 + 0.5);

    cout << hryvnias << " гривень " << kopeck << " коп≥йок." << endl;


    return 0;
}