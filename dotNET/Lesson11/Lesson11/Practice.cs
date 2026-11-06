
using System;
using System.Collections.Generic;
using System.Linq;

List<Game> games =
[
    new(1, "Ashen Depths", "RPG", 49, 91, ["Singleplayer", "Loot", "Bosses"]),
    new(2, "Iron Arena", "Action", 30, 77, ["Multiplayer", "PvP"]),
    new(3, "Forestbound", "Survival", 24, 86, ["Co-op", "Crafting"]),
    new(4, "Neon Run", "Action", 19, 82, ["Singleplayer", "Roguelike"]),
    new(5, "Crystal Tactics", "Strategy", 40, 88, ["Turn-based", "Singleplayer"]),
    new(6, "Dungeon Forge", "RPG", 35, 90, ["Co-op", "Loot"]),
    new(7, "Star Drifter", "Survival", 55, 79, ["Space", "Co-op"]),
    new(8, "Tiny Kingdom", "Strategy", 15, 75, ["Turn-based", "Casual"]),
    new(9, "Hollow Circuit", "Action", 29, 92, ["Roguelike", "Bosses"]),
    new(10, "Mythbound", "RPG", 60, 94, ["Open World", "Bosses"])
];

List<Purchase> purchases =
[
    new(1, 1, "Anna", 2),
    new(2, 1, "Oleg", 1),
    new(3, 3, "Ira", 3),
    new(4, 6, "Anna", 2),
    new(5, 9, "Max", 1),
    new(6, 10, "Ira", 1),
    new(7, 3, "Oleg", 2),
    new(8, 2, "Max", 1)
];

// Виконуйте завдання тут.

var result = games
    .Where(g => g.Genre == "RPG" && g.Price > 30)
    .Select(g => g.Name);

foreach (var name in result)
{
    Console.WriteLine(name);
}

Console.WriteLine();////////////////////////////////////////////////////////////

var sortedGames = games
    .OrderBy(g => g.Genre)
    .ThenByDescending(g => g.Rating);

foreach (var game in sortedGames)
{
    Console.WriteLine($"{game.Genre} | {game.Name} | {game.Rating}");
}

Console.WriteLine();////////////////////////////////////////////////////////////

var secondPage = games
    .OrderBy(g => g.Id)
    .Skip(3)
    .Take(3);

foreach (var game in secondPage)
{
    Console.WriteLine($"{game.Id}. {game.Name}");
}

Console.WriteLine();////////////////////////////////////////////////////////////

int count = games.Count(g => g.Price <= 30);

double averageRating = games
    .Where(g => g.Price <= 30)
    .Average(g => g.Rating);

Console.WriteLine($"Amount of games: {count}");
Console.WriteLine($"Average rating: {averageRating}");

Console.WriteLine();////////////////////////////////////////////////////////////

var cheapGame = games.FirstOrDefault(g => g.Price < 20);
var gameById = games.SingleOrDefault(g => g.Id == 8);

Console.WriteLine($"First game cheapier than 20: {cheapGame?.Name ?? "Not found"}");
Console.WriteLine($"Game with Id = 8: {gameById?.Name ?? "Not found"}");

Console.WriteLine();////////////////////////////////////////////////////////////

bool hasPvP = games.Any(g => g.Tags.Contains("PvP"));
bool allRatingsAbove70 = games.All(g => g.Rating > 70);

Console.WriteLine($"There is a game with the PvP tag: {hasPvP}");
Console.WriteLine($"All ratings are above 70: {allRatingsAbove70}");

Console.WriteLine();////////////////////////////////////////////////////////////

List<Game> rpgGames = games
    .Where(g => g.Genre == "RPG")
    .ToList();

Game[] cheapGames = games
    .Where(g => g.Price < 30)
    .ToArray();

Console.WriteLine("Games of genre RPG:");
foreach (var game in rpgGames)
{
    Console.WriteLine(game.Name);
}

Console.WriteLine("\nGames cheapier than 30:");
foreach (var game in cheapGames)
{
    Console.WriteLine($"{game.Name} — {game.Price}");
}

Console.WriteLine();////////////////////////////////////////////////////////////

var groups = games.GroupBy(g => g.Genre);

foreach (var group in groups)
{
    Console.WriteLine($"Жанр: {group.Key}");

    foreach (var game in group)
    {
        Console.WriteLine($"  {game.Name}");
    }
}

Console.WriteLine();////////////////////////////////////////////////////////////

var genreStats = games
    .GroupBy(g => g.Genre)
    .Select(group => new
    {
        Genre = group.Key,
        Count = group.Count(),
        TotalPrice = group.Sum(g => g.Price),
        AverageRating = group.Average(g => g.Rating)
    });

foreach (var stat in genreStats)
{
    Console.WriteLine(
        $"{stat.Genre}: games — {stat.Count}, " +
        $"total price — {stat.TotalPrice}, " +
        $"average rating — {stat.AverageRating:F1}");
}

var uniqueTags = games
    .SelectMany(g => g.Tags)
    .Distinct();

Console.WriteLine("\nUnique tags:");

foreach (var tag in uniqueTags)
{
    Console.WriteLine(tag);
}

Console.WriteLine();////////////////////////////////////////////////////////////

var purchaseDetails = purchases.Join(
    games,
    p => p.GameId,
    g => g.Id,
    (p, g) => new
    {
        Buyer = p.Buyer,
        GameName = g.Name,
        Copies = p.Copies,
        TotalPrice = g.Price * p.Copies
    });

foreach (var item in purchaseDetails)
{
    Console.WriteLine(
        $"{item.Buyer} | {item.GameName} | " +
        $"{item.Copies} copies | {item.TotalPrice}");
}



public record Game(
    int Id,
    string Name,
    string Genre,
    decimal Price,
    int Rating,
    string[] Tags
);

public record Purchase(
    int Id,
    int GameId,
    string Buyer,
    int Copies
);
