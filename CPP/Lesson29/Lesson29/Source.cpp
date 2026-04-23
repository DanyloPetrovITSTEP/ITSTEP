#include <iostream>

using namespace std;

template<typename T>
class SomeClass
{
    T* SomeData;

public:
    T* GetSomeData() const { return SomeData; }

    SomeClass()
    {
        SomeData = new T();

        cout << "SomeClass default created\n";
    }

    SomeClass(T value)
    {
        SomeData = new T(value);

        cout << "SomeClass created\n";
    }

    SomeClass(const SomeClass& other)
    {
        SomeData = new T(*other.SomeData);

        cout << "SomeClass copied\n";
    }

    SomeClass(SomeClass&& other) noexcept
    {
        SomeData = other.SomeData;
        other.SomeData = nullptr;

        cout << "SomeClass moved\n";
    }

    ~SomeClass()
    {
        delete SomeData;

        cout << "SomeClass deleted\n";
    }

    bool operator==(const SomeClass& other) const
    {
		return *SomeData == *other.SomeData;
	}

    SomeClass& operator=(const SomeClass& other)
    {
        if (*this == other) return *this;
        delete SomeData;
        SomeData = new T(*other.SomeData);

        cout << "SomeClass assigned\n";
        
        return *this;
    }

    SomeClass& operator=(SomeClass&& other) noexcept
    {
        if (*this == other) return *this;
        delete SomeData;
        SomeData = other.SomeData;
        other.SomeData = nullptr;

        cout << "SomeClass assign moved\n";

        return *this;
    }
};

template<typename T>
class SmartArray
{
    T* data;
    int size;
    int capacity;

    void reallocate(int newCapacity)
    {
        if (newCapacity <= capacity) return;

        T* newData = new T[newCapacity];

        for (int i = 0; i < size; i++)
        {
            newData[i] = std::move(data[i]);
        }

        delete[] data;

        data = newData;
        capacity = newCapacity;
    }

public:
    SmartArray()
    {
        size = capacity = 0;
        data = nullptr;
    }

    SmartArray(int capacity)
    {
        size = 0;
        this->capacity = capacity;

        data = new T[capacity];
    }

    SmartArray(const SmartArray& other)
    {
        size = other.size;
        capacity = other.capacity;
        data = new T[capacity];

        for (int i = 0; i < size; i++)
        {
            data[i] = other.data[i];
        }
    }

    SmartArray(SmartArray&& other) noexcept
    {
        size = other.size;
        capacity = other.capacity;
        data = other.data;

        other.size = other.capacity = 0;
        other.data = nullptr;
    }

    ~SmartArray()
    {
        delete[] data;
    }

    SmartArray& operator=(const SmartArray& other)
    {
        if (this == &other) return *this;

        delete[] data;

        size = other.size;
        capacity = other.capacity;
        data = new T[capacity];

        for (int i = 0; i < size; i++)
        {
            data[i] = other.data[i];
        }

        return *this;
    }

    SmartArray& operator=(SmartArray&& other) noexcept
    {
        if (this == &other) return *this;

        delete[] data;

        size = other.size;
        capacity = other.capacity;
        data = other.data;

        other.size = other.capacity = 0;
        other.data = nullptr;

        return *this;
    }

    void Clear()
    {
        delete[] data;
		data = nullptr;
        capacity = size = 0;
    }

    void PushBack(const T& value)
    {
        if (size >= capacity) reallocate(capacity == 0 ? 1 : capacity * 2);

        data[size] = value;
        size++;
    }

    void PushBack(T&& value)
    {
        if (size >= capacity) reallocate(capacity == 0 ? 1 : capacity * 2);

        data[size] = std::move(value);
        size++;
    }

    T& operator[](int index) const
    {
        return data[index];
    }

    T* GetAt(int index) const
    {
        if (index < 0 || index >= size) return nullptr;

        return &data[index];
    }

    T* PopBack()
    {
        if (size == 0) return nullptr;

        return &data[--size];
    }

    // a&b a|b a<<b a>>b
	template<typename Func>
    void For_Each(Func func)
    {
        for (int i = 0; i < size; i++)
        {
            func(data[i]);
        }
    }
};

//int Sum(int a, int b)
//{
//    return a + b;
//}
//
//int Difference(int a, int b)
//{
//    return a - b;
//}
//
//int Multiply(int a, int b)
//{
//    return a * b;
//}


//using SA_int = SmartArray<SomeClass<int>>;
//using math_func = int(int, int);
int main(int argc, char* argv[])
{
    /*SA_int array;

    array.PushBack(SomeClass<int>(1));

    math_func *func = Sum;
    int choice = 0;
    cin >> choice;
    switch (choice)
    {
    case 0: 
        func = Sum;
        break;
	case 1: 
        func = Difference;
		break;
    case 2: 
		func = Multiply;
        break;
    }
	int a, b;
	cin >> a >> b;

    cout << func(a, b) << endl;*/

    /*for (int i = 0; i < 10; i++)
    {
        SomeClass<int> SomeInt(i);
        array.PushBack(SomeInt);
    }

    SmartArray<SomeClass<int>> array_2(std::move(array));*/

    SmartArray<SomeClass<int>> arr;
    int SomeInt = 5;

    for (int i = 0; i < 10; i++)
    {
        SomeClass<int> SomeInt(i);
        arr.PushBack(SomeInt);
    }

    arr.For_Each([](SomeClass<int>& value) {});

    return 0;
}
