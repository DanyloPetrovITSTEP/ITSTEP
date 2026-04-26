// Додавати об'єкт лише на початок. Забирати лише з початку. 
// Якщо max_size більше -1 використовувати це значення як максимальне скільки може зберігати
template<typename T>
class Stack
{
    list<T> list;

    const int max_size = -1;

public:
    Stack(int max_size)
    {
        this->max_size = max_size;
    }

    void Push(const T& item);
    T Pop();
    const T& Top() const;
    bool Empty() const;
    int Size() const;
};

// Додавати об'єкт лише на кінець. Забирати лише з початку. 
// Якщо увімкнено ісКикліковий, то при забиранні об'єкта вставляти його в кінець
template<typename T>
class Queue
{
    list<T> list;

    bool isCyclical;

public:
    Queue(bool isCyclical)
    {
        this->isCyclical = isCyclical;
    }

    void Push(const T& item);
    T Pop();
    const T& Front() const;
    bool Empty() const;
    int Size() const;

};