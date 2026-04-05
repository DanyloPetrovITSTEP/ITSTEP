#include <iostream>

using namespace std;

class Texture
{
	char* buffer;
	int size;

public:

	Texture(int size)
	{
		this->size = size;
		buffer = new char[size];

		cout << "Texture constructor" << endl;
	}

	Texture(const Texture& other)
	{
		size = other.size;
		buffer = new char[size];

		for (int i = 0; i < size; i++)
		{
			buffer[i] = other.buffer[i];
		}

		cout << "Texture copy constructor" << endl;
	}

	Texture(Texture&& other)
	{
		buffer = other.buffer;
		size = other.size;

		other.buffer = nullptr;
		other.size = 0;

		cout << "Texture move constructor" << endl;
	}

	Texture& operator=(const Texture& other)
	{
		if (this == &other) { return *this; }

		delete[] buffer;

		size = other.size;
		buffer = new char[size];

		for (int i = 0; i < size; i++)
		{
			buffer[i] = other.buffer[i];
		}

		return *this;
	}

	Texture& operator=(Texture&& other)
	{
		if (this == &other) { return *this; }

		delete[] buffer;

		size = other.size;
		buffer = other.buffer;

		other.size = 0;
		other.buffer = nullptr;


		return *this;
	}

	~Texture()
	{
		delete[] buffer;
	}
};

class Material
{
	Texture texture;
	string name;

public:

	Material() : texture(16), name("default")
	{
		cout << "Material default constructor" << endl;
	}
	
	Material(int textureSize, const string& name) : texture(textureSize), name(name)
	{
		cout << "Material constructor" << endl;
	}

	Material(const Material& other) : texture(other.texture), name(other.name)
	{
		cout << "Material copy constructor" << endl;
	}

	Material(Material&& other) : texture(move(other.texture)), name(move(other.name))
	{
		cout << "Material move constructor" << endl;
	}

	Material& operator=(const Material& other) noexcept
	{
		if (this == &other) { return *this; }

		texture = other.texture;
		name = other.name;

		return *this;
	}

	Material& operator=(Material&& other) noexcept
	{
		if (this == &other) { return *this; }

		texture = std::move(other.texture);
		name = std::move(other.name);

		return *this;
	}
};

class MaterialContainer
{
	Material** arr;
	int count;
	int bufferSize;

public:

	MaterialContainer()
	{
		
		count = 0;
		bufferSize = 10;
		arr = new Material * [bufferSize] {};

		cout << "MaterialContainer constructor" << endl;
	}

	void addMaterial(const Material& material)
	{
		if (count >= bufferSize)
		{
			cout << "Old array size is " << bufferSize << endl;

			Material** new_arr = new Material*[bufferSize + 3];

			for (int i = 0; i < count; i++)
			{
				new_arr[i] = arr[i];
			}

			delete[] arr;
			arr = new_arr;
			bufferSize += 3;

			cout << "New array size is " << bufferSize << endl;
		}

		arr[count++] = new Material(material);
	}

	void RemoveMaterial()
	{
		if (count == 0)
		{
			return;
		}

		delete arr[count - 1];
		count--;

		if (bufferSize - count >= 3)
		{
			cout << "Old array size is " << bufferSize << endl;

			Material** new_arr = new Material*[bufferSize - 3];

			for (int i = 0; i < count; i++)
			{
				new_arr[i] = arr[i];
			}

			delete[] arr;
			arr = new_arr;
			bufferSize -= 3;

			cout << "New array size is " << bufferSize << endl;
		}
	}

	~MaterialContainer()
	{
		for (int i = 0; i < count; i++)
		{
			delete arr[i];
		}

		delete[] arr;
	}
};



int main()
{



	return 0;
}