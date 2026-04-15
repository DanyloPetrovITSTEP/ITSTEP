#include <iostream>
#include <string>

using namespace std;

template<typename T>
class SmartArray
{
    T* data;
    int size;

public:
    SmartArray(int size = 1)
    {
        if (size < 1)
        {
            this->size = 0;
        }
        else
        {
            this->size = size;
            data = new T[size];
        }
    }

    ~SmartArray()
    {
        delete[] data;
    }

    T& operator[](int index)
    {
        return data[index];
    }



    void Print()
    {
        for (int i = 0; i < this->size; i++)
        {
            cout << data[i] << " ";
        }
    }
};

template<typename T, typename D>
struct Pair
{
    T Key;
    D Value;
};

template<typename T, typename D>
ostream& operator<<(ostream& os, const Pair<T, D>& p)
{
    return os << p.Key << ":\n" << p.Value << '\n';
}

struct StudentData
{
    int year;
};

ostream& operator<<(ostream& os, const StudentData& sd)
{
    return os << "Year: " << sd.year << '\n';
}

class MyClass
{
    char* byteData;

public:

    template<typename T>
    T Get()
    {
        return (T)byteData;
    }
};

int main()
{
    int arr_size = 10;
    SmartArray<Pair<string, StudentData>> Students(10);

    for (int i = 0; i < arr_size; i++)
    {
        Students[i].Key = "Student_" + to_string(i + 1);
        Students[i].Value.year = rand() % 6 + 1;
    }

    Students.Print();





    MyClass someClass;

    someClass.Get<int>();

    return 0;
}