/*void Print(params string[] values)
{
    foreach (var value in values)
    {
        Console.WriteLine(value);
    }
}

Print("1, 2, 3", "4, 5, 6", "Hello there!");

User user_1 = new User();

user_1.Name = "John Doe";
user_1.Age = 18;

// string tempName = user_1.Name;
// int tempAge

var (tempName, tempAge) = user_1;



int[] arr = new int[] { 1, 2, 3 };

bool TestFoo()
{
    try
    {
        Console.WriteLine(arr[3]);
        return true;
    }
    catch (Exception e)
    {
        Console.WriteLine(e);
        return false;
    }
    finally
    {
        Console.WriteLine("Press any key to exit.");
        Console.ReadKey();
    }
}


int i = int.MaxValue;
// 1111 1111

i++; // 1111 1111 -> trying to increase -> 1111 1110 -> ... -> 0000 0000

Console.WriteLine(i);


int i = int.MaxValue;

checked
{
    i++; // error
}

unchecked
{
    i++;
}

Console.WriteLine(i);



try
{
    // ping google.com/....
}
// 4xx
catch (HttpRequestException e) when ((int?)e.StatusCode >= 400 && (int?)e.StatusCode < 500)
{

}
// 5xx
catch (HttpRequestException e) when ((int?)e.StatusCode >= 500 && (int?)e.StatusCode < 600)
{

}
catch (Exception e)
{
    Console.WriteLine(e);
}

// HttpRequestException // 200 201 404 501 502
*/


using Lesson4.Lesson;

var hero = new Practice.Character(100, 20);

hero.CharacterAttributesLog();

hero.Damage.AddBonuses(
    new Practice.AttributeBonus
    {
        Tag = "Sword",
        Type = Practice.AttributeBonusType.Add,
        Value = 10
    },
    new Practice.AttributeBonus
    {
        Tag = "Potion",
        Type = Practice.AttributeBonusType.Multiply,
        Value = 1.5
    }
);

var (health, damage) = hero;

/*Console.WriteLine($"Health: {health}");
Console.WriteLine($"Damage: {damage}");*/

hero.CharacterAttributesLog();

try
{
    hero.TakeDamage(-10);
}
catch (Practice.InvalidAttributeException ex) when (ex.AttributeName == "Health")
{
    Console.WriteLine($"Health error: {ex.Message}");
}
catch (Practice.InvalidAttributeException ex) when (ex.AttributeName == "Damage")
{
    Console.WriteLine($"Damage error: {ex.Message}");
}