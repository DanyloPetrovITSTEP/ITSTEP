using Lesson6;

List<Character> characters = new List<Character>
{
    new Warrior("Warrior_1", 100, 15),
    new Archer("Archer_1", 90, 12),
    new Mage("Mage_1", 80, 20),
    new Goblin("Goblin_1", 50, 10),
    new Ork("Ork_1", 120, 18)
};

Character upcasted = new Mage("Mage_2", 70, 25);
characters.Add(upcasted);

Console.WriteLine("Initial state:");
foreach (var c in characters)
    Console.WriteLine(c);

Console.WriteLine();

Character archerAsChar = new Archer("Archer_2", 85, 11);
Console.WriteLine("GetDescription via Character reference: " + archerAsChar.GetDescription());
var archerConcrete = (Archer)archerAsChar;
Console.WriteLine("GetDescription via Archer reference: " + archerConcrete.GetDescription());

Console.WriteLine();

for (int i = 0; i < characters.Count - 1; i++)
{
    var attacker = characters[i];
    var target = characters[i + 1];
    try
    {
        attacker.Attack(target);
        Console.WriteLine($"{attacker.Name} attacked {target.Name}");
    }
    catch (InvalidOperationException ex)
    {
        Console.WriteLine("Action failed: " + ex.Message);
    }

    if (target is Goblin g)
    {
        Console.WriteLine($"{g.Name} uses LifeSteal on {attacker.Name}");
        g.LifeSteal(attacker);
    }
}

Console.WriteLine();
Console.WriteLine("After combat:");
foreach (var ch in characters)
    Console.WriteLine(ch);