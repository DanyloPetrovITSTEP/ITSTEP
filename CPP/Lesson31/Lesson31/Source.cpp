#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

template<typename T>
class Node
{
    T data;

    Node<T>* parent;
    Node<T>* next;
    Node<T>* prev;

    bool isBlack = false;

public:
    Node<T>*& GetParent() { return parent; }
    void SetParent(Node<T>* parent) { this->parent = parent; }

    Node<T>*& GetNext() { return next; }
    Node<T>*& GetPrev() { return prev; }
    void SetNext(Node<T>* next)
    {
        this->next = next;
        if (prev != nullptr)
        {
            prev->SetParent(this);
        }
    }
    void SetPrev(Node<T>* prev)
    {
        this->prev = prev;
        if (prev != nullptr)
        {
            prev->SetParent(this);
        }
    }

    bool IsBlack() const { return isBlack; }
    void SetBlack(bool isBlack) { this->isBlack = isBlack; }

    const T& GetData() const { return data; }
    void SetData(const T& newData) { data = newData; }

    Node(const T& data, Node<T>* next = nullptr, Node<T>* prev = nullptr, Node<T>* parent = nullptr)
    {
        this->data = data;
        this->next = next;
        this->prev = prev;
        this->parent = parent;
    }
};

template<typename T>
class BinaryTree
{
    Node<T>* root;

    void DeleteTree(Node<T>*& node)
    {
        if (node == nullptr)
        {
            return;
        }

        DeleteTree(node->GetPrev());
        DeleteTree(node->GetNext());

        delete node;
    }

    void PrintTree(Node<T>* node) const
    {
        if (node == nullptr)
        {
            return;
        }

        PrintTree(node->GetPrev());

        cout << node->GetData() << endl;

        PrintTree(node->GetNext());
    }

    void Rebalance(Node<T>* node)
    {
		while (node != root && node->GetParent()->IsBlack() == false) // виконуємо дії поки не дійдемо до кореня і поки батьківский вузел - червоний
        {
            Node<T>* parent = node->GetParent(); // "запам'ятовуємо" батьківський вузел
			Node<T>* grand = parent->GetParent(); // "запам'ятовуємо" вузел перед батьківським, діда :P

			if (!grand || !parent) return; // якщо немає діда або батька, то виходимо з функції

            if (parent == grand->GetPrev()) // якщо батікьвский вузел є лівим вузлом діда тоді...
            {
				Node<T>* uncle = grand->GetNext(); // "запам'ятовуємо" правий вузел діда, дядько

                if (uncle && uncle->IsBlack() == false) // якщо дядько існує і він червоний, тоді...
                {
                    parent->SetBlack(true); // робимо батьківский вузел чорним
                    uncle->SetBlack(true); // робимо вузел "дядько" чорним
                    grand->SetBlack(false); // робимо вузел "дід" червоним

                    node = grand; // робимо вузел "дід" поточним для наступної ітерації
                }
                else  // або, якщо дядька немає, або він чорний (O_O), тоді...
                {
					if (node == parent->GetNext()) // якщо поточний вузел є правим вузлом батьківского вузла, тоді...
                    {
                        node = parent; // робимо поточни вузел - батьківским
                        RotateLeft(node); // виконуємо зрушення вліво від поточного вузла, який тепер є батьківским
                    }

                    parent->SetBlack(true); // робимо батьківский вузел чорним (ПРАВИЛЬНО КАЗАТИ ТЕМНОШКІРИМ... а, ой, ми не про це..)
                    grand->SetBlack(false); // робимо вузел діда червоним

                    RotateRight(grand); // зрушуємо дерево вправо від вузла діда
                }
            }
			else // якщо батьківский вузел не є лівим вузлом діда, тоді...
            {
				Node<T>* uncle = grand->GetPrev(); // запам'ятовуємо лівий вузел діда як дядька

                if (uncle && uncle->IsBlack() == false) // якщо дядько існує і він червоний, тоді...
                {
					parent->SetBlack(true); // робимо батьківский вузел чорним
                    uncle->SetBlack(true); // робимо вузел дядька чорним
                    grand->SetBlack(false); // робимо вузел діда червоним

                    node = grand; // робимо вузел діда поточним
                }
                else // або, якщо дядька немає, або він чорний, тоді...
                {
					if (node == parent->GetPrev()) // якщо поточний вузел є лівим вузлом батьківского вузла, тоді...
                    {
						node = parent; // робимо поточни вузел - батьківским
                        RotateRight(node); // зрушуємо дерево вправо від поточного вузла, тобто від батьківского
                    }

					parent->SetBlack(true); // робимо батьківский вузел чорним
					grand->SetBlack(false); // робимо вузел діда червоним

                    RotateLeft(grand); // зрушуємо дерево вліво від вузла діда
                }
            }
        }
    }

