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
    public int Value;
}


public class Attribute(int baseValue)
{
    public int Value
    {
        get
        {
            int result = BaseValue;

            foreach (var bonus in Bonuses)
            {
                if (bonus.Type == AttributeBonusType.Add)
                {
                    result += bonus.Value;
                }
                else if (bonus.Type == AttributeBonusType.Multiply)
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

    public void AddBonus(string tag, int value, AttributeBonusType type = AttributeBonusType.Add)
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
    public Attribute Health { get; private set; } = new(health) { MinValue = 0, MaxValue = health };
    public Attribute Damage { get; private set; } = new(damage);

    public override string ToString()
    {
        return $"{nameof(Health)}:{Health.Value}; {nameof(Damage)}:{Damage.Value}";
    }

    public void TakeDamage(int value) => Health.BaseValue -= value;
    public void Heal(int value) => Health.BaseValue += value;
}
