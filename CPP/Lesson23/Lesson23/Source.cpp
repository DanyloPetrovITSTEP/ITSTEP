#include <iostream>
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

class Inventory
{
	struct ItemStack
	{
		Item* item;
		int quantity;
	};

	static const int maxSlots = 20;
	ItemStack items[maxSlots];
	int count = 0;

public:

	bool addItem(Item* item, int quantity = 1)
	{

		for (int i = 0; i < count; i++)
		{
			if (items[i].item->getName() == item->getName())
			{
				items[i].quantity += quantity;
				return true;
			}
		}

		if (count < maxSlots)
		{
			items[count].item = item;
			items[count].quantity = quantity;
			count++;
			return true;
		}
		else
		{
			cout << "Inventory is full!" << endl;
			return false;
		}
	}

	bool dropItem(const string& name)
	{
		for (int i = 0; i < count; i++)
		{
			if (items[i].item->getName() == name)
			{
				items[i].quantity--;

				if (items[i].quantity <= 0)
				{
					for (int j = i; j < count - 1; j++)
					{
						items[j] = items[j + 1];
					}
					count--;
				}
				return true;
			}
		}
		return false;
	}

	void showInventory()
	{
		cout << "Inventory:" << endl;
		for (int i = 0; i < count; i++)
		{
			cout << "* " << items[i].item->getName() << " x" << items[i].quantity << endl;
		}
	}

	bool isHasItem(const string& name)
	{
		for (int i = 0; i < count; i++)
		{
			if (items[i].item->getName() == name)
			{
				return true;
			}
		}
		return false;
	}

	Item* getItemPointer(const string& name)
	{
		for (int i = 0; i < count; i++)
		{
			if (items[i].item->getName() == name)
			{
				return items[i].item;
			}
		}

		return nullptr;
	}
};

class droppedItem
{
public:
	Item* item;
	int quantity;

	droppedItem() : item(nullptr), quantity(0) {}
	droppedItem(Item* item, int quantity) : item(item), quantity(quantity) {}
};

class Scene
{
	droppedItem* droppedItems = nullptr;
	int droppedCount = 0;
	int arraySize;
	
public:

	~Scene()
	{
		delete[] droppedItems;
	}

	void addDroppedItem(Item* item, int quantity = 1)
	{
		if (droppedCount >= arraySize)
		{
			int newArraySize = (arraySize == 0) ? 20 : arraySize * 2;
			droppedItem* newArray = new droppedItem[newArraySize];

			for (int i = 0; i < droppedCount; i++)
			{
				newArray[i] = droppedItems[i];
			}

			delete[] droppedItems;
			droppedItems = newArray;
			arraySize = newArraySize;
		}

		droppedItems[droppedCount++] = droppedItem(item, quantity);
	}

	bool pickUpItem(const string& name, Inventory& invent)
	{
		for (int i = 0; i < droppedCount; i++)
		{
			if (droppedItems[i].item->getName() == name)
			{
				if (invent.addItem(droppedItems[i].item, droppedItems[i].quantity))
				{
					for (int j = i; j < droppedCount - 1; j++)
					{
						droppedItems[j] = droppedItems[j + 1];
					}
					droppedCount--;
					return true;
				}
				else
				{
					return false;
				}
			}
		}
		cout << "There is no such item on the ground!" << endl;
		return false;
	}

	void getDroppedItems()
	{
		if (droppedCount == 0)
		{
			cout << "There is nothing on the ground" << endl;
		}
		else
		{
			cout << "Items on the ground:" << endl;
			for (int i = 0; i < droppedCount; i++)
			{
				cout << "* " << droppedItems[i].item->getName() << " x" << droppedItems[i].quantity << endl;
			}
		}
	}
};

class Character
{
	string name;
	float health;
	Inventory inventory;
	Scene* scene = nullptr;

public:
	Character(string name, float health, Scene* scene = nullptr) : name(name), health(health), scene(scene) {}

	Inventory& getInventory()
	{
		return inventory;
	}

	void dropItem(const string& name)
	{
		if (inventory.dropItem(name))
		{
			Item* itemPtr = inventory.getItemPointer(name);
			if (scene && itemPtr)
			{
				scene->addDroppedItem(itemPtr, 1);
			}
		}
		else
		{
			cout << this->name << " dont have " << name << " to drop!" << endl;
		}
	}
	
	void pickUpItem(const string& name)
	{
		if (scene &&scene->pickUpItem(name, inventory))
		{
			cout << name << " picked up" << endl;
		}
	}

	void getInfo()
	{
		cout << name << " | " << health << " HP" << endl;
		inventory.showInventory();
	}
};

int main()
{
	Scene scene;
	
	Item sword("Steel Sword");
	Item axe("Vibranium Battle Axe");
	Item food("Mivina");

	Character FallenGod("Fallen God", 200, &scene);

	FallenGod.getInventory().addItem(&sword);
	FallenGod.getInventory().addItem(&axe);
	FallenGod.getInventory().addItem(&food, 5);

	FallenGod.getInfo();

	FallenGod.dropItem("Steel Sword");
	FallenGod.getInfo();
	scene.getDroppedItems();

	FallenGod.pickUpItem("Steel Sword");
	FallenGod.getInfo();
	scene.getDroppedItems();

	return 0;
}