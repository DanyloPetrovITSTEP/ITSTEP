#include <iostream>
using namespace std;


template <typename T>
class SmartArray
{
private:

    T* data;                 // Вказівник на динамічний масив елементів
    size_t size;             // Поточна кількість елементів у масиві
    size_t capacity;         // Максимальна кількість елементів, яку можна зберігати без перевиділення пам'яті

    static size_t objectCount; // Лічильник створених об'єктів цього типу (окремо для кожного T)

    // Приватний метод для зміни розміру внутрішнього буфера
    // Повинен перевиділити пам'ять і скопіювати існуючі елементи
    void ResizeInternal(size_t newCapacity)
    {
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < size; ++i)
        {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
		capacity = newCapacity;
    }

public:

    // =========================
    // RULE OF FIVE
    // =========================

    // Конструктор за замовчуванням
    // Повинен створити порожній масив
    SmartArray()
    {
        data = nullptr;
        size = 0;
        capacity = 0;
		objectCount++;
    }

    // Конструктор із заданим розміром
    // Повинен створити масив із size елементів
    explicit SmartArray(size_t size)
    {
        data = new T[size];
        this->size = size;
        capacity = size;
		objectCount++;
    }

    // Конструктор із розміром та значенням
    // Повинен заповнити всі елементи значенням value
    SmartArray(size_t size, const T& value)
    {
        data = new T[size];
        this->size = size;
		capacity = size;
        for (int i = 0; i < size; i++)
        {
            data[i] = value;
        }
		objectCount++;
    }

    // Конструктор копіювання
    // Повинен створити повну копію іншого масиву
    SmartArray(const SmartArray& other)
    {
        data = new T[other.capacity];
        size = other.size;
        capacity = other.capacity;
        for (int i = 0; i < size; i++)
        {
            data[i] = other.data[i];
        }
		objectCount++;
    }

    // Move-конструктор
    // Повинен "перемістити" ресурси з іншого об'єкта
    SmartArray(SmartArray&& other) noexcept
    {
        data = other.data;
        size = other.size;
		capacity = other.capacity;
        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
		objectCount++;
    }

    // Деструктор
    // Повинен звільнити всю виділену пам'ять
    ~SmartArray()
    {
        delete[] data;
        data = nullptr;
        size = 0;
		capacity = 0;
		objectCount--;
    }

    // Оператор копіювання
    // Повинен правильно обробляти самоприсвоєння
    SmartArray& operator=(const SmartArray& other)
    {
        if (this != &other)
        {
            delete[] data;
			data = new T[other.capacity];
            size = other.size;
			capacity = other.capacity;
            for (int i = 0; i < size; i++)
            {
                data[i] = other.data[i];
			}
        }
        return *this;
    }

    // Move-оператор присвоювання
    // Повинен передати ресурси без копіювання
    SmartArray& operator=(SmartArray&& other) noexcept
    {
        if (this != &other)
        {
            delete[] data;
            data = other.data;
            size = other.size;
            capacity = other.capacity;
            other.data = nullptr;
            other.size = 0;
            other.capacity = 0;
        }
        return *this;
    }

    // =========================
    // ACCESS
    // =========================

    // Оператор доступу до елементу за індексом без перевірки меж
    T& operator[](size_t index)
    {
		return data[index];
    }

    // Константна версія оператора []
    const T& operator[](size_t index) const
    {
		return data[index];
    }

    // Повертає перший елемент масиву
    T& Front()
    {
        return data[0];
    }

    // Повертає останній елемент масиву
    T& Back()
    {
        return data[size - 1];
    }

    // Константна версія Front
    const T& Front() const
    {
		return data[0];
    }

    // Константна версія Back
    const T& Back() const
    {
		return data[size - 1];
    }

    // Повертає сирий вказівник на масив
    T* Data()
    {
		return data;
    }

    // Константна версія Data
    const T* Data() const
    {
		return data;
    }

    // =========================
    // SIZE
    // =========================

    // Повертає кількість елементів
    size_t Size() const
    {
		return size;
    }

    // Повертає поточну місткість масиву
    size_t Capacity() const
    {
		return capacity;
    }

    // Перевіряє, чи масив порожній
    bool Empty() const
    {
		return size == 0;
    }

