#pragma once

struct Student
{
	double GPA; // середня оцінка  8
	int age;// 4
	char name[29];  //29
	char surname[29];  // 29
	char phone[18]; //18
};

struct ArrayStudents
{
	Student** ptrSt;  // двовимірний динамічний масив студентів
	int Size; // розмір масиву (в пам'яті)
	int Count; // кількість студентів в масиві
	int Block; // для зменшення перерозподілу пам'яті

};


void Menu(char[][50], int);

void AddStudents(ArrayStudents&);
void InputData(Student*);
void Print(ArrayStudents&);
void Destroy(ArrayStudents&);
void DeleteStudent(ArrayStudents&);
void SearchStudent(ArrayStudents&);
void SortStudents(ArrayStudents&);
void EditStudent(ArrayStudents&);