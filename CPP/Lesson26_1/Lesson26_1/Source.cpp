#include <iostream>
using namespace std;

class SomeClass
{
	int someInt = 1;
	static int ObjectCount;

public:

	int GetSomeInt() const
	{
		return someInt;
	}

	void SetSomeInt(int newInt)
	{
		someInt = newInt;
	}

	SomeClass()
	{
		ObjectCount++;
	}

	~SomeClass()
	{
		ObjectCount--;
	}

	static int GetObjectCount()
	{
		return ObjectCount;
	}

};

int SomeClass::ObjectCount = 0;

int main()
{
	SomeClass obj_1;
	SomeClass obj_2;

	cout << SomeClass::GetObjectCount() << endl;

	{
		SomeClass obj_3;
		SomeClass obj_4;
		SomeClass obj_5;

		cout << SomeClass::GetObjectCount() << endl;
	}

	cout << SomeClass::GetObjectCount() << endl;

	return 0;
}