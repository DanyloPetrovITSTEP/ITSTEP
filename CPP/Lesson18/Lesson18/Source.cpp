#include <iostream>
//#include "io.h"
#include "students.h"
#include <iomanip>
using namespace std;

// масив структур, що описують студентів

int main()
{
    ArrayStudents as;  // масив студенів
    as.Block = 10;

    // !!! Все що закоментовано, це був давно написаний код минулим викладачем, який нам сказали так залишити.

    // FILE* f = nullptr;
    //fopen_s(&f, "students.txt", "ab");  // створюємо файл в разі першого запуску
    // fclose(f);
    // fopen_s(&f, "students.txt", "rb");  // відкриваємо файл на читання
    // int length = _filelength((_fileno(f))); // довжина файла в бт
   //  length = length / sizeof(Student);  // кількість студентів в базі з файла

   /*  if (length != 0)
     {
         as.Count = length;
         as.Size = as.Count + as.Block;
         Student** temp = new Student * [length];
         delete[]as.ptrSt;
         as.ptrSt = temp;
         for (int i = 0; i < length; i++)  // вичитка даних в масив студентів із файла
         {
             Student* student = new Student;
             fread(student, sizeof(Student), 1, f);
             as.ptrSt[i] = student;
         }
     }
     else
     {*/
        as.ptrSt = nullptr;
        as.Size = 0;
        as.Count = 0;
    // }
   //  fclose(f);
   

    // меню (двовимірний масив рядків)
    char menu[7][50] =
    {
        "1. Add students",
        "2. Delete ",// * подумати над перерозподілом пам'яті
        "3. Search ",  // ДЗ
        "4. Print",
        "5. Sort",
        "6. Edit",
        "7. Exit",
    };

    while (true)
    {
        // очищення консолі
        system("cls");

        // функція Меню
        Menu(menu, 7);
        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            // функція додавання студента в список
            AddStudents(as);
            break;
        case 2:
            DeleteStudent(as);
            break;
        case 3:
            SearchStudent(as);
            break;
        case 4:
            // функція виведення на екран всього списку студентів
            Print(as);
            break;
        case 5:
            SortStudents(as);
            break;
        case 6:
            EditStudent(as);
            break;
        case 7:
            Destroy(as);
            return 0;
            break;
        default:
            cout << "error" << endl;
            system("pause");
        }
    }


    return 0;
}