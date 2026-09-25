namespace Lesson3.Lesson;

public enum AttributeBonusType
{
    Add,
    Multiply,
}

struct AttributeBonus
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
    public void RemoveBonus(string tag)
    {
        var bonusesToRemove = Bonuses.ToList().Where(bonus => bonus.Tag == tag);

        foreach (var bonus in bonusesToRemove)
        {
            Bonuses.Remove(bonus);
        }
    }
}

public class Character(int health, int damage)
{
    public myAttribute Health { get; private set; } = new(health) { MinValue = 0, MaxValue = health };
    public myAttribute Damage { get; private set; } = new(damage);

    public override string ToString()
    {
        return $"{nameof(Health)}:{Health.Value}; {nameof(Damage)}:{Damage.Value}";
    }

    public void TakeDamage(int value) => Health.BaseValue -= value;
    public void Heal(int value) => Health.BaseValue += value;
}
