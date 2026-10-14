/*Character character = new Character { Health = 100 };

Action<int, int> messageHealthUpdate = (oldHealh, newHealth) =>
{
    Console.WriteLine($"Health: {oldHealh} -> {newHealth}");
};

Action<int, int> messageDead = (oldHealh, newHealth) =>
{
    Console.WriteLine($"Character is dead");
};

character.Damage(10);

character.OnHealthChanged += messageHealthUpdate;
character.OnDead += messageDead;

character.Damage(10);
character.Damage(10);
character.Damage(10);
character.Damage(10);
character.Damage(10);
character.Damage(10);

character.OnHealthChanged -= messageHealthUpdate;

character.Damage(10);
character.Damage(10);
character.Damage(10);











public delegate void MyDelegate(string message);

static class Logger
{
    public static void LogMessage(string message)
    {
        Console.WriteLine($"Message: {message}");
    }

    public static void LogWarning(string message)
    {
        Console.WriteLine($"Warning: {message}");
    }

    public static void LogError(string message)
    {
        Console.WriteLine($"Error: {message}");
    }
}


static class Calculator
{
    public delegate int Operation(int a, int b);

    public static int Calculate(int a, int b, Operation operation)
    {
        return operation(a, b);
    }

    public static int Add(int a, int b)
    {
        return a + b;
    }

    public static int Multiply(int a, int b)
    {
        return a * b;
    }
}

public delegate void Notification(string message);

public static class Send
{
    public static void Email(string message)
    {
        Console.WriteLine($"Email sent: {message}");
    }

    public static void SMS(string message)
    {
        Console.WriteLine($"SMS sent: {message}");
    }
}



public class Program
{
    public static void Main(string[] args)
    {
        MyDelegate handler = Logger.LogMessage;

        handler += Logger.LogWarning;

        handler("This is a message.");

        ////////////////

        Console.WriteLine(Calculator.Calculate(1, 2, Calculator.Add));

        ////////////////

        Notification? notification = null;

        notification += Send.Email;
        notification += Send.SMS;

        if (notification != null)
        {
            notification("Some message");
        }

        notification?.Invoke("Some Message");

        ////////////////

        foreach (var notify in notification.GetInvocationList())
        {
            Console.WriteLine($"Method: {notify.Method.Name}");
        }

        ////////////////

        //Action<int>
        Func<int, int, int> Test = Calculator.Add;
        //Predicate<string>

        ////////////////

        MessageHandler someHandler = delegate (string message)
        {
            Console.WriteLine("-------");
            Console.WriteLine(message);
            Console.WriteLine("-------");

        };

        someHandler("Some message");


        string Separator = "==========";

        Action<string> Message = static (string message) =>
        {
            //Console.WriteLine(Separator);
            Console.WriteLine(message);
            //Console.WriteLine(Separator);
        };

        Message("Hello World!");


        Func<int, int, bool> isSame = (int a, int b) => a == b;

        if (isSame(1, 1))
        {
            Console.WriteLine("Same");
        }
    }
}*/