    // Очищає масив (розмір стає 0, але пам'ять може залишатися)
    void Clear()
    {
		size = 0;
    }

    // Змінює розмір масиву
    // Якщо новий розмір більший — додає елементи за замовчуванням
    void Resize(size_t newSize)
    {
        if (newSize > capacity)
        {
            ResizeInternal(newSize * 2);
        }
        if (newSize > size)
        {
            for (size_t i = size; i < newSize; ++i)
            {
                data[i] = T();
            }
        }
		size = newSize;
    }

    // Резервує пам'ять під newCapacity елементів
    void Reserve(size_t newCapacity)
    {
        if (newCapacity > capacity)
        {
            ResizeInternal(newCapacity);
		}
    }

    // Зменшує capacity до size
    void ShrinkToFit()
    {
        if (capacity > size)
        {
            ResizeInternal(size);
		}
    }

    // =========================
    // MODIFICATION
    // =========================

    // Додає елемент у кінець масиву (копіювання)
    void PushBack(const T& value)
    {
        if (size >= capacity)
        {
			if (capacity == 0)
            {
                ResizeInternal(1);
            }
            else
            {
                ResizeInternal(capacity * 2);
			}
		}
        data[size++] = value;
    }

    // Додає елемент у кінець масиву (переміщення)
    void PushBack(T&& value)
    {
        if (size >= capacity)
        {
            if (capacity == 0)
            {
                ResizeInternal(1);
            }
            else
            {
                ResizeInternal(capacity * 2);
            }
        }
        data[size++] = std::move(value);
    }

    // Видаляє останній елемент масиву
    void PopBack()
    {
        if (size > 0)
        {
            --size;
        }
    }

    // Вставляє елемент у задану позицію
    // Повинен зсунути інші елементи вправо
    void Insert(size_t index, const T& value)
    {
        if (index > size)
        {
            return;
        }

        if (size >= capacity)
        {
            ResizeInternal(capacity == 0 ? 1 : capacity * 2);
		}
        for (int i = size; i > index; --i)
        {
            data[i] = data[i - 1];
		}
        data[index] = value;
		++size;
    }

    // Видаляє елемент за індексом
    // Повинен зсунути інші елементи вліво
    void RemoveAt(size_t index)
    {
        if (index >= size)
        {
            return;
        }

        for (int i = index; i < size - 1; ++i)
        {
            data[i] = data[i + 1];
        }
		--size;
    }

    // Видаляє перше входження заданого значення
    void Remove(const T& value)
    {
        int index = Find(value);
        if (index != -1)
        {
            RemoveAt(index);
		}
    }

    // Обмінює вміст двох масивів
    void Swap(SmartArray& other)
    {
        T* tempData = data;
        data = other.data;
        other.data = tempData;

        size_t tempSize = size;
        size = other.size;
        other.size = tempSize;

        size_t tempCapacity = capacity;
        capacity = other.capacity;
        other.capacity = tempCapacity;
    }

    // Заповнює всі елементи заданим значенням
    void Fill(const T& value)
    {
        for (int i = 0; i < size; ++i)
        {
            data[i] = value;
		}
    }

    // =========================
    // SEARCH
    // =========================

    // Повертає індекс першого входження значення
    // Якщо не знайдено — повертає -1
    int Find(const T& value) const
    {
        for (size_t i = 0; i < size; ++i)
        {
            if (data[i] == value)
            {
                return i;
            }
        }
		return -1;
    }

    // Перевіряє, чи містить масив задане значення
    bool Contains(const T& value) const
    {
        return Find(value) != -1;
    }

    // Повертає кількість входжень заданого значення
    int Count(const T& value) const
    {
        int count = 0;

        for (int i = 0; i < size; i++)
        {
            if (data[i] == value)
            {
                count++;
            }
        }

		return count;
    }

    // =========================
    // ITERATORS
    // =========================

    // Повертає ітератор на початок масиву
    T* begin()
    {
        return data;
    }

    // Повертає ітератор на кінець масиву
    T* end()
    {
		return data + size;
    }

    // Константна версія begin
    const T* begin() const
    {
		return data;
    }

    // Константна версія end
    const T* end() const
    {
		return data + size;
    }

    // =========================
    // OPERATORS
    // =========================

