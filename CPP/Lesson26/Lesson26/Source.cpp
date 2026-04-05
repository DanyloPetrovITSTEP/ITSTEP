#include <iostream>
using namespace std;

class SomeClass
{
	int someInt = 1;
	mutable int accessCountInt = 0; // mutable змінні можна змінювати навіть в константних записах

	static int someStaticInt;

	int SomeInt;

public:
	
	int GetSomeInt() const
	{
		accessCountInt++;
		return someInt;
	}

	void SetSomeInt(int newInt)
	{
		someInt = newInt;
	}

	static int GetSomeStaticInt()
	{
		return someStaticInt;
	}

	static void SetSomeStaticInt(int newStaticInt)
	{
		someStaticInt = newStaticInt;
	}

	SomeClass(int InSomeInt)
	{
		SomeInt = InSomeInt;
	}
};

int SomeClass::someStaticInt = 1;


class MyString
{
	// ...

public:

	MyString()
	{

	}

	MyString(const char* NewString)
	{

	}

	explicit MyString(int size)
	{

	}
};

void Print(MyString string)
{
	//...
	//cout << string << endl;
}

int main()
{
	SomeClass::GetSomeStaticInt();

	cout << SomeClass::GetSomeStaticInt() << endl;



	SomeClass Test1(100);
	SomeClass Test1 = 200;

	MyString Test3(10);
	MyString Test4(true);

	MyString Test5 = 10;
	// 1. 10 -> MyString name(10);
	// 2. Test5 = MyString name(10);

	Print(10);


	return 0;
}