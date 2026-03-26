#include "LibFunc.h"
using namespace std;

void addBook(Book library[], int& bookCount)
{
    if (bookCount >= MAX_BOOKS)
    {
        cout << "Library is full!" << endl;
        return;
    }

    cin.ignore();

    cout << "Enter title: ";
    cin.getline(library[bookCount].title, MAX_TITLE);
    cout << "Enter author: ";
    cin.getline(library[bookCount].author, MAX_TITLE);
    cout << "Enter year: ";
    cin >> library[bookCount].year;
    cout << endl;

    bookCount++;
    cout << "Book added!" << endl;
}

void removeBook(Book library[], int& bookCount)
{
    if (bookCount == 0)
    {
        cout << "Library is empty!" << endl;
        return;
    }

    int choice;
    cout << "Delete by:" << endl
    << "1. Index" << endl
    << "2. Title" << endl;
    cout << "Your choice: ";
    cin >> choice;

    if (choice == 1)
    {
        int index;
        cout << "Enter book index: ";
        cin >> index;

        if (index < 1 || index > bookCount)
        {
            cout << "Wrong index!" << endl;
            return;
        }

        index--;

        for (int i = index; i < bookCount - 1; i++)
        {
            library[i] = library[i + 1];
        }

        bookCount--;
        cout << endl;
        cout << "Book deleted!" << endl;
    }
    else if (choice == 2)
    {
        char title[MAX_TITLE];
        bool found = false;

        cin.ignore();
        cout << "Enter title: ";
        cin.getline(title, MAX_TITLE);

        for (int i = 0; i < bookCount; i++)
        {
            if (strcmp(library[i].title, title) == 0)
            {
                for (int j = i; j < bookCount - 1; j++)
                {
                    library[j] = library[j + 1];
                }

                bookCount--;
                found = true;
                cout << "Book deleted!" << endl;
                break;
            }
        }

        if (!found)
        {
            cout << "Book not found!" << endl;
        }
    }
    else
    {
        cout << "Wrong choice!" << endl;
    }
}

void findBook(Book library[], int bookCount)
{
    if (bookCount == 0)
    {
        cout << "Library is empty!" << endl;
        return;
    }

    int choice;
    bool found = false;

    cout << "Find by:" << endl;
    cout << "1. Title" << endl;
    cout << "2. Year" << endl;
    cout << "Your choice: ";
    cin >> choice;
    cout << endl;

    if (choice == 1)
    {
        char title[MAX_TITLE];
        cin.ignore();

        cout << "Enter title: ";
        cin.getline(title, MAX_TITLE);

        for (int i = 0; i < bookCount; i++)
        {
            if (strcmp(library[i].title, title) == 0)
            {
                cout << i + 1 << ". " << library[i].title << " - " << library[i].author << " - " << library[i].year << endl;
                found = true;
            }
        }
    }
    else if (choice == 2)
    {
        int year;
        cout << "Enter year: ";
        cin >> year;
        cout << endl;

        for (int i = 0; i < bookCount; i++)
        {
            if (library[i].year == year)
            {
                cout << i + 1 << ". " << library[i].title << " - " << library[i].author << " - " << library[i].year << endl;
                found = true;
            }
        }
    }
    else
    {
        cout << "Wrong choice!" << endl;
        return;
    }

    if (!found)
    {
        cout << "Nothing found!" << endl;
    }
}

void showBooks(Book library[], int bookCount)
{
    if (bookCount == 0)
    {
        cout << "Library is empty!" << endl;
        return;
    }

    for (int i = 0; i < bookCount; i++)
    {
        cout << i + 1 << ". " << library[i].title << " - " << library[i].author << " - " << library[i].year << endl;
    }
}

void sortBooks(Book library[], int bookCount)
{
    if (bookCount == 0)
    {
        cout << "Library is empty!" << endl;
        return;
    }

    int choice;
    cout << "Sort by:" << endl
        << "1. Title" << endl
        << "2. Year" << endl;
    cout << "Your choice: ";
    cin >> choice;

    for (int i = 0; i < bookCount - 1; i++)
    {
        for (int j = 0; j < bookCount - i - 1; j++)
        {
            bool needSwap = false;

            if (choice == 1)
            {
                if (strcmp(library[j].title, library[j + 1].title) > 0)
                {
                    needSwap = true;
                }
            }
            else if (choice == 2)
            {
                if (library[j].year > library[j + 1].year)
                {
                    needSwap = true;
                }
            }
            else
            {
                cout << "Wrong choice!" << endl;
                return;
            }

            if (needSwap)
            {
                Book temp = library[j];
                library[j] = library[j + 1];
                library[j + 1] = temp;
            }
        }
    }

    cout << "Books sorted!" << endl;
}

void saveToFile(Book library[], int bookCount)
{
    FILE* file = fopen("libList.dat", "wb");

    if (file == nullptr)
    {
        cout << "File open error!" << endl;
        return;
    }

    fwrite(&bookCount, sizeof(int), 1, file);
    fwrite(library, sizeof(Book), bookCount, file);

    fclose(file);

    cout << "Data saved!" << endl;
}

void loadFromFile(Book library[], int& bookCount)
{
    FILE* file = fopen("libList.dat", "rb");

    if (file == nullptr)
    {
        cout << "File not found!" << endl;
        return;
    }

    fread(&bookCount, sizeof(int), 1, file);

    if (bookCount > MAX_BOOKS)
    {
        cout << "Too many books in file!" << endl;
        fclose(file);
        bookCount = 0;
        return;
    }

    fread(library, sizeof(Book), bookCount, file);

    fclose(file);

    cout << "Data loaded!" << endl;
}
