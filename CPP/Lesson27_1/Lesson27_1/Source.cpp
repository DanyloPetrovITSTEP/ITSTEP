#include <iostream>

using namespace std;

class Vector2D
{
	float x = 0, y = 0;

public:

	float getX() const { return x; }
	float getY() const { return y; }
	void setX(float x) { this->x = x; }
	void setY(float y) { this->y = y; }

	Vector2D() : x(0), y(0) {}
	Vector2D(float x, float y) : x(x), y(y) {}
	Vector2D(const Vector2D& other) : x(other.x), y(other.y) {}

	Vector2D& operator=(const Vector2D& other)
	{
		x = other.x;
		y = other.y;

		return *this;
	}
	
	bool operator==(const Vector2D& other) const
	{
		return x == other.x && y == other.y;
	}

	bool operator!=(const Vector2D& other) const
	{
		//return (*this == other);
		return x != other.x && y != other.y;
	}


	Vector2D operator+(const Vector2D& other) const
	{
		return Vector2D(x + other.x, y + other.y);
	}

	Vector2D operator-(const Vector2D& other) const
	{
		return Vector2D(x - other.x, y - other.y);
	}

	Vector2D operator*(const Vector2D& other) const
	{
		return Vector2D(x * other.x, y * other.y);
	}

	Vector2D operator*(const int other) const
	{
		return Vector2D(x * other, y * other);
	}

	Vector2D operator/(const Vector2D& other) const
	{
		return Vector2D(x / other.x, y / other.y);
	}


	Vector2D operator++()
	{
		x++;
		y++;

		return *this;
	}

	Vector2D operator++(int)
	{
		Vector2D temp = *this;
		x++;
		y++;

		return temp;
	}

	Vector2D operator--()
	{
		x--;
		y--;

		return *this;
	}

	Vector2D operator--(int)
	{
		Vector2D temp = *this;
		x--;
		y--;

		return temp;
	}

	Vector2D& operator+=(const Vector2D& other)
	{
		return *this = *this + other;
	}

	Vector2D& operator-=(const Vector2D& other)
	{
		return *this = *this - other;
	}

	
};

ostream& operator<<(ostream& os, const Vector2D& v)
{
	os << v.getX() << ' ' << v.getY();
	return os;
}

class Matrix
{
	int size;
	Vector2D* vectors;

public:

	int getSize() const { return size; }
	Vector2D* getVector(int index) const
	{
		if (index < 0 || index >= size) return nullptr;

		return &vectors[index];
	}

	Vector2D& operator[](int index) const
	{
		return vectors[index];
	}

	Matrix(int size)
	{
		if (size <= 0) return;

		this->size = size;
		vectors = new Vector2D[size];
	}

	~Matrix()
	{
		delete[] vectors;
	}
};

ostream& operator<<(ostream& os, const Matrix& m)
{
	for (int i = 0; i < m.getSize(); i++)
	{
		os << m[4];
	}
}

int main()
{
	Vector2D vector_1(10, 5);
	Vector2D vector_2(10, 5);

	if (vector_1 == vector_2)
	{
		cout << "Vectors are same" << endl;
	}

	Vector2D vector_3 = vector_1 + vector_2;
	cout << "Vector_3: " << vector_3.getX() << ":" << vector_3.getY() << endl;
	

	vector_1 = vector_2 = vector_3;


	// << >>
	cout << vector_3;

	return 0;
}