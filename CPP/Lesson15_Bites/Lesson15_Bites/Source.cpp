#include <iostream>
#include <windows.h>
using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	/*
	// упаковка кольору
	unsigned int red, green, blue;

	cout << "Enter a red component 0 - 255: ";
	cin >> red;  // 31 00000000 00000000 00000000 00011111
	cout << "Enter a green component 0 - 255: ";
	cin >> green;  // 233 00000000 00000000 00000000 11101001
	cout << "Enter a blue component 0 - 255: ";
	cin >> blue;  // 242  00000000 00000000 00000000 11110010

	unsigned int color; // 00000000 00000000 00000000 00000000
						// 00000000 00011111 11101001 11110010

	red = red << 16; // зсув вліво   00000000 00011111 00000000 00000000
	green = green << 8; //           00000000 00000000 11101001 00000000
	                           //    00000000 00000000 00000000 11110010
	color = red | green | blue;  //  00000000 00011111 11101001 11110010

	cout << hex << color << endl;
	*/

	// розпаковка кольору RGB в 3 змінні
	unsigned int red, green, blue, color;

	cout << "Enter a color (for example 1fe9f2): " << endl;
	cin >> hex >> color; // 00000000 00011111 11101001 11110010

	red = color >> 16; // 00000000 00000000 00000000 00011111
	green = color >> 8; // 00000000 00000000 00011111 11101001
	// маска (FF = 11111111) - набір 0 та 1 для того, щоб позбутися зайвих бітів
	green = 0xFF & green;  // 00000000 00000000 00011111 11101001
						   // 00000000 00000000 00000000 11111111
						   // 00000000 00000000 00000000 11101001

	blue = 0xFF & color;

	cout << red << endl;
	cout << green << endl;
	cout << blue << endl;

	


	return 0;
}