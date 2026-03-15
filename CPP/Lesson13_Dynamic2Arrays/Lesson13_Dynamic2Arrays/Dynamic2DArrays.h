#pragma once

int** Allocate(int, int);
int* Allocate(int);

void Init(int**, int, int);
void Init(int*, int);

void Print(int**, int, int);
void Print(int*, int);

void Free(int**, int);

int SumPositive(int**, int, int);

int SumMainDiag(int**, int, int);

bool SearchForElement(int**, int, int, int);

void AddColEnd(int**&, int, int&, int*);

void RemoveStringStart(int**&, int&);

void AddRowEnd(int**&, int&, int, int*);

void InsertRowAt(int**& p, int& rows, int cols, int index, int* mas);

void RemoveRowAt(int**& p, int& rows, int index);

void InsertColAt(int**& p, int rows, int& cols, int index, int* mas);

void RemoveColAt(int**& p, int rows, int& cols, int index);