#pragma once

int* Allocate(int);
void Free(int*);
void Init(int* pointer, int size);
void Print(int* pointer, int size);
int DynamicArrMaxInd(int* arr, int size);
int DynamicArrMinInd(int* arr, int size);
void SumOdd(int* pointer, int size, int* suma);
int* DeleteLastElement(int* pointer, int& size);
int CountAboveAverage(int* arr, int size);
void SwapMinMax(int* arr, int size);
int* AppEnd(int* arr, int* size, int number);
void InsertByIndex(int*& arr, int& size, int number, int index);
void InsertArray(int*& arr, int& size, int* arr2, int size2, int index);
void DeleteByIndex(int*& arr, int& size, int index);