    void RotateLeft(Node<T>* node)
    {
        Node<T>* right = node->GetNext(); // запам'ятовуємо правий вузел від поточного вузла
		node->SetNext(right->GetPrev()); // робимо правим вузлом поточного вузла, лівим вузлом правого вузла (чаво я тільки-но написав??)

        if (right->GetPrev() != nullptr) // якщо лівий вузол правого вузла існує, тоді..
        {
            right->GetPrev()->SetParent(node); // робимо потойний вузел батьківским для лівого вузла правого вузла ( ._. ...)
        }

        right->SetParent(node->GetParent()); // робимо батьківским вузлом для правого вузла, батьківский вузел поточного вузла

        if (node->GetParent() == nullptr) // якщо в поточного вузла немає батьківского вузла, тоді...
        {
            root = right; // робимо правий вузел коренем дерева
        }
        else if (node == node->GetParent()->GetPrev()) // або, якщо поточний вузел є лівим вузлом батьківского вузла поточного вузла (вузел з вузлом на вузлі за вузлами вузлів x_x), тоді...
        {
            node->GetParent()->SetPrev(right);
        }
        else
        {
            node->GetParent()->SetNext(right);
        }

        right->SetPrev(node);
        node->SetParent(right);
    }

    void RotateRight(Node<T>* node)
    {
        Node<T>* left = node->GetPrev();
        node->SetPrev(left->GetNext());

        if (left->GetNext() != nullptr)
        {
            left->GetNext()->SetParent(node);
        }

        left->SetParent(node->GetParent());

        if (node->GetParent() == nullptr)
        {
            root = left;
        }

        else if (node == node->GetParent()->GetNext())
        {
            node->GetParent()->SetNext(left);
        }
        else
        {
            node->GetParent()->SetPrev(left);
        }

        left->SetNext(node);
        node->SetParent(left);
    }

public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree() { DeleteTree(root); }

    void Insert(const T& data)
    {
        Node<T>* newNode = new Node<T>(data);


        Node<T>* parent = nullptr;
        Node<T>* current = root;

        while (current)
        {
            parent = current;

            if (data < current->GetData())
            {
                current = current->GetPrev();
            }
            else
            {
                current = current->GetNext();
            }
        }

        newNode->SetParent(parent);

        if (parent == nullptr)
        {
            root = newNode;
        }
        else if (data < parent->GetData())
        {
            parent->SetPrev(newNode);
        }
        else
        {
            parent->SetNext(newNode);
        }

        Rebalance(newNode);
    }

    void Print() const
    {
        PrintTree(root);
        cout << endl;
    }
};

int main(int argc, char* argv[])
{
    BinaryTree<int> tree;
    tree.Insert(10);
    tree.Insert(20);
    tree.Insert(30);
    tree.Insert(40);
    tree.Insert(50);
    tree.Insert(60);
    tree.Insert(70);
    tree.Insert(80);
    tree.Insert(90);
    tree.Insert(100);

    tree.Print();

    return 0;
}
