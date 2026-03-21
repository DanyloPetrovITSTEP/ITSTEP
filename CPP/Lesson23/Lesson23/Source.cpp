#include <iostream>
#include <string>
using namespace std;

class Item
{
	string name;

public:
	Item(string name) : name(name) {}

	string getName() const
	{
		return name;
	}
};

class ItemSlot
{
public:
	Item* item;
	int quantity;

	ItemSlot() : item(nullptr), quantity(0) {}
};

class Inventory
{
	int maxSlots;
	ItemSlot* slots;

public:

	Inventory(int size = 20)
	{
		maxSlots = size;
		slots = new ItemSlot[maxSlots];
	}

	~Inventory()
	{
		delete[] slots;
	}

	bool addItem(Item* item, int quantity = 1)
	{

		for (int i = 0; i < maxSlots; i++)
		{
			if (slots[i].item != nullptr && slots[i].item->getName() == item->getName())
			{
				slots[i].quantity += quantity;
				return true;
			}
		}

		for (int i = 0; i < maxSlots; i++)
		{
			if (slots[i].item == nullptr)
			{
				slots[i].item = item;
				slots[i].quantity = quantity;

				return true;
			}
		}

		cout << "Inventory is full!" << endl;
		return false;
	}

	bool dropItem(const string& name, Item*& droppedItem, int quantity = 1)
	{
		for (int i = 0; i < maxSlots; i++)
		{
			if (slots[i].item != nullptr && slots[i].item->getName() == name)
			{
				slots[i].quantity -= quantity;
				droppedItem = slots[i].item;

				if (slots[i].quantity <= 0)
				{
					slots[i].item = nullptr;
					slots[i].quantity = 0;
				}
				return true;
			}
		}
		return false;
	}

	void showInventory()
	{
		for (int i = 0; i < maxSlots; i++)
		{
			if (slots[i].item != nullptr)
			{
				cout << "* " << slots[i].item->getName() << " x" << slots[i].quantity << endl;
			}
		}
	}
};

class Actor
{
protected:
	string name;
	static int counter;

public:
	Actor()
	{
		counter++;
		name = "Actor" + to_string(counter); // ³äåÿ - ìîÿ, ðåàë³çàö³ÿ - ÃåÏåÒå
	}
	Actor(string name) : name(name) {}

	string getName()
	{
		return name;
	}
};
int Actor::counter = 0;

class DroppedItem : public Actor
{
public:
	Item* item;
	int quantity;

	DroppedItem() : item(nullptr), quantity(0) {}
	DroppedItem(Item* item, int quantity, string name = "DroppedItem") : Actor(name)
	{
		this->item = item;
		this->quantity = quantity;
	}
};

class Scene
{
	DroppedItem* DroppedItems;
	int DroppedCount = 0;
	int SIZE;
	
public:

	Scene()
	{
		SIZE = 10;
		DroppedCount = 0;
		DroppedItems = new DroppedItem[SIZE];
	}

	~Scene()
	{
		delete[] DroppedItems;
	}

	void addDroppedItem(Item* item, int quantity)
	{
		if (DroppedCount >= SIZE)
		{
			SIZE *= 2;
			DroppedItem* newArr = new DroppedItem[SIZE];

			for (int i = 0; i < DroppedCount; i++)
			{
				newArr[i] = DroppedItems[i];
			}

			delete[] DroppedItems;
			DroppedItems = newArr;
		}

		DroppedItems[DroppedCount++] = DroppedItem(item, quantity);
	}

	bool pickUpItem(const string& name, Item*& item, int& quantity)
	{
		for (int i = 0; i < DroppedCount; i++)
		{
			if (DroppedItems[i].item->getName() == name)
			{
				item = DroppedItems[i].item;
				quantity = DroppedItems[i].quantity;

				for (int j = i; j < DroppedCount - 1; j++)
				{
					DroppedItems[j] = DroppedItems[j + 1];
				}

				DroppedCount--;
				return true;
			}
		}
		cout << "There is no such item on the ground!" << endl;
		return false;
	}

	void showDroppedItems()
	{
		if (DroppedCount == 0)
		{
			cout << "There's nothing on the ground!" << endl;
			return;
		}

		cout << "Items on the ground: " << endl;
		for (int i = 0; i < DroppedCount; i++)
		{
			cout << "* " << DroppedItems[i].item->getName() << " x" << DroppedItems[i].quantity << endl;
		}
	}
};

class Character : public Actor
{
	Inventory inventory;
	Scene* scene;

public:
	Character(string name, Scene* scene) : Actor(name)
	{
		this->scene = scene;
	}

	void showInventory()
	{
		cout << name << "'s inventory: " << endl;
		inventory.showInventory();
	}

	void dropItem(const string& name, int quantity = 1)
	{
		Item* item;

		if (inventory.dropItem(name, item, quantity))
		{
			scene->addDroppedItem(item, quantity);
			cout << "Dropped " << name << " x" << quantity << endl;
		}
		else
		{
			cout << "No such item to drop!" << endl;
		}
	}
	
	void pickUpItem(const string& name)
	{
		Item* item;
		int quantity;

		if (scene->pickUpItem(name, item, quantity))
		{
			inventory.addItem(item, quantity);
			cout << "Picked up " << name << " x" << quantity << endl;
		}
	}

	Inventory& getInventory()
	{
		return inventory;
	}
};

int main()
{
	Scene scene;
	
	Item sword("Steel Sword");
	Item axe("Vibranium Battle Axe");
	Item food("Mivina");

	Character FallenGod("Fallen God", &scene);

	FallenGod.getInventory().addItem(&sword);
	FallenGod.getInventory().addItem(&axe);
	FallenGod.getInventory().addItem(&food, 5);

	FallenGod.showInventory();
	cout << endl;

	FallenGod.dropItem("Steel Sword");
	cout << endl;
	FallenGod.showInventory();
	cout << endl;
	scene.showDroppedItems();
	cout << endl;

	FallenGod.pickUpItem("Steel Sword");
	cout << endl;
	FallenGod.showInventory();
	cout << endl;
	scene.showDroppedItems();

	return 0;
}