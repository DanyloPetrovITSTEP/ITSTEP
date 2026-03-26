#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>

#define MAX_TITLE 100
#define MAX_BOOKS 1000

struct Book
{
    char title[MAX_TITLE];
    char author[MAX_TITLE];
    int year;
};

void addBook(Book library[], int& bookCount);
void removeBook(Book library[], int& bookCount);
void findBook(Book library[], int bookCount);
void showBooks(Book library[], int bookCount);
void sortBooks(Book library[], int bookCount);
void saveToFile(Book library[], int bookCount);
void loadFromFile(Book library[], int& bookCount);
