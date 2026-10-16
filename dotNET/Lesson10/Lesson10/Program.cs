using System;
using System.Collections;
using System.Collections.Generic;

public interface IItem
{
    string Name { get; }
}

public class Item : IItem
{
    public string Name { get; }

    public Item(string name)
    {
        Name = name;
    }

    public override string ToString()
    {
        return Name;
    }
}

public class Inventory<T> : IEnumerable<T>
{
    private readonly List<T> items = new();

    public int Count => items.Count;

    public T this[int index]
    {
        get => items[index];
        set => items[index] = value;
    }

    public void Add(T item)
    {
        items.Add(item);
    }

    public bool Remove(T item)
    {
        return items.Remove(item);
    }

    public IEnumerable<T> FindAll(Func<T, bool> predicate)
    {
        foreach (T item in items)
        {
            if (predicate(item))
            {
                yield return item;
            }
        }
    }

    public List<TResult> ConvertAll<TResult>(Func<T, TResult> converter)
    {
        List<TResult> result = new List<TResult>();

        foreach (T item in items)
        {
            result.Add(converter(item));
        }

        return result;
    }

    public IEnumerator<T> GetEnumerator()
    {
        return items.GetEnumerator();
    }

    IEnumerator IEnumerable.GetEnumerator()
    {
        return GetEnumerator();
    }
}

public class ItemInventory<T> : Inventory<T> where T : IItem
{
    public T? FindByName(string name)
    {
        foreach (T item in this)
        {
            if (item.Name == name)
            {
                return item;
            }
        }

        return default;
    }
}


public class Program
{
    public static void Main()
    {
        Item sword = new Item("Wooden Sword");
        Item shield = new Item("Shield");
        Item food = new Item("Meat");
        Item potion = new Item("Potion of Regeneration");
        Item armor = new Item("Steel Chestplate");

        ItemInventory<Item> inventory = new ItemInventory<Item>();

        inventory.Add(sword);
        inventory.Add(shield);
        inventory.Add(food);
        inventory.Add(potion);
        inventory.Add(armor);

        /////////////////////////////////////////////////////

        Console.WriteLine($"Amount of items in inventory: {inventory.Count}");

        bool removed = inventory.Remove(food);

        Console.WriteLine($"Removed {food.Name} from inventory: {removed}");
        Console.WriteLine($"Amount of items in inventory: {inventory.Count}");

        Console.WriteLine();/////////////////////////////////////////////////////

        Console.WriteLine("Items in inventory:");
        foreach (Item item in inventory)
        {
            Console.WriteLine(item);
        }

        Console.WriteLine();/////////////////////////////////////////////////////

        Console.WriteLine($"First item in inventory: {inventory[0]}");
        inventory[0] = new Item("Iron Sword");
        Console.WriteLine($"First item in inventory after replace: {inventory[0]}");

        Console.WriteLine();/////////////////////////////////////////////////////

        Console.WriteLine("Items in inventory that containing \"Sword\" in their name:");
        foreach (Item item in inventory.FindAll(item => item.Name.Contains("Sword")))
        {
            Console.WriteLine(item);
        }

        Console.WriteLine();/////////////////////////////////////////////////////

        List<string> itemNames = inventory.ConvertAll(item => item.Name);
        Console.WriteLine("Item names in inventory:");
        foreach (string name in itemNames)
        {
            Console.WriteLine(name);
        }

        Console.WriteLine();/////////////////////////////////////////////////////

        Console.WriteLine("Searching for Shield:");
        Item? foundItem = inventory.FindByName("Shield");

        if (foundItem != null)
        {
            Console.WriteLine($"Found item: {foundItem.Name}");
        }
        else
        {
            Console.WriteLine("Item not found");
        }






        Console.WriteLine();/////////////////////////////////////////////////////

        Console.WriteLine("List");

        List<Item> itemList = new List<Item>();

        itemList.Add(new Item("Magic Wand"));
        itemList.Add(new Item("Book of spells"));
        itemList.Add(new Item("Amulet of Fire"));

        foreach (Item item in itemList)
        {
            Console.WriteLine(item);
        }

        Console.WriteLine();/////////////////////////////////////////////////////

        Console.WriteLine("Queue");

        Queue<Item> itemQueue = new Queue<Item>();

        itemQueue.Enqueue(new Item("First"));
        itemQueue.Enqueue(new Item("Second"));
        itemQueue.Enqueue(new Item("Third"));

        while (itemQueue.Count > 0)
        {
            Console.WriteLine(itemQueue.Dequeue());
        }
    }
}