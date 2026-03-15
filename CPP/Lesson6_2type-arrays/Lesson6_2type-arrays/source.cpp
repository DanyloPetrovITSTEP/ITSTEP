#include <iostream>
#include <windows.h>
#include <iomanip>
using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	// Масив (ARRAY) - це набір однотипних даних під 1 ім'ям
	// Двовимірні масиви = таблиці = матриці	
	srand(time(NULL));  // вплив на рандомізацію, виходячи з подачі поточного часу

	const int ROW = 3;  // кількість частин поділу
	const int COL = 3;  // кількість елементів в 1 частині

	int a[ROW][COL]; // 9елементів * 4Бт(int) = 36Бт
	//cout << sizeof(a);
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			a[i][j] = rand() % 101;  // rand() % (max - min + 1) + min



	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
			cout << setw(4) << a[i][j] << "   ";  // setw(позиції) вирівнює дані по кількості позицій на консолі

		cout << endl;
	}

	return 0;
}