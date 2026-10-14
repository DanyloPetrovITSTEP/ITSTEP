using Lesson8.Practice;
using System;
using System.Collections.Generic;
using System.Text;
using static System.Net.Mime.MediaTypeNames;

public class Program
{
    public static void Main()
    {
        Character character = new Character();

        character.OnDead += () => Console.WriteLine("Character is dead!");

        character.OnExhausted += () => Console.WriteLine("Character is exhausted!");

        character.Strength.OnBonusAdded += bonus => Console.WriteLine($"Added strength bonus: {bonus.Type}, {bonus.Value}");

        character.Strength.OnBonusRemoved += bonus => Console.WriteLine($"Removed strength bonus: {bonus.Type}, {bonus.Value}");

        PrintAttributes(character);


        AttributeBonus addBonus =
            new AttributeBonus(BonusType.Add, 5f);

        AttributeBonus multiplyBonus =
            new AttributeBonus(BonusType.Multiply, 2f);

        character.AddStrengthBonus(addBonus);
        character.AddStrengthBonus(multiplyBonus);

        Console.WriteLine($"Strength: {character.Strength.Value}");

        character.Strength.BaseValue = 15f;

        character.Strength.RemoveBonus(addBonus);

        Console.WriteLine($"Strength after removal: {character.Strength.Value}");


        Lesson8.Practice.Attribute testAttribute = new Lesson8.Practice.Attribute(50f, 0f, 100f);

        testAttribute.OnValueChanged += (oldValue, newValue) => Console.WriteLine($"Test attribute: {oldValue} -> {newValue}");

        testAttribute.BaseValue = 150f;
        Console.WriteLine($"MaxValue: {testAttribute.Value}");

        testAttribute.BaseValue = -20f;
        Console.WriteLine($"MinValue: {testAttribute.Value}");


        character.TakeDamage(30f);
        character.TakeDamage(40f);
        character.TakeDamage(30f);

        character.UseStamina(40f);
        character.UseStamina(60f);

        character.TakeDamage(10f);
        character.UseStamina(10f);

        PrintAttributes(character);
    }

    private static void PrintAttributes(Character character)
    {
        Console.WriteLine($"Health: {character.Health.Value}");
        Console.WriteLine($"Stamina: {character.Stamina.Value}");
        Console.WriteLine($"Strength: {character.Strength.Value}");
    }
}

/*Модуль 8. Практичне завдання — Атрибути персонажа та події

Завдання 1. Система атрибутів

Створити клас Attribute, який містить:
-BaseValue(float) — базове значення.
-Bonuses — колекція бонусів.
-MinValue, MaxValue(float ?) — необов'язкові обмеження.
- Value (float) — обчислюване значення з урахуванням бонусів та обмежень.

Створити тип AttributeBonus:
-Type — Add або Multiply.
- Value (float) — величина бонусу.

Формула розрахунку: (BaseValue + сума Add) × добуток Multiply. Після розрахунку застосовуються MinValue та MaxValue, якщо вони задані.

Реалізувати методи додавання та видалення бонусів.

Додати події:
-OnValueChanged(float oldValue, float newValue) — коли змінюється підсумкове значення атрибута.
- OnBonusAdded(AttributeBonus bonus) — коли додано бонус.
- OnBonusRemoved(AttributeBonus bonus) — коли видалено бонус.

Події мають викликатися автоматично при відповідних змінах. OnValueChanged не повинен викликатися, якщо підсумкове значення залишилося незмінним.

Завдання 2. Персонаж

Створити клас Character із трьома атрибутами:
-Health — здоров'я (0–100).
- Stamina — витривалість (0–100).
- Strength — сила (мінімум 0).

Реалізувати методи:
-TakeDamage(float damage) — зменшує базове здоров'я.
- UseStamina(float amount) — витрачає витривалість.
- AddStrengthBonus(AttributeBonus bonus) — додає бонус до сили.

Персонаж повинен підписуватися на події своїх атрибутів та мати власні події:
-OnDead — здоров'я змінилося з додатного значення на 0.
- OnExhausted — витривалість змінилася з додатного значення на 0.

Завдання 3. Демонстрація

У Program.cs:
-Створити персонажа.
- Підписатися на всі події персонажа та виводити повідомлення в консоль.
- Додати декілька бонусів різних типів.
- Продемонструвати зміну BaseValue, додавання та видалення бонусів.
- Продемонструвати роботу MinValue та MaxValue.
- Завдати персонажу шкоди до смерті.
- Витратити всю витривалість.
- Змінити силу за допомогою бонусів.

Вимоги:
-Використовувати делегати, події та лямбда-вирази.
- Не викликати події персонажа безпосередньо з Program.cs.
- Не допускати повторного виклику OnDead та OnExhausted без переходу значення вище 0.
- Всі обчислення виконувати з типом float.*/