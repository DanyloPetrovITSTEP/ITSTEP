/*using System.Reflection;

namespace DotNetLessons;

[AttributeUsage(AttributeTargets.Method)]
public class CommandAttribute(string name) : Attribute
{
    public string Name { get; init; } = name;
}

public class CommandRegistry
{
    private readonly Dictionary<string, List<Action>> _commands = new();

    public void RegisterCommand(object target)
    {
        var targetType = target.GetType();

        foreach (var method in targetType.GetMethods())
        {
            var attribute = method.GetCustomAttribute<CommandAttribute>();
            if (attribute is null) continue;

            var action = Delegate.CreateDelegate(typeof(Action), target, method) as Action;

            if (action is not null)
            {
                if (_commands.TryGetValue(attribute.Name, out var commands))
                {
                    commands.Add(action);
                }
                else
                {
                    _commands.Add(attribute.Name, [action]);
                }
            }
        }
    }

    public void Execute(string commandName)
    {
        if (_commands.TryGetValue(commandName, out var actions))
        {
            foreach (var action in actions)
            {
                action();
            }
        }
        else
        {
            Console.WriteLine("Command not found: " + commandName);
        }
    }
}

public class GameObject
{
    public string Name { get; set; }
}

public class Character : GameObject
{
    public void Move()
    {
        Console.WriteLine("Character moving...");
    }

    [CommandAttribute("Character Help")]
    public void Help()
    {
        Console.WriteLine("Help");
    }
}

public class Game
{
    public CommandRegistry Commands { get; private set; }

    private List<GameObject> Objects { get; } = [];

    public void AddObject(GameObject obj)
    {
        Objects.Add(obj);
        Commands.RegisterCommand(obj);
    }

    public Game()
    {
        Commands = new CommandRegistry();
        Commands.RegisterCommand(this);
    }

    [CommandAttribute("Save Game")]
    public void Save()
    {
        Console.WriteLine("Saving...");
    }

    [CommandAttribute("Load Game")]
    public void Load()
    {
        Console.WriteLine("Loading...");
    }

    [CommandAttribute("Start Game")]
    public void StartGame()
    {
        Console.WriteLine("Starting game...");
    }
}
*/