#include <iostream>
#include <cstring>
using namespace std;


class String
{
	char* line;
	int length;

public:

	String() : line(nullptr), length(0) {}

	String(const char* Str)
	{
		if (Str != nullptr)
		{
			length = strlen(Str);
			line = new char[length + 1];
			strcpy(line, Str);
		}
		else
		{
			line = nullptr;
			length = 0;
		}
	}

	String(const String& other)
	{
		if (other.line != nullptr)
		{
			length = other.length;
			line = new char[length + 1];
			strcpy(line, other.line);
		}
		else
		{
			line = nullptr;
			length = 0;
		}
	}

	String(String&& other) noexcept
	{
		line = other.line;
		length = other.length;

		other.line = nullptr;
		other.length = 0;
	}

	~String()
	{
		delete[] line;
	}


	String operator+(const String& other) const //конкатенація
	{
		String temp;

		temp.length = length + other.length;
		temp.line = new char[temp.length + 1];

		for (int i = 0; i < length; i++)
		{
			temp.line[i] = line[i];
		}
		for (int j = 0; j < other.length; j++)
		{
			temp.line[length + j] = other.line[j];
		}
		temp.line[length + other.length] = '\0';

		return temp;
	}
	String& operator+=(const String& other) // додавання до поточного
	{
		char* new_line = new char[length + other.length + 1];

		for (int i = 0; i < length; i++)
		{
			new_line[i] = line[i];
		}
		for (int j = 0; j < other.length; j++)
		{
			new_line[length + j] = other.line[j];
		}

		new_line[length + other.length] = '\0';

		delete[] line;
		line = new_line;
		length += other.length;

		return *this;
	}
	String& operator=(const String& other) // Копіювання
	{
		if (this != &other)
		{
			delete[] line;

			if (other.line != nullptr)
			{
				length = other.length;
				line = new char[length + 1];
				strcpy(line, other.line);
			}
			else
			{
				line = nullptr;
				length = 0;
			}
		}

		return *this;
	}

	String& operator=(String&& other) noexcept
	{
		if (this != &other)
		{
			delete[] line;

			line = other.line;
			length = other.length;

			other.line = nullptr;
			other.length = 0;
		}
		return *this;
	}

	bool operator==(const String& other) const // Порівняння на рівність
	{
		if (line == nullptr && other.line == nullptr)
		{
			return true;
		}
		if (line == nullptr || other.line == nullptr)
		{
			return false;
		}

		return strcmp(line, other.line) == 0;
	}
	bool operator!=(const String& other) const // Порівняння на нерівність
	{
		return !(*this == other);
	}
	bool operator<(const String& other) const // лексикографічно менше
	{
		if (line == nullptr && other.line == nullptr)
		{
			return false;
		}
		if (line == nullptr)
		{
			return true;
		}
		if (other.line == nullptr) return false;

		return strcmp(line, other.line) < 0;
	}
	bool operator>(const String& other) const // лексикографічно більше
	{
		return other < *this;
	}

	char& operator[](int index) // для читання та запису символу
	{
		return line[index];
	}
	const char& operator[](int index) const // для константного об'єкта
	{
		return line[index];
	}

	bool operator!() const // повертає true, якщо рядок порожній
	{
		return length == 0;
	}
	operator const char* () const // дозволяє використовувати String там, де потрібний const char*
	{
		return line;
	}
};

ostream& operator<<(ostream& os, const String& s)
{
	os << (const char*)s;
	return os;
}


int main()
{




	return 0;
}