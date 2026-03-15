#include <iostream>
#include <windows.h>
#include <fstream>
using namespace std;

struct person
{
	string name;
	string password;
	bool registered : 1;   // "... : 1" дозволяє використовувати змінній типу bool замість 1 байту - 1 біт. (4 bool - 1 байт (корисні 4 його біти)
	bool authed : 1;
};

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	/*ofstream file("example.txt");
	if (!file.is_open())
	{
		cout << "Error!" << endl;
		return;
	}

	file << "Hello World!";
	file << "Binary world is beautiful!";
	file.close();
	

	ifstream file("example.txt");
	if (!file.is_open())
	{
		cout << "Error!" << endl;
		return;
	}

	string Example;
	file >> Example;
	file.close();
	cout << Example;


	fstream file("example.txt", ios::in | ios::out | ios::app);
	if (!file.is_open())
	{
		cout << "Error!" << endl;
		return;
	}

	file << "Hello Wolrd!";
	file.seekp(0, ios::beg);

	string str;
	while (file >> str)
	{
		cout << str << ' ';
	}

	// або

	char Example[255];
	file.getline(Example, sizeof(Example));
	cout << Example;
	*/


	//////////       ПРАКТИКА       \\\\\\\\\\

	// Завдання 1: Даний текстовий файл. 
	// Необхідно створити новий файл, 
	// в який переписати з вихідного файлу всі слова, 
	// що складаються не менше ніж із семи букв.


	/*ifstream inputFile("example.txt");
	ofstream outputFile("wordsOfSeven.txt");

	if (!inputFile.is_open() || !outputFile.is_open())
	{
		cout << "Error!" << endl;
		return;
	}

	string word;

	while (inputFile >> word)
	{
		if (word.length() >= 7) outputFile << word << ' ';
	}
	inputFile.close();
	outputFile.close();
	*/

	// Завдання 2: Дан текстовый файл. 
	// Необходимо переписать его строки во второй файл. 
	// Порядок строк во втором файле должен быть обратным...
	// по отношению к порядку строк в заданном файле.

	/*ifstream inputFile("example.txt");
	ofstream outputFile("reverse.txt");

	if (!inputFile.is_open() || !outputFile.is_open())
	{
		cout << "Error!" << endl;
		return;
	}

	char line[255];
	int count = 0;

	while (inputFile.getline(line, sizeof(line)))
	{
		count++;
	}

	inputFile.close();

	for (int i = count; i > 0; i--)
	{
		ifstream file("example.txt");

		for (int j = 0; j < i; j++)
		{
			file.getline(line, sizeof(line));
		}

		outputFile << line << endl;

		file.close();
	}

	outputFile.close();*/

	
	// Завдання 3: Дан текстовый файл. 
	// Добавить в него строку из двенадцати черточек (------------), 
	// поместив ее после последней из строк, в которых нет пробела. 
	// Если таких строк нет, то новая строка должна быть добавлена...
	// после всех строк имеющегося файла. 
	// Результат записать в другой файл.

	/*ifstream inputFile("example.txt");

	if (!inputFile.is_open())
	{
		cout << "Error!" << endl;
		return;
	}

	char line[255];
	int count = 0;
	int lastNoSpace = -1;

	while (inputFile.getline(line, sizeof(line)))
	{
		count++;

		bool hasSpace = false;

		for (int i = 0; line[i] != '\0'; i++)
		{
			if (line[i] == ' ')
			{
				hasSpace = true;
				break;
			}
		}

		if (!hasSpace)
		{
			lastNoSpace = count;
		}
	}

	inputFile.close();

	ifstream file("example.txt");
	ofstream outputFile("result.txt");

	int currentLine = 0;

	while (file.getline(line, sizeof(line)))
	{
		currentLine++;

		outputFile << line << endl;

		if (currentLine == lastNoSpace)
		{
			outputFile << "------------" << endl;
		}
	}

	file.close();
	outputFile.close();*/
	

	// Робота з бінарними файлами

	ofstream file("test.bin", ios::binary | ios::in);
	
	if (file.is_open())
	{
		cout << "Error!" << endl;
		return;
	}

	person Person;

	Person.name = "Alex";
	Person.password = "12321";
	Person.registered = true;
	Person.authed = false;

	file.write((char*)&Person, sizeof(Person));*/

	
	ifstream file("test.bin", ios::binary);

	if (file.is_open())
	{
		cout << "Error!" << endl;
		return;
	}

	person Person;

	file.read((char*)&Person, sizeof(Person));

	file.close();
	cout << Person.name << endl;
	cout << Person.password << endl;
	cout << Person.registered << endl;
	cout << Person.authed << endl;
	


	return 0;
}