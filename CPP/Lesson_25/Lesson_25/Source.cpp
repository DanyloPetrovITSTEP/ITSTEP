#include <iostream>

using namespace std;

class BigData
{
public:
    BigData()
    {
        cout << "BigData constructor" << endl;
    }

    BigData(const BigData& other)
    {
        cout << "BigData copy constructor" << endl;
    }
};

class SomeClass
{
    BigData* data;

public:
    SomeClass()
    {
        data = new BigData();
        cout << "SomeClass constructor" << endl;
    }

    SomeClass(const SomeClass& other)
    {
        data = new BigData(*other.data);
        cout << "SomeClass copy constructor" << endl;
    }

    SomeClass(SomeClass&& other)
    {
        data = other.data;
        other.data = nullptr;
        cout << "SomeClass move constructor" << endl;
    }

    ~SomeClass()
    {
        delete data;
    }
};

class SomeContainer
{
    SomeClass someClass;

public:
    const SomeClass& GetSomeClass() const { return someClass; }

    SomeContainer()
    {
        cout << "SomeContainer constructor" << endl;
    }

    SomeContainer(const SomeClass& obj) : someClass(obj)
    {
        cout << "SomeContainer constructor with copy" << endl;
    }

    SomeContainer(SomeClass&& obj) : someClass(move(obj))
    {
        cout << "SomeContainer constructor with move" << endl;
    }
};




int main()
{
    SomeClass obj_1;

    SomeClass obj_2(move(obj_1));



    return 0;
}