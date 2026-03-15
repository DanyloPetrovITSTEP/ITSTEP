#pragma once
// прототипи функцій

void Init(int *, int size);
void Print(int array[], int size);
void Print(int array[][5], int rows, int cols);
int Sum(int array[], int size);
double Average(int array[], int size);
int EvenSum(int array[], int size);
void BubbleSort(int array[], int size);
int ArrayIndex(int array[], int size, int number);
int ArrayMax(int array[], int size);
int ArrayMin(int array[], int size);
void ArrayReverse(int array[], int size);
bool isPrime(int number);
int ArrayNumOfPrime(int array[], int size);
void Counter_Pos_Neg_Zero(int array[], int size, int*, int*, int*);
void Counter_Even_Odd_Mult5(int array[], int size, int*, int*, int*);
void SortArr(int array[], int size);
void SortArray_byChoice(int array[], int size, int choice);
void SortArray_HalfdownHalfhigh(int array[], int size);
void SortArray_BetweenNegElem(int array[], int size);
void Insert_Sort(int array[], int size);
void InitMatrix(int array[][5], int rows, int cols);
void PrintMatrix(int array[][5], int rows, int cols);
int SumMatrix(int array[][5], int rows, int cols);
void MainDiagMinMax(int array[][5], int rows, int cols, int* min, int* max);
void SortRows(int array[][5], int rows, int cols);