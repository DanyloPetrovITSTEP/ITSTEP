#include <iostream>
#include <vector>
using namespace std;

class Base
{
	int someInt = 0;

public:

	int getSomeInt() const { return someInt; }
	void setSomeInt(int someInt) { this->someInt = someInt; }


	virtual ~Base() = default;
};

class Derived : public Base {};

enum Color
{
	RED, // = 0
	GREEN, // = 1
	BLUE, // = 2
	YELLOW, // = 3
};


int main()
{
	 //static cast
	 //dynamic cast
	 //const cast
	 //reinterpret cast

	//double d = 5.6;
	//int i = static_cast<int>(d);

	//Derived x;
	//Base* p = static_cast<Base*>(&x); // Derived* -> Base*

	//vector<Base*> vec;

	//for (Base* i : vec)
	//{
	//	Derived* der1 = dynamic_cast<Derived*>(i);
	//	
	//	if (der1 == nullptr) continue;

	//	// ...

	//	try
	//	{
	//		Derived& der2 = dynamic_cast<Derived&>(*i);
	//	}
	//	catch (exception& e) // std::bad_cast
	//	{
	//		cerr << e.what() << endl;
	//	}
	//	catch (...) {}
	//	
	//}

	/*const Base test;
	test.getSomeInt();

	Base* pTest = const_cast<Base*>(&test);

	pTest->setSomeInt(10);

	cout << test.getSomeInt() << endl;*/


	/*double x = 100;

	int* p = reinterpret_cast<int*>(&x);

	cout << &x << ' ' << p << endl;
	cout << x << ' ' << *p << endl;*/

	// + 
	// Base* base = new Derived;
	// Derived* d = reinterpret_cast<Derived*>(base);

	// +
	// Derived* derived = new Derived;
	// Base* nase = reinterpret_cast<Base*>(derived);

	// -
	// Base* base = new Base;
	// Derived* derived = reinterpret_cast<Derived*>(base);




	return 0;
}