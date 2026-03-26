#include "LibFunc.h"
using namespace std;


int main()
{
    Book library[MAX_BOOKS];
    int bookCount = 0;
    int choice = -1;

    while (choice != 0)
    {
        cout << endl;
        cout << "Library options:" << endl
        << "1. Add book" << endl
        << "2. Delete book" << endl
        << "3. Find book" << endl
        << "4. Show all books" << endl
        << "5. Sort books" << endl
        << "6. Save to file" << endl
        << "7. Load from file" << endl
        << "0. Exit" << endl;
        cout << "Choose option by entering number: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addBook(library, bookCount);
            break;
        case 2:
            removeBook(library, bookCount);
            break;
        case 3:
            findBook(library, bookCount);
            break;
        case 4:
            showBooks(library, bookCount);
            break;
        case 5:
            sortBooks(library, bookCount);
            break;
        case 6:
            saveToFile(library, bookCount);
            break;
        case 7:
            loadFromFile(library, bookCount);
            break;
        case 0:
            cout << "Program closed." << endl;
            break;
        default:
            cout << "Error! Wrong number!" << endl;
        }
    }

    return 0;
}
