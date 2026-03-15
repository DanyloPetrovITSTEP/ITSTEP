#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    //////// Завдання 1: Частота слів ////////

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    ifstream inputFile("input.txt");
    ofstream outputFile("word_frequency.txt");

    if (!inputFile.is_open() || !outputFile.is_open())
    {
        cout << "Error opening file!" << endl;
        return 1;
    }

    const int MAX_WORDS = 1000; // максимально слів, можна збільшити
    string words[MAX_WORDS];
    int counts[MAX_WORDS] = { 0 };
    int totalWords = 0;

    string word;
    while (inputFile >> word)
    {
        bool found = false;
        for (int i = 0; i < totalWords; i++)
        {
            if (words[i] == word)
            {
                counts[i]++;
                found = true;
                break;
            }
        }

        if (!found)
        {
            if (totalWords >= MAX_WORDS)
            {
                cout << "Too many unique words!" << endl;
                break;
            }
            words[totalWords] = word;
            counts[totalWords] = 1;
            totalWords++;
        }
    }

    inputFile.close();

    for (int i = 0; i < totalWords; i++)
    {
        outputFile << words[i] << ": " << counts[i] << endl;
    }

    outputFile.close();

    cout << "Word frequency written to word_frequency.txt" << endl;


    //////// Завдання 2: Бінарний файл – збереження масиву чисел ////////

    int numbers[10] = { 0,1,2,3,4,5,6,7,8,9 };

    ofstream binFile("numbers.bin", ios::binary);
    if (!binFile.is_open())
    {
        cout << "Error creating numbers.bin!" << endl;
        return 1;
    }

    binFile.write((char*)numbers, sizeof(numbers));
    binFile.close();

    int reversed[10];

    ifstream readBin("numbers.bin", ios::binary);
    if (!readBin.is_open())
    {
        cout << "Error reading numbers.bin!" << endl;
        return 1;
    }

    for (int i = 9; i >= 0; i--)
    {
        readBin.read((char*)&reversed[i], sizeof(int));
    }
    readBin.close();

    cout << "Масив у зворотньому порядку: ";
    for (int i = 0; i < 10; i++)
        cout << reversed[i] << " ";
    cout << endl;


    //////// Завдання 3: Пошук максимального значення ////////

    ifstream readNumbers("numbers.bin", ios::binary);
    if (!readNumbers.is_open())
    {
        cout << "Error reading numbers.bin!" << endl;
        return 1;
    }

    int maxNum = numbers[0]; // або 0
    int temp;

    for (int i = 0; i < 10; i++)
    {
        readNumbers.read((char*)&temp, sizeof(int));
        if (temp > maxNum)
            maxNum = temp;
    }

    readNumbers.close();

    ofstream maxFile("max_number.bin", ios::binary);
    if (!maxFile.is_open())
    {
        cout << "Error creating max_number.bin!" << endl;
        return 1;
    }

    maxFile.write((char*)&maxNum, sizeof(int));
    maxFile.close();

    cout << "Максимальне число: " << maxNum << " записано у max_number.bin" << endl;

    return 0;
}