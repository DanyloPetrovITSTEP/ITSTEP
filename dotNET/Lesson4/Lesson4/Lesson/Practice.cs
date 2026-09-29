using System;
using System.Collections.Generic;
using System.Security.Cryptography.X509Certificates;
using System.Text;

namespace Lesson4.Lesson
{
    internal class Practice
    {
        public enum AttributeBonusType
        {
            Add,
            Multiply,
        }

        public struct AttributeBonus
        {
            public string Tag;
            public AttributeBonusType Type;
            public double Value;
        }


        public class myAttribute(int baseValue)  // доречі, Attribute не дає використовувати, скаржиться що вже існує System.Attribute, тож довелося змінити назву
        {
            public double Value
            {
                get
                {
                    double result = BaseValue;

                    foreach (var bonus in Bonuses)
                    {
                        if (bonus.Type == AttributeBonusType.Add)
                        {
                            result += bonus.Value;
                        }
                    }

                    foreach (var bonus in Bonuses)
                    {
                        if (bonus.Type == AttributeBonusType.Multiply)
                        {
                            result *= bonus.Value;
                        }
                    }


                    if (MinValue != null && result < MinValue.Value)
                    {
                        result = MinValue.Value;
                    }

                    if (MaxValue != null && result > MaxValue.Value)
                    {
                        result = MaxValue.Value;
                    }


                    return result;
                }
            }

            public int BaseValue { get; set; } = baseValue;
            private List<AttributeBonus> Bonuses { get; } = [];

            public int? MinValue { get; set; }
            public int? MaxValue { get; set; }

            public void AddBonus(string tag, double value, AttributeBonusType type = AttributeBonusType.Add)
            {
                Bonuses.Add(new AttributeBonus { Tag = tag, Value = value, Type = type });
            }

            public void AddBonuses(params AttributeBonus[] bonuses)
            {
                foreach (var bonus in bonuses)
                {
                    Bonuses.Add(bonus);
                }
            }

            public void RemoveBonus(string tag)
            {
                var bonusesToRemove = Bonuses.ToList().Where(bonus => bonus.Tag == tag);

                foreach (var bonus in bonusesToRemove)
                {
                    Bonuses.Remove(bonus);
                }
            }

            public void AddToBaseValue(int value)
            {
                checked
                {
                    BaseValue += value;
                }
            }
        }

        public partial class Character(int health, int damage)
        {
            public myAttribute Health { get; private set; } = new(health) { MinValue = 0, MaxValue = health };
            public myAttribute Damage { get; private set; } = new(damage);

            public void Deconstruct(out double health, out double damage)
            {
                health = Health.Value;
                damage = Damage.Value;
            }

            public void TakeDamage(int value)
            {
                if (value < 0)
                {
                    throw new InvalidAttributeException("Damage", "Damage value cannot be negative");
                }

                Health.AddToBaseValue(-value);
            }
            public void Heal(int value)
            {
                if (value < 0)
                {
                    throw new InvalidAttributeException("Health", "Heal value cannot be negative");
                }

                Health.AddToBaseValue(value);
            }
        }

        public partial class Character
        {
            public override string ToString()
            {
                return $"{nameof(Health)}: {Health.Value}; {nameof(Damage)}: {Damage.Value}";
            }

            public void CharacterAttributesLog()
            {
                Console.WriteLine(ToString());
            }
        }

        public class InvalidAttributeException : Exception
        {
            public string AttributeName { get; }

            public InvalidAttributeException(string attributeName, string message) : base(message)
            {
                 AttributeName = attributeName;
            }
        }
    }
}


/*ЗАВДАННЯ 1 — params та Deconstruct
Додайте до Attribute метод AddBonuses(), який дозволяє передати довільну кількість бонусів за допомогою params.
Додайте до Character метод Deconstruct(), щоб персонажа можна було розкласти на поточні Health.Value та Damage.Value.

ЗАВДАННЯ 2 — partial
Розділіть клас Character на два: основна логіка та логування

ЗАВДАННЯ 3 — винятки
Створіть власний тип винятку InvalidAttributeException, успадкований від Exception.
TakeDamage() та Heal() не повинні приймати від'ємні значення.

ЗАВДАННЯ 4 — checked та unchecked
Додайте до Attribute метод: public void AddToBaseValue(int value)
Зміна BaseValue повинна виконуватися всередині checked, щоб переповнення int викликало OverflowException.

ЗАВДАННЯ 5 — фільтри винятків
Додайте до InvalidAttributeException інформацію про назву атрибута, наприклад public string AttributeName { get; }
У Program.cs обробіть InvalidAttributeException за допомогою двох catch з when AttributeName == "Health" та AttributeName == "Damage"*/