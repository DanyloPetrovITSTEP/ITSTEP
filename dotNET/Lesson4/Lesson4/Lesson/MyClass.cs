// Core
partial class User
{
    public string Name { get; set; }
    public int Age {  get; set; }

    public User[] Friends { get; set; } = [];

    public void Deconstruct(out string outName, out int outAge)
    {
        // 1
        // => (outName, outAge) = (Name, Age);

        // 2
        outName = Name;
        outAge = Age;
    }

    User GetFriend(int index)
    {
        if (index >= Friends.Length)
        {
            throw new IndexOutOfRangeException();
        }

        return Friends[index];
    }
}

// Economy
partial class User
{
    public int Money;
    void Transfer(User user, int amount)
    {
        user.Money += amount;
        Money -= amount;
    }
}



/*class TestException : Exception
{
    public int Code { get; set; }

    public TestException(int code, string message) : base(message)
    {
        Code = code;
    }

    public TestException(int code) : base($"Something went wrong: {code}")
    {
        Code = code;
    }
}

throw new TestException(100, "Something went wrong");
throw new TestException(100);*/