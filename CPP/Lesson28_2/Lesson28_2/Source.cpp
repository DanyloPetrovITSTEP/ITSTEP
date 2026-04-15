#include <iostream>
#include <string>

using namespace std;

template<typename T>
class MyClass
{
    T* data;

public:
    MyClass& operator+(const MyClass& other)
    {
        return *this;
    }

    /*MyClass& operator*(const MyClass& other)
    {
        return *this;
    }*/
};

// ============================

template<int T>
class MyBuffer
{
    char* data;

public:
    MyBuffer()
    {
        this->data = new char[T];
    }
};

class SmallBuffer : public MyBuffer<16>
{

};

class BigBuffer : public MyBuffer<255>
{

};

// ============================

template<int T>
struct Factorial
{
    static constexpr int value = T * Factorial<T - 1>::value;
};

template<>
struct Factorial<0>
{
    static constexpr int value = 1;
};

// ============================

template<typename T>
concept Number = is_arithmetic_v<T>;
// constexpr bool

template<typename T>
concept Sum = requires(T t)
{
    t + t;
};

template<typename T>
concept Mult = requires(T t)
{
    t* t;
};

template<typename T>
requires Sum<T>
class SmartArray
{
    //...

public:
    double Sum()
    {


        /*double result;

        for (...)
        {
            result += data[i];
        }

        return result;*/
    }

    double Mult();
};


int main()
{
    cout << Factorial<5>::value << endl;

    return 0;
}
