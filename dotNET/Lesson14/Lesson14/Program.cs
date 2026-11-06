/*using Lesson14;
using System.Numerics;
using System.Text.Json;

*//*Player palyer = new Player()
{
    Name = "Alex",
    //Level = 1,
    Health = 100,
};

palyer.Inventory.Slots[0] = "Apple"; 
palyer.Inventory.Slots[2] = "Pen"; 

string json = JsonSerializer.Serialize(palyer);

Console.WriteLine(json);
// {
//     "Name":"Palyer",
//     "Level":1,
//     "Health":100
// }

Player Des_Player = JsonSerializer.Deserialize<Player>(json);

Console.WriteLine(Des_Player.ToString());*//*

//////////////////

Player palyer = new Player()
{
    Name = "Alex",
    //Level = 1,
    Health = 100,
};

palyer.Inventory.Slots[0] = "Apple";
palyer.Inventory.Slots[2] = "Pen";

// Save
PlayerSaveData SaveData = new PlayerSaveData(palyer);
string JsonSave = JsonSerializer.Serialize(SaveData);
Console.WriteLine(JsonSave);

// Load
PlayerSaveData LoadedData = JsonSerializer.Deserialize<PlayerSaveData>(JsonSave);
Player LoadedPlayer = LoadedData.Load();
Console.WriteLine(LoadedPlayer.ToString());*/