#include <iostream>
#include <windows.h>
using namespace std;

// оголошення структури
/*struct Person {
	char name[15];
	char surname[25];
	int age;
	char adr[50];
	double balance;
	// 15 + 25 + 4(+1) + 50 + 8 = 98
	// розмір має бути кратний 8 (double) = 98
	// кожне поле вирівнюється по адресі, кратній своєму типу
};*/
struct Fraction {
	int numerator;
	int denominator;
};

void FractionInput(Fraction& f) {
	cout << "Введіть чисельник: ";
	cin >> f.numerator;
	cout << "Введіть знаменник: ";
	cin >> f.denominator;

	while (f.denominator == 0) {
		cout << "Знаменник не може бути 0! Введіть знаменник ще раз: ";
		cin >> f.denominator;
	}
}
void FractionOutput(Fraction f) {
	cout << f.numerator << "/" << f.denominator << endl;
}
void FractionReduce(Fraction& f) {
	int min;
	int num = f.numerator;
	int den = f.denominator;

	if (num < 0) num = -num;
	if (den < 0) den = -den;

	min = num < den ? num : den;

	for (int i = min; i > 1; i--) {
		if (f.numerator % i == 0 && f.denominator % i == 0) {
			f.numerator = f.numerator / i;
			f.denominator = f.denominator / i;
			break;
		}
	}

	if (f.denominator < 0) {
		f.denominator = -f.denominator;
		f.numerator = -f.numerator;
	}
}
Fraction Add(Fraction a, Fraction b) {
	Fraction result;
	result.numerator = a.numerator * b.denominator + b.numerator * a.denominator;
	result.denominator = a.denominator * b.denominator;
	FractionReduce(result);
	return result;
}
Fraction Subtract(Fraction a, Fraction b) {
	Fraction result;
	result.numerator = a.numerator * b.denominator - b.numerator * a.denominator;
	result.denominator = a.denominator * b.denominator;
	FractionReduce(result);
	return result;
}
Fraction Multiply(Fraction a, Fraction b) {
	Fraction result;
	result.numerator = a.numerator * b.numerator;
	result.denominator = a.denominator * b.denominator;
	FractionReduce(result);
	return result;
}
Fraction Divide(Fraction a, Fraction b) {
	Fraction result;
	result.numerator = a.numerator * b.denominator;
	result.denominator = a.denominator * b.numerator;
	FractionReduce(result);
	return result;
}


struct Car {
	char brand[20];
	char model[20];
	int year;
	char color[20];
	float engineVolume;
	int power;
	double price;
};

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	/*
	// оголошення екземпляра структури
	Person person;  // Person - складений тип даних

	cout << sizeof(person) << endl;
	
	cout << "Enter your name: ";
	cin >> person.name;
	cout << "Enter your surname: ";
	cin >> person.surname;

	Person* ptr = &person;
	cout << "Enter your age: ";
	cin >> (*ptr).age; // розіменовуємо покажчик та використовуємо оператор вибору

	cout << "Your name is \"" << person.name << "\" and your surname is \"" << person.surname << "\"" << endl;
	cout << "You are " << ptr->age << " years old." << endl; // використовуємо оператор вибору ->


	Person persons[5]; // масив структур
	cout << sizeof(persons) << endl;

	for (int i = 0; i < 5; i++) {
		persons[i].balance = i *100 + 10000.5;
		cout << persons[i].balance << endl;
	}
	*/


	Fraction f1, f2, result;

	cout << "Впишіть значення першого дробу." << endl;
	FractionInput(f1);
	cout << "Впишіть значення другого дробу." << endl;
	FractionInput(f2);

	cout << "Сума дробів: ";
	result = Add(f1, f2);
	FractionOutput(result);

	cout << "Різниця дробів: ";
	result = Subtract(f1, f2);
	FractionOutput(result);

	cout << "Добуток дробів: ";
	result = Multiply(f1, f2);
	FractionOutput(result);

	cout << "Частка дробів: ";
	result = Divide(f1, f2);
	FractionOutput(result);

	cout << "==------------------------------==" << endl;
	Car car;
	cin.get();

	cout << "Введіть марку: ";
	cin.getline(car.brand, 20);

	cout << "Введіть модель: ";
	cin.getline(car.model, 20);

	cout << "Введіть рік випуску: ";
	cin >> car.year;
	cin.get();

	cout << "Введіть колір: ";
	cin.getline(car.color, 20);

	cout << "Введіть об'єм двигуна: ";
	cin >> car.engineVolume;
	cin.get();

	cout << "Введіть потужність: ";
	cin >> car.power;
	cin.get();

	cout << "Введіть ціну: ";
	cin >> car.price;
	cin.get();

	cout << "==--- Короткий опис авто ---==" << endl;
	cout << "Марка: " << car.brand << endl;
	cout << "Модель: " << car.model << endl;
	cout << "Рік: " << car.year << endl;
	cout << "Колір: " << car.color << endl;
	cout << "Об'єм: " << car.engineVolume << endl;
	cout << "Потужність: " << car.power << endl;
	cout << "Ціна: " << car.price << endl;

	return 0;
}