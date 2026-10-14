/*Створіть клас Money, який представляє грошову суму.
Клас повинен містити:
Amount — сума грошей (decimal).
Конструктор для ініціалізації суми.
Перевизначений метод ToString().

Реалізуйте перевантаження:
+ — додавання двох сум. (та унарный)
- — віднімання двох сум. (та унарный)
* — множення суми на число.
	/ — ділення суми на число.
++ — збільшення суми на 1.
-- — зменшення суми на 1.
== та != — перевірка рівності сум.
>, <, >=, <= — порівняння сум.
! — повертає true, якщо сума дорівнює нулю.
true — сума вважається істинною, якщо вона більша за нуль.
false — сума вважається хибною, якщо вона менша або дорівнює нулю.
implicit — перетворення int у Money.
explicit — перетворення Money у decimal.*/


using System;
public class Money
{
    public decimal Amount { get; private set; }

    public Money(decimal amount)
    {
        Amount = amount;
    }

    public override string ToString()
    {
        return $"{Amount}$";
    }


    public static Money operator +(Money m) => new Money(+m.Amount);
    public static Money operator -(Money m) => new Money(-m.Amount);

    public static Money operator +(Money m1, Money m2) => new Money(m1.Amount + m2.Amount);
    public static Money operator -(Money m1, Money m2) => new Money(m1.Amount - m2.Amount);
    public static Money operator *(Money m, decimal mult) => new Money(m.Amount * mult);
    public static Money operator /(Money m, decimal div) => new Money(m.Amount / div);

    public static Money operator ++(Money m) => new Money(m.Amount + 1);
    public static Money operator --(Money m) => new Money(m.Amount - 1);

    public static bool operator ==(Money m1, Money m2) => m1.Amount == m2.Amount;
    public static bool operator !=(Money m1, Money m2) => !(m1 == m2);
    public static bool operator >(Money m1, Money m2) => m1.Amount > m2.Amount;
    public static bool operator <(Money m1, Money m2) => m1.Amount < m2.Amount;
    public static bool operator >=(Money m1, Money m2) => m1.Amount >= m2.Amount;
    public static bool operator <=(Money m1, Money m2) => m1.Amount <= m2.Amount;

    public static bool operator !(Money m) => m.Amount != 0;
    public static bool operator true(Money m) => m.Amount > 0;
    public static bool operator false(Money m) => m.Amount <= 0;

    public static implicit operator Money(int amount) => new Money(amount);
    public static explicit operator decimal(Money m) => m.Amount;

}

public class Program
{
    public static void Main()
    {
        Money balance = new Money(321.99m);

        Console.WriteLine($"Balance: {balance}");

        if(balance)
        {
            Console.WriteLine("True");
        }
        else
        {
            Console.WriteLine("False");
        }


        balance = -balance;
        Console.WriteLine(balance);

        if (balance)
        {
            Console.WriteLine("True");
        }
        else
        {
            Console.WriteLine("False");
        }
    }
}