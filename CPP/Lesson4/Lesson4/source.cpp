#include <iostream>
#include <windows.h>
#include <iomanip> // б≥бл≥отека ман≥пул€ц≥й вводу/виводу
using namespace std;


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	// 100   50$,  за кожне 3-тЇ сп≥зненн€ -20$
	double  income;
	int code_lines;
	short lateness;

	cout << "¬и обрали вар≥ант: \"¬изначити ск≥льки грошей отримаЇ ¬ас€ та чи отримаЇ взагал≥.\"" << endl;
	cout << "¬вед≥ть ск≥льки р€дк≥в коду написав ¬ас€: ";
	cin >> code_lines;
	cout << "¬вед≥ть ск≥льки раз≥в зап≥знивс€ ¬ас€: ";
	cin >> lateness;
	income = (double(code_lines) / 100 * 50) - (lateness / 3 * 20);
	if (income <= 0) {
		cout << "¬ас€ не отримаЇ грошей, бо багато зап≥знювавс€.";
	}
	else {
		cout << "¬ас€ отримаЇ " << fixed << setprecision(2) << income << " долар≥в.";
	}

	return 0;
}