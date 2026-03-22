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
	string type;

public:
	Actor(string type = "Actor", string name = "Actor") : type(type), name(name) {}
	
	string getType()
	{
		return type;
	}
	string getName()
	{
		return name;
	}

};

class DroppedItem : public Actor
{
public:
	Item* item;
	int quantity;

	DroppedItem(Item* item, int quantity) : Actor("DroppedItem", "DroppedItem")
	{
		this->item = item;
		this->quantity = quantity;
	}
};

class Scene
{
	Actor** actors;
	int count;
	int SIZE;
	
public:

	Scene()
	{
		SIZE = 10;
		count = 0;
		actors = new Actor*[SIZE];
	}

	~Scene()
	{
		delete[] actors;
	}

	void AddActor(Actor* actor)
	{
		if (count >= SIZE)
		{
			SIZE *= 2;
			Actor** newArr = new Actor*[SIZE];

			for (int i = 0; i < count; i++)
			{
				newArr[i] = actors[i];
			}

			delete[] actors;
			actors = newArr;
		}
		actors[count++] = actor;
	}

	void RemoveActor(int index)
	{
		for (int i = index; i < count - 1; i++)
		{
			actors[i] = actors[i + 1];
		}
		count--;
	}

	Actor** getActors()
	{
		return actors;
	}
	int getActorsCount()
	{
		return count;
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
			scene->AddActor(new DroppedItem(item, quantity));
			cout << "Dropped " << name << " x" << quantity << endl;
		}
		else
		{
			cout << "No such item to drop!" << endl;
		}
	}
	
	void pickUpItem(const string& name)
	{
		Actor** actors = scene->getActors();
		int count = scene->getActorsCount();

		for (int i = 0; i < count; i++)
		{
			if (actors[i]->getType() == "DroppedItem")
			{
				DroppedItem* dropped = (DroppedItem*)actors[i];

				if (dropped->item->getName() == name)
				{
					inventory.addItem(dropped->item, dropped->quantity);

					scene->RemoveActor(i);

					cout << "Picked up " << name << " x" << dropped->quantity << endl;
					return;
				}
			}
		}
		cout << "No such item on the ground!" << endl;
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
	scene.getActors();
	cout << endl;

	FallenGod.pickUpItem("Steel Sword");
	cout << endl;
	FallenGod.showInventory();
	cout << endl;
	scene.getActors();

	return 0;
}