    // Повертає новий масив як результат додавання двох масивів
    SmartArray operator+(const SmartArray& other) const
    {
		SmartArray ArrResult(size + other.size);

        for (int i = 0; i < size; i++)
        {
            ArrResult.data[i] = data[i];
        }

        for (int i = 0; i < other.size; i++)
        {
            ArrResult.data[size + i] = other.data[i];
		}

		return ArrResult;
    }

    // Повертає новий масив як результат віднімання
    SmartArray operator-(const SmartArray& other) const
    {
        SmartArray ArrResult(size);

        for (int i = 0; i < size; i++)
        {
            ArrResult.data[i] = data[i];
        }

        for (int i = 0; i < other.size; i++)
        {
            ArrResult.Remove(other.data[i]);
		}

		return ArrResult;
    }

    // Множить кожен елемент на значення value
    SmartArray operator*(const T& value) const
    {
        SmartArray ArrResult(size);

        for (int i = 0; i < size; i++)
        {
            ArrResult.data[i] = data[i] * value;
		}

		return ArrResult;
    }

    // Додає інший масив до поточного
    SmartArray& operator+=(const SmartArray& other)
    {
        if (size + other.size > capacity)
        {
			ResizeInternal((size + other.size) * 2);
        }

        for (int i = 0; i < other.size; i++)
        {
			data[size + i] = other.data[i];
		}

		size += other.size;
        return *this;
	}


    // Віднімає інший масив від поточного
    SmartArray& operator-=(const SmartArray& other)
    {
        for (int i = 0; i < other.size; i++)
        {
            Remove(other.data[i]);
        }

        return *this;
    }

    // Перевіряє рівність двох масивів
    bool operator==(const SmartArray& other) const
    {
        if (size != other.size)
        {
            return false;
        }

        for (int i = 0; i < size; i++)
        {
            if (data[i] != other.data[i])
            {
                return false;
            }
		}

		return true;
    }

    // Перевіряє нерівність
    bool operator!=(const SmartArray& other) const
    {
		return !(*this == other);
    }

    // Порівняння масивів (наприклад за сумою елементів)
    bool operator<(const SmartArray& other) const
    {
        T elemSum = T();
		T otherElemSum = T();

        for (int i = 0; i < size; i++)
        {
            elemSum += data[i];
        }

        for (int i = 0; i < other.size; i++)
        {
            otherElemSum += other.data[i];
		}

		return elemSum < otherElemSum;
    }

    // Порівняння масивів
    bool operator>(const SmartArray& other) const
    {
		return other < *this;
    }

    // Порівняння масивів
    bool operator<=(const SmartArray& other) const
    {
		return !(*this > other);
    }

    // Порівняння масивів
    bool operator>=(const SmartArray& other) const
    {
		return !(*this < other);
    }

    // Оператор логічного заперечення
    // Повертає true, якщо масив порожній
    bool operator!() const
    {
		return size == 0;
    }

    // =========================
    // STATIC
    // =========================

    // Повертає кількість створених об'єктів цього типу
    static size_t GetObjectCount()
    {
		return objectCount;
    }

    // =========================
    // TEMPLATE METHODS
    // =========================

    // Перетворює масив у масив іншого типу
    // Наприклад SmartArray<int> -> SmartArray<double>
    template <typename U>
    void Transform(SmartArray<U>& out) const        // Довелось спитати ChatGPT, тому з static_cast (не пам'ятаю чи було нам дозволено його використовувати)
    {
        out.Resize(size);
        for (size_t i = 0; i < size; ++i)
        {
            out[i] = static_cast<U>(data[i]);
		}
    }

    // =========================
    // FRIEND OPERATORS
    // =========================

    // Виведення масиву у потік (cout)
    template <typename U>
    friend ostream& operator<<(ostream& out, const SmartArray<U>& arr)
    {
        out << "[";
        for (size_t i = 0; i < arr.size; ++i)
        {
            out << arr.data[i];
            if (i < arr.size - 1)
            {
                out << ", ";
            }
        }
        out << "]";

		return out;
    }

    // Введення масиву з потоку (cin)
    template <typename U>
    friend istream& operator>>(istream& in, SmartArray<U>& arr)
    {
        for (size_t i = 0; i < arr.size; ++i)
        {
            in >> arr.data[i];
		}

		return in;
    }
};



int main()
{



	return 0;
}