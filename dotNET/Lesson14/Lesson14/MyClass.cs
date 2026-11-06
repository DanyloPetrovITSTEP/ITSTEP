/*using System.Text.Json.Serialization;

namespace Lesson14;

public class Inventory
{
    public static int DefaultSize = 5;

    public string[] Slots { get; set; } = new string[DefaultSize];
}

public class Player
{
    public string Name { get; set; } = "";

    public Inventory Inventory { get; set; } = new Inventory();

    private int Level;

    public int Health { get; set; }

    public override string ToString()
    {
        return $"{Name}: Level - {Level}; Health - {Health}";
    }
}

// DTO
public record PlayerSaveData
{
    public string Name { get; set; }
    public string[] Items { get; set; }

    public PlayerSaveData() { }

    public PlayerSaveData(Player player)
    {
        Name = player.Name;
        Items = new string[player.Inventory.Slots.Length];

        for (int i = 0; i < Items.Length; i++)
        {
            Items[i] = player.Inventory.Slots[i];
        }
    }

    public Player Load()
    {
        Player player = new Player()
        {
            Name = Name
        };

        player.Inventory.Slots = new string[Items.Length];
        for (int i = 0; i < Items.Length; i++)
        {
            player.Inventory.Slots[i] = Items[i];
        }

        return player;
    }
}

*/