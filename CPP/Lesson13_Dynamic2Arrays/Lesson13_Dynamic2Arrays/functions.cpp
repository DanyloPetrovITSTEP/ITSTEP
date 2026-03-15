#include <iostream>
#include <windows.h>
#include <iomanip>
using namespace std;

int** Allocate(int rows, int cols) {
	int** p = new int*[rows]; // виділення пам'яті під масив вказівників

	for (int i = 0; i < rows; i++) {
		p[i] = new int[cols];
	}

	return p;
}
int* Allocate(int size) {
	return new int[size];
}

void Init(int** p, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			p[i][j] = rand() % 41 - 20;
		}
	}
}
void Init(int* p, int size) {
	for (int i = 0; i < size; i++) p[i] = rand() % 41 - 20;
}

void Print(int** p, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << setw(7) << p[i][j];
		}
		cout << endl;
	}
}
void Print(int* p, int size) {
	for (int i = 0; i < size; i++) cout << setw(7) << p[i];
	cout << endl;
}

void Free(int** p, int rows) {
	for (int i = 0; i < rows; i++) {
		delete[] p[i];
	}
	delete[] p;
}

int SumPositive(int** p, int rows, int cols) {
	int sum = 0;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (p[i][j] > 0)
				sum += p[i][j];
		}
	}
	return sum;
}

int SumMainDiag(int** p, int rows, int cols) {
	int sum = 0, size;
	size = (rows < cols) ? rows : cols;
	
	for (int i = 0; i < size; i++) {
		sum += p[i][i];
	}

	return sum;
}

bool SearchForElement(int** p, int rows, int cols, int element) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (p[i][j] == element) return true;
		}
	}
	return false;
}

// int**& p  -  посилання на вказівник на вказівник
void AddColEnd(int**& p, int rows, int& cols, int* mas) {
	cols++;

	// перерозподіл пам'яті
	int** p_new = Allocate(rows, cols);

	// перезапис даних із старого масиву в новий
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols-1; j++) {
			p_new[i][j] = p[i][j];
		}
		p_new[i][cols - 1] = mas[i]; // додавання колонки поелементно
	}
	
	Free(p, rows);
	p = p_new;
}

void RemoveStringStart(int**& p, int& rows) {
	rows--;

	int** p_new = new int* [rows];

	for (int i = 0; i < rows; i++) {
		p_new[i] = p[i + 1];
	}

	delete[] p[0];
	delete[] p;
	p = p_new;
}

void AddRowEnd(int**& p, int& rows, int cols, int* mas) {
	if (cols <= 0) {
		cout << "Помилка! Кількість колонок 0 або менша!" << endl;
		return;
	}
	if (mas == nullptr) {
		cout << "Помилка! Порожній масив для вставки!" << endl;
		return;
	}
	if (p == nullptr) {
		cout << "Помилка! Порожній головний масив!" << endl;
		return;
	}

	int** p_new = new int* [rows + 1];

	for (int i = 0; i < rows; i++) {
		p_new[i] = p[i];
	}

	int* new_row = new int[cols];
	for (int j = 0; j < cols; j++) {
		new_row[j] = mas[j];
	}
	p_new[rows] = new_row;

	delete[] p;
	p = p_new;
	rows++;
}

void InsertRowAt(int**& p, int& rows, int cols, int index, int* mas) {
	if (index < 0 || index > rows) return;
	int** p_new = new int* [rows + 1];

	for (int i = 0; i < index; i++) p_new[i] = p[i];

	p_new[index] = new int[cols];
	for (int j = 0; j < cols; j++) p_new[index][j] = mas[j];

	for (int i = index; i < rows; i++) p_new[i + 1] = p[i];

	delete[] p;
	p = p_new;
	rows++;
}

void RemoveRowAt(int**& p, int& rows, int index) {
	if (index < 0 || index >= rows) return;
	delete[] p[index];
	int** p_new = new int* [rows - 1];

	for (int i = 0; i < index; i++) p_new[i] = p[i];
	for (int i = index + 1; i < rows; i++) p_new[i - 1] = p[i];

	delete[] p;
	p = p_new;
	rows--;
}

void InsertColAt(int**& p, int rows, int& cols, int index, int* mas) {
	if (index < 0 || index > cols) return;
	int** p_new = Allocate(rows, cols + 1);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < index; j++) p_new[i][j] = p[i][j];

		p_new[i][index] = mas[i];

		for (int j = index; j < cols; j++) p_new[i][j + 1] = p[i][j];
	}
	
	Free(p, rows);
	p = p_new;
	cols++;
}

void RemoveColAt(int**& p, int rows, int& cols, int index) {
	if (index < 0 || index >= cols) return;
	int** p_new = Allocate(rows, cols - 1);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < index; j++) p_new[i][j] = p[i][j];

		for (int j = index + 1; j < cols; j++) p_new[i][j - 1] = p[i][j];
	}

	Free(p, rows);
	p = p_new;
	cols--;
}