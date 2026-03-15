#include <iostream>
#include <cstring>
#include "students.h"
#include <iomanip>
using namespace std;

void Destroy(ArrayStudents& as)
{
	for (int i = 0; i < as.Count; i++)
	{
		delete as.ptrSt[i];
	}
	delete[] as.ptrSt;

	// онулення пам'яті
	memset(&as, 0, sizeof(ArrayStudents));
}

void Menu(char menu[][50], int row)
{
	for (int i = 0; i < row; i++)
		cout << menu[i] << endl;
}


void InputData(Student* student)
{
	cout << "Name:" << endl;
	cin >> student->name;
	cout << "Surname:" << endl;
	cin >> student->surname;
	cout << "Age:" << endl;
	cin >> student->age;
	cout << "Phone:" << endl;
	cin >> student->phone;
	cout << "GPA:" << endl;
	cin >> student->GPA;
}
void AddStudents(ArrayStudents& as)
{
	system("cls");

	int count;
	cout << "How many? " << endl;
	cin >> count;

	if (count <= 0)
		return;

	int new_count = as.Count + count;  // нова кільсть студентів у списку

	//FILE* f = nullptr;

	//fopen_s(&f, "students.txt", "ab");

	if (as.Size < new_count)
	{
		as.Size = new_count + (as.Block - new_count % as.Block);

		Student** temp = new Student * [as.Size];
		for (int i = 0; i < as.Count; i++)
		{
			temp[i] = as.ptrSt[i];
		}
		delete[] as.ptrSt;
		as.ptrSt = temp;
	}

	//  додавання студентів
	for (int i = 0; i < count; i++)
	{
		Student* st = new Student;
		cout << "Enter the data for student #" << i+1 << ":" << endl;
		InputData(st);
		as.ptrSt[as.Count] = st;
		as.Count++;
		//fwrite(st, sizeof(Student), 1, f);
	}
	cout << "Students added." << endl;
	//fclose(f);
	system("pause");
}
void DeleteStudent(ArrayStudents& as)
{
	system("cls");

	if (as.Count == 0)
	{
		cout << "List is empty, no student to delete!" << endl;
		system("pause");
		return;
	}

	int number;
	cout << "Enter student number: " << endl;
	cin >> number;

	if (number < 1 || number > as.Count)
	{
		cout << "Invalid number!" << endl;
		system("pause");
		return;
	}

	int index = number - 1;
	delete as.ptrSt[index];

	for (int i = index; i < as.Count - 1; i++)
	{
		as.ptrSt[i] = as.ptrSt[i + 1];
	}

	as.Count--;

	cout << "Student deleted succesfully." << endl;
	system("pause");
}
void Print(ArrayStudents& as)
{
	system("cls");

	cout << setw(3) << "#" 
		<< setw(30) << "Name" 
		<< setw(30) << "Surname" 
		<< setw(8) << "Age" 
		<< setw(20) << "Phone" 
		<< setw(10) << "GPA" << endl;

	for (int i = 0; i < as.Count; i++)
	{
		cout << setw(3) << i + 1
			<< setw(30) << as.ptrSt[i]->name
			<< setw(30) << as.ptrSt[i]->surname
			<< setw(8) << as.ptrSt[i]->age
			<< setw(20) << as.ptrSt[i]->phone
			<< setw(10) << as.ptrSt[i]->GPA
			<< endl;
	}

	system("pause");
}
void SearchStudent(ArrayStudents& as)
{
	system("cls");

	if (as.Count == 0)
	{
		cout << "List is empty!" << endl;
		system("pause");
		return;
	}

	char surname[50];
	cout << "Enter surname to search: ";
	cin >> surname;
	bool found = false;

	for (int i = 0; i < as.Count; i++)
	{
		if (strcmp(as.ptrSt[i]->surname, surname) == 0)
		{
			if (!found)
			{
				cout << setw(3) << "#"
					<< setw(30) << "Name"
					<< setw(30) << "Surname"
					<< setw(8) << "Age"
					<< setw(20) << "Phone"
					<< setw(10) << "GPA"
					<< endl;
			}

			cout << setw(3) << i + 1
				<< setw(30) << as.ptrSt[i]->name
				<< setw(30) << as.ptrSt[i]->surname
				<< setw(8) << as.ptrSt[i]->age
				<< setw(20) << as.ptrSt[i]->phone
				<< setw(10) << as.ptrSt[i]->GPA
				<< endl;

			found = true;
		}
	}
	if (!found)
	{
		cout << "Student not found!" << endl;
	}

	system("pause");
}
void EditStudent(ArrayStudents& as)
{
	system("cls");

	if (as.Count == 0)
	{
		cout << "List is empty!" << endl;
		system("pause");
		return;
	}

	int number;
	cout << "Enter student number: ";
	cin >> number;

	if (number < 1 || number > as.Count)
	{
		cout << "Error! Wrong number!" << endl;
		system("pause");
		return;
	}

	InputData(as.ptrSt[number - 1]);

	cout << "Student edited" << endl;
	system("pause");
}
void SortStudents(ArrayStudents& as)
{
	if (as.Count == 0)
	{
		cout << "List is empty!" << endl;
		system("pause");
		return;
	}

	system("cls");

	int choice;
	cout << "Sort by:" << endl;
	cout << "1. Name (alphabetically)" << endl;
	cout << "2. Surname (alphabetically)" << endl;
	cout << "3. GPA (descending)" << endl;
	cout << "Enter choice: ";
	cin >> choice;

	for (int i = 0; i < as.Count - 1; i++)
	{
		for (int j = 0; j < as.Count - i - 1; j++)
		{
			bool swap_needed = false;

			switch (choice)
			{
			case 1:
				if (strcmp(as.ptrSt[j]->name, as.ptrSt[j + 1]->name) > 0) swap_needed = true;
				break;
			case 2:
				if (strcmp(as.ptrSt[j]->surname, as.ptrSt[j + 1]->surname) > 0) swap_needed = true;
				break;
			case 3:
				if (as.ptrSt[j]->GPA < as.ptrSt[j + 1]->GPA) swap_needed = true;
				break;
			default:
				cout << "Invalid choice!" << endl;
				system("pause");
				return;
			}

			if (swap_needed)
				swap(as.ptrSt[j], as.ptrSt[j + 1]);
		}
	}

	cout << "Sorted successfully!" << endl;
	cout << "====----------------------------------====" << endl;
	Print(as);
}