#include <iostream>
using namespace std;

class String
{
    char* ptr;
    int length;

public:
    const char* GetData() const
    {
        return ptr;
    }

    int GetLength() const
    {
        return length;
    }

    String()
    {
        length = 0;
        ptr = new char('\0');
    }

    String(const String& string)
    {
        length = 0;
        Append(string.GetData());
    }

    String(const char* ptr)
    {
        length = 0;
        Append(ptr);
    }

    String(const char* ptr, const int length)
    {
        this->length = 0;
        Append(ptr, length);
    }

    ~String()
    {
        delete[] ptr;
    }

    void Print() const
    {
        cout << ptr << endl;
    }

    void Append(const String& string, int length = -1)
    {
        Append(string.GetData(), length);
    }

    void Append(const char* ptr, int length = -1)
    {
        if (length < 0)
        {
            length = 0;

            while (ptr[length] != '\0')
            {
                length++;
            }
        }

        const int new_length = this->length + length;
        char* new_ptr = new char[new_length + 1];

        for (int i = 0; i < this->length; i++)
        {
            new_ptr[i] = this->ptr[i];
        }

        for (int i = 0; i < length; i++)
        {
            new_ptr[i + this->length] = ptr[i];
        }

        new_ptr[new_length] = '\0';

        delete[] this->ptr;
        this->ptr = new_ptr;
        this->length = new_length;
    }

    void Remove(const char* old_substring, const char* new_substring)
    {
        String result;

        int old_substring_length = 0;
        int new_substring_length = 0;

        while (old_substring[old_substring_length] != '\0')
        {
            old_substring_length++;
        }

        while (new_substring[new_substring_length] != '\0')
        {
            new_substring_length++;
        }

        int i = 0;
        while (i < length)
        {
            bool match = true;

            for (int j = 0; j < old_substring_length; j++)
            {
                if (ptr[i + j] != old_substring[j])
                {
                    match = false;

                    break;
                }
            }

            if (match)
            {
                result.Append(new_substring);
                i += old_substring_length;
            }
            else
            {
                result.Append(ptr + i, 1);
                i++;
            }
        }

        delete[] ptr;
        length = result.length;
        ptr = new char[length + 1];

        for (int i = 0; i <= length; i++)
        {
            ptr[i] = result.ptr[i];
        }
    }

    void Clear()
    {
        delete[] ptr;

        length = 0;
        ptr = new char('\0');
    }
};

int main()
{
    String string1("Test TEXT Asd TEXT Asd");
    string1.Print(); // Test TEXT Asd TEXT Asd

    string1.Remove("TEXT", "text123");
    string1.Print(); // Test text123 Asd TEXT Asd

    // Треба: Test text123 Asd text123 Asd

    return 0;
}