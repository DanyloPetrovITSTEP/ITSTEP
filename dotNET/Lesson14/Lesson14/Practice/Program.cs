using Lesson14.Practice;
using System;
using System.Text.Json;

Spaceship spaceship = new Spaceship()
{
    Name = "Explorer",
    Health = 100,
    Fuel = 100,
    Position = new Vector3D(0, 0, 0)
};

spaceship.AddCargo(new CargoItem("Food", 10, 2.5f));
spaceship.AddCargo(new CargoItem("Fuel Cells", 5, 4.0f));
spaceship.AddCargo(new CargoItem("Metal", 20, 1.5f));

spaceship.StartEngine();
spaceship.Move(3, 4, 0);

spaceship.TakeDamage(20);

Console.WriteLine("=== ORIGINAL SHIP ===");
Console.WriteLine(spaceship);

// ==========================

SpaceshipJsonDto jsonDto = new SpaceshipJsonDto(spaceship);

string json = JsonSerializer.Serialize(
    jsonDto,
    new JsonSerializerOptions { WriteIndented = true }
);

File.WriteAllText("spaceship.json", json);

Console.WriteLine("JSON saved successfully!");

// ==========================

spaceship.Name = "Modified Ship";
spaceship.Health = 10;
spaceship.Fuel = 5;

spaceship.StopEngine();

Console.WriteLine("\n=== MODIFIED ORIGINAL SHIP ===");
Console.WriteLine(spaceship);

// ==========================

string loadedJson = File.ReadAllText("spaceship.json");

SpaceshipJsonDto loadedJsonDto =
    JsonSerializer.Deserialize<SpaceshipJsonDto>(loadedJson)!;

Spaceship jsonShip = loadedJsonDto.Load();

Console.WriteLine("\n=== JSON LOADED SHIP ===");
Console.WriteLine(jsonShip);
