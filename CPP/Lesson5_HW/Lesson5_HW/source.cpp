#include <iostream>
#include <windows.h>
using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	// Завдання 1
	
	cout << " ---- Програма для визначення максимального та мінімального по прибутку місяця в введеному діапазоні ---- ";
	const int SIZE = 12;
	double profit[SIZE];
	cout << "Введіть прибуток компанії за 12 місяців: " << endl;
	for (int i = 0; i < SIZE; i++)
	{
		cout << i + 1 << "-й місяць: ";
		cin >> profit[i];
	}

	short first, last;
	cout << "Введіть початковий місяць діапазону: ";
	cin >> first;
	cout << "Введіть кінечний місяць діапазону: ";
	cin >> last;
	if (first < 1 || last > 12 || first > last)
	{
		cout << "Помилка! Ви ввели некоректний діапазон! Спробуйте ще раз:" << endl;
		while (true)
		{
			cout << "Введіть початковий місяць діапазону: ";
			cin >> first;
			cout << "Введіть кінечний місяць діапазону: ";
			cin >> last;
			if (!(first < 1 || last > 12 || first > last)) break;
			else cout << "Ви знову ввели некоректний діапазон, сробуйте ще раз:" << endl;
		}
	}

	short maxMonth = first - 1;
	short minMonth = first - 1;
	for (int i = first - 1; i < last; i++)
	{
		if (profit[i] > profit[maxMonth]) maxMonth = i;
		if (profit[i] < profit[minMonth]) minMonth = i;
	}

	cout << "Максимальний прибуток був у " << maxMonth + 1 << " місяці. Прибуток цього місяця: " << profit[maxMonth] << endl;
	cout << "Мінімальний прибуток був у " << minMonth + 1 << " місяці. Прибуток цього місяця: " << profit[minMonth] << endl;
	

	// Завдання 2

	int N;
	cout << "Введіть розмір для масиву: ";
	cin >> N;

	int arrive[1000];         // Я не зрозумів як зробити щоб тут було число яке введе користувач.
	if (N > 1000)
	{
		cout << "Занадто великий масив, спобуйте ще раз:" << endl;
		while (true)
		{
			cout << "Введіть розмір для масиву (Програма може прийняти число до 1000): ";
			cin >> N;
			if (N < 1000) break;
			else cout << "Помилка! Спробуйте знову:" << endl;
		}
	}

	cout << "Введіть " << N << " дійсних чисел:" << endl;
	cout << "Введіть перше число: ";
	cin >> arrive[0];
	for (int i = 1; i < N; i++)
	{
		cout << "Введіть наступне число: ";
		cin >> arrive[i];
	}

	short choice;
	cout << "Оберіть дію з цим масивом:" << endl;
	cout << "1 - Сума від'ємних елементів" << endl << "2 - Добуток елементів між мінімальним і максимальним" << endl << "3 - Добуток елементів з парними індексами" << endl << "4 - Сума між першим і останнім від’ємними" << endl;
	cout << "Введіть ваш вибір: ";
	cin >> choice;

	if (choice == 1)
	{
		int sum = 0;
		for (int i = 0; i < N; i++)
		{
			if (arrive[i] < 0) sum += arrive[i];
		}
		cout << "Сума від'ємних чисел в масиві: " << sum;
	}
	else if (choice == 2)
	{
		int Min = 0;
		int Max = 0;
		for (int i = 0; i < N; i++)
		{
			if (arrive[i] < arrive[Min]) Min = i;
			if (arrive[i] > arrive[Max]) Max = i;
		}
		double product = 1;
		if (Min == Max) product = 0;
		else
		{
			for (int i = Min + 1; i < Max; i++)
			{
				product *= arrive[i];
			}
		}
		cout << "Добуток елементів між мінімальним і максимальним: " << product;
	}
	else if (choice == 3)
	{
		double product = 1;
		for (int i = 0; i < N; i += 2)
		{
			product *= arrive[i];
		}
		cout << "Добуток елементів з парними індексами: " << product;
	}
	else if (choice == 4)
	{
		int first = -1;
		int last = -1;
		for (int i = 0; i < N; i++)
		{
			if (arrive[i] < 0)
			{
				if (first == -1) first = i;
				last = i;
			}
		}

		double sum = 0;
		if (first == -1 || first == last) sum = 0;
		else
		{
			for (int i = first + 1; i < last; i++)
			{
				sum += arrive[i];
			}
		}
		cout << "Сума між першим і останнім від'ємними: " << sum;
	}
	else cout << "Помилка! Введена цифра не в межах вибору."; // Чому воно видає помилку expected a statement??? Я ж написав else в ряду з всіма else if і початковий if

	return 0;
}