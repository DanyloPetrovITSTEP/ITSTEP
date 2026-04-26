#include <iostream>
using namespace std;

template<typename T>
class Node
{
    T data;
    Node<T>* next;
    Node<T>* prev;

public:
    Node<T>* GetNext() const { return next; }
    Node<T>* GetPrev() { return prev; }
    void SetNext(Node<T>* next) { this->next = next; }
    void SetPrev(Node<T>* prev) { this->prev = prev; }

    const T& GetData() const { return data; }
    void SetData(T newData) { data = newData; }

    Node(T data, Node<T>* next = nullptr, Node<T>* prev = nullptr)
    {
        this->data = data;
        this->next = next;
        this->prev = prev;
    }
};

template<typename T>
class List
{
    Node<T>* head;
    Node<T>* tail;

    int size;

public:
    Node<T>* GetHead() const { return head; }
    Node<T>* GetTail() const { return tail; }
    int GetSize() const { return size; }

    Node<T>* GetNodeAt(const int pos) const
    {
        if (pos < 0 || pos >= size) return nullptr;

        Node<T>* curr;

        if (pos < size / 2)
        {
            curr = head;
            for (int i = 0; i < pos; i++)
            {
                curr = curr->GetNext();
            }
        }
        else
        {
            curr = tail;
            for (int i = size - 1; i > pos; i--)
            {
                curr = curr->GetPrev();
            }
        }

        return curr;
    }
    const T* At(int pos) const
    {
        Node<T>* node = GetNodeAt(pos);
        return node ? &(node->GetData()) : nullptr;
    }

    void Push(T newData, const int pos)
    {
        if (pos < 0 || pos > size) return;

        Node<T>* newNode = new Node<T>(newData);

        if (size == 0)
        {
            head = tail = newNode;
        }
        else if (pos == 0)
        {
            newNode->SetNext(head);
            head->SetPrev(newNode);
            head = newNode;
        }
        else if (pos == size)
        {
            newNode->SetPrev(tail);
            tail->SetNext(newNode);
            tail = newNode;
        }
        else
        {
            Node<T>* curr = GetNodeAt(pos);
            newNode->SetNext(curr);
            newNode->SetPrev(curr->GetPrev());

            curr->GetPrev()->SetNext(newNode);
            curr->SetPrev(newNode);
        }
        size++;
    }

    void PushBack(T newData)
    {
        Push(newData, size);
    }

    void PushFront(T newData)
    {
        Push(newData, 0);
    }

    Node<T>* Pop(int pos)
    {
        if (pos < 0 || pos >= size) return nullptr;

        Node<T>* elem = GetNodeAt(pos);

        if (size == 1)
        {
            head = tail = nullptr;
        }
        else if (elem == head)
        {
            head = head->GetNext();
            head->SetPrev(nullptr);
        }
        else if (elem == tail)
        {
            tail = tail->GetPrev();
            tail->SetNext(nullptr);
        }
        else
        {
            elem->GetPrev()->SetNext(elem->GetNext());
            elem->GetNext()->SetPrev(elem->GetPrev());
        }
        size--;
        return elem;
    }

    Node<T>* PopFront()
    {
        return Pop(0);
    }
    Node<T>* PopBack()
    {
        return Pop(size - 1);
    }


    T& operator[](int pos)
    {
        Node<T>* node = GetNodeAt(pos);
        return node->GetData();
    }
    const T& operator[](int pos) const
    {
        Node<T>* node = GetNodeAt(pos);
        return node->GetData();
    }

    List() : head(nullptr), tail(nullptr), size(0)
    {

    }

    ~List()
    {
        Node<T>* curr = head;

        for (int i = 0; i < size; i++)
        {
            Node<T>* fordel = curr;
            curr = curr->GetNext();

            delete fordel;
        }
    }
};


// Додавати об'єкт лише на початок. Забирати лише з початку. 
// Якщо max_size більше -1 використовувати це значення як максимальне скільки може зберігати
template<typename T>
class Stack
{
    List<T> list;

    const int max_size;

public:
    Stack(int max_size) : max_size(max_size) {}

    void Push(const T& item)
    {
        if (max_size > -1 && list.GetSize() >= max_size)
        {
            return;
        }

        list.PushFront(item);
    }

    T Pop()
    {
        if (list.GetSize() == 0) return T();

        Node<T>* node = list.PopFront();
        T value = node->GetData();
        delete node;
        return value;
    }

    const T& Top() const
    {
	    return list.GetHead()->GetData();
    }

    bool Empty() const
    {
        return list.GetSize() == 0;
    }

    int Size() const
    {
        return list.GetSize();
    }
};

// Додавати об'єкт лише на кінець. Забирати лише з початку. 
// Якщо увімкнено ісКикліковий, то при забиранні об'єкта вставляти його в кінець
template<typename T>
class Queue
{
    List<T> list;

    bool isCyclical;

public:
    Queue(bool isCyclical)
    {
        this->isCyclical = isCyclical;
    }

    void Push(const T& item)
    {
        list.PushBack(item);
    }

    T Pop()
    {
        if (list.GetSize() == 0) return T();

        Node<T>* node = list.PopFront();
        T value = node->GetData();
        delete node;

        if (isCyclical)
        {
			list.PushBack(value);
        }

        return value;
    }

    const T& Front() const
    {
		return list.GetHead()->GetData();
    }

    bool Empty() const
    {
		return list.GetSize() == 0;
    }

    int Size() const
    {
		return list.GetSize();
    }
};

// homework.isDone() ? cout << "yaaaay\n" : cout << ":(\n"