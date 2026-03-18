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
        ptr = new char[1];
        ptr[0] = '\0';
    }

    String(const String& string)
    {
        length = 0;
        ptr = new char[1];
        ptr[0] = '\0';
        Append(string.GetData());
    }

    String(const char* ptr)
    {
        length = 0;
        this->ptr = new char[1];
        this->ptr[0] = '\0';
        Append(ptr);
    }

    String(const char* ptr, const int length)
    {
        this->length = 0;
        this->ptr = new char[1];
        this->ptr[0] = '\0';
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

    bool Contains(const char* substring) const
    {
        int substring_length = 0;
        
        while (substring[substring_length] != '\0')
        {
            substring_length++;
        }

        for (int i = 0; i <= length - substring_length; i++)
        {
            bool match = true;

            for (int j = 0; j < substring_length; j++)
            {
                if (ptr[i + j] != substring[j])
                {
                    match = false;
                    break;
                }
            }

            if (match)
            {
                return true;
            }
        }
        return false;
    }

    int Count(const char* substring) const
    {
        int substring_length = 0;
        
        while (substring[substring_length] != '\0')
        {
            substring_length++;
        }

        int count = 0;

        for (int i = 0; i <= length -substring_length; i++)
        {
            bool match = true;

            for (int j = 0; j < substring_length; j++)
            {
                if (ptr[i + j] != substring[j])
                {
                    match = false;
                    break;
                }
            }

            if (match)
            {
                count++;
                i += substring_length - 1;
            }
        }
        return count;
    }

    void Insert(int position, const char* substring)
    {
        int substring_length = 0;

        while (substring[substring_length] != '\0')
        {
            substring_length++;
        }

        char* new_ptr = new char[length + substring_length + 1];

        for (int i = 0; i < position; i++)
        {
            new_ptr[i] = ptr[i];
        }
        
        for (int i = 0; i < substring_length; i++)
        {
            new_ptr[position + i] = substring[i];
        }

        for (int i = position; i < length; i++)
        {
            new_ptr[substring_length + i] = ptr[i];
        }

        new_ptr[length + substring_length] = '\0';

        delete[] ptr;
        ptr = new_ptr;
        length += substring_length;
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

            if (i + old_substring_length > length)
            {
                match = false;
            }
            else
            {
                for (int j = 0; j < old_substring_length; j++)
                {
                    if (ptr[i + j] != old_substring[j])
                    {
                        match = false;
                        break;
                    }
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
        ptr = new char[1];
        ptr[0] = '\0';
    }
};

int main()
{
    String string1("Test TEXT Asd TEXT Asd");
    string1.Print();

    string1.Remove("TEXT", "text123");
    string1.Print();

    cout << "Contains 'text123': " << (string1.Contains("Asd") ? "True" : "False") << endl;
    cout << "Contains 'Something': " << (string1.Contains("Something") ? "True" : "False") << endl;

    cout << "Count of 'Asd': " << string1.Count("Asd") << endl;

    string1.Insert(5, " Something ");
    string1.Print();
    

    return 0;
}