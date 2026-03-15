#include <iostream>

#include <windows.h>

#include <iomanip>

using namespace std;

int main()

{

	SetConsoleCP(1251);

	SetConsoleOutputCP(1251);

	cout << "Міні-калькулятор" << endl;

	double num1, num2;

	cout << "Введи два числа через пробіл:" << endl;

	cin >> num1 >> num2;

	char choice;

	cout << "обери + , - , * , /    :";

	cin >> choice;

	if (choice == '+') cout << "сума чисел = " << num1 + num2 << endl;

	else if (choice == '-') cout << "різниця чисел = " << num1 - num2 << endl;

	else if (choice == '*') cout << "добуток чисел = " << num1 * num2 << endl;

	else if (choice == '/')

	{

		if (num2 != 0) 		cout << "частка чисел = " << fixed << setprecision(9) << num1 / num2 << endl;

		else cout << "не можна" << endl;

	}

	else cout << "error" << endl;


	// множинний вибір swicth

	// інколи можна замінити if-else оператором swicth (коли аналізуємо 1 змінну на рівність)

	switch (choice)  // switch перемикач (змінна)
	{
	case '+':   // choice == '+'
		cout << "сума чисел = " << num1 + num2 << endl;
		break;  // вихід із конструкції множинного вибору
	case '-':
		cout << "різниця чисел = " << num1 - num2 << endl;
		break;
	case '*':
		cout << "добуток чисел = " << num1 * num2 << endl;
		break;
	case '/':
		if (num2 != 0)
		{
			cout << "частка чисел = " << fixed << setprecision(9) << num1 / num2 << endl;
		}
		else
		{
			cout << "не можна" << endl;
		}
		break;
	default:
		cout << "error" << endl;
	}

	// Практика, користувач вводить місяць, а програма видає пору року.

	short month;
	cout << "Введіть порядковий номер місяця: ";
	cin >> month;

	switch (month) {
		case 12:
		case 1:
		case 2:
			cout << "Зима";
			break;
		case 3:
		case 4:
		case 5:
			cout << "Весна";
			break;
		case 6:
		case 7:
		case 8:
			cout << "Літо";
			break;
		case 9:
		case 10:
		case 11:
			cout << "Осінь";
			break;
		default:
			cout << "Помилка, такого номеру місяца не буває, їх 12 якщо не Ви не знали ;)";
	}

	// тернарний оператор  (умова) ? дія(умова істинна) : дія(умова хибна);

	int a, b;

	cout << "введи два цілих числа:" << endl;

	cin >> a;
	cin >> b;

	// max?

	int max;

	(a > b) ? max = a : max = b;

	cout << "Максимальне число: " << max << endl;

	// вкладенний тернарний вираз
	(a == b) ? cout << "рівні" : (a > b) ? cout << a : cout << b;


	return 0;

}
