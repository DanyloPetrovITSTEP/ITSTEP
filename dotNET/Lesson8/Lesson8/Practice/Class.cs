using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text;

namespace Lesson8.Practice
{
    public enum BonusType
    {
        Add,
        Multiply
    }

    public class AttributeBonus
    {
        public BonusType Type { get; }
        public float Value { get; }

        public AttributeBonus(BonusType type, float value)
        {
            Type = type;
            Value = value;
        }
    }

    public class Attribute
    {
        private float _baseValue;

        public float BaseValue
        {
            get => _baseValue;
            set
            {
                float oldValue = Value;
                _baseValue = value;
                NotifyOnValueChanged(oldValue);
            }
        }

        public List<AttributeBonus> Bonuses { get; } = new();

        public float? MinValue { get; set; }
        public float? MaxValue { get; set; }

        public float Value
        {
            get
            {
                float result = BaseValue;

                foreach (AttributeBonus bonus in Bonuses)
                {
                    if (bonus.Type == BonusType.Add)
                    {
                        result += bonus.Value;
                    }
                }

                foreach (AttributeBonus bonus in Bonuses)
                {
                    if (bonus.Type == BonusType.Multiply)
                    {
                        result *= bonus.Value;
                    }
                }

                if (MinValue.HasValue && result < MinValue.Value)
                {
                    result = MinValue.Value;
                }

                if (MaxValue.HasValue && result > MaxValue.Value)
                {
                    result = MaxValue.Value;
                }

                return result;
            }
        }

        public event Action<float, float>? OnValueChanged;
        public event Action<AttributeBonus>? OnBonusAdded;
        public event Action<AttributeBonus>? OnBonusRemoved;

        public Attribute(float baseValue, float? minValue = null, float? maxValue = null)
        {
            _baseValue = baseValue;
            MinValue = minValue;
            MaxValue = maxValue;
        }

        private void NotifyOnValueChanged(float oldValue)
        {
            float newValue = Value;

            if (oldValue != newValue)
            {
                OnValueChanged?.Invoke(oldValue, newValue);
            }
        }

        public void AddBonus(AttributeBonus bonus)
        {
            float oldValue = Value;

            Bonuses.Add(bonus);
            OnBonusAdded?.Invoke(bonus);

            NotifyOnValueChanged(oldValue);
        }

        public bool RemoveBonus(AttributeBonus bonus)
        {
            int index = Bonuses.IndexOf(bonus);

            if (index < 0)
                return false;

            float oldValue = Value;

            Bonuses.RemoveAt(index);
            OnBonusRemoved?.Invoke(bonus);

            NotifyOnValueChanged(oldValue);
            return true;
        }
    }

    public class Character
    {
        public Attribute Health { get; } = new Attribute(100f, 0f, 100f);
        public Attribute Stamina { get; } = new Attribute(100f, 0f, 100f);
        public Attribute Strength { get; } = new Attribute(10f, 0f);

        public event Action? OnDead;
        public event Action? OnExhausted;

        public Character()
        {
            Health.OnValueChanged += (oldValue, newValue) =>
            {
                Console.WriteLine($"Health: {oldValue} => {newValue}");

                if (oldValue > 0f && newValue == 0f)
                {
                    OnDead?.Invoke();
                }
            };

            Stamina.OnValueChanged += (oldValue, newValue) =>
            {
                Console.WriteLine($"Stamina: {oldValue} => {newValue}");

                if (oldValue > 0f && newValue == 0f)
                {
                    OnExhausted?.Invoke();
                }
            };

            Strength.OnValueChanged += (oldValue, newValue) =>
            {
                Console.WriteLine($"Strength: {oldValue} => {newValue}");
            };
        }

        public void TakeDamage(float damage)
        {
            if (damage < 0f)
            {
                throw new ArgumentOutOfRangeException(nameof(damage));
            }

            Health.BaseValue -= damage;
        }

        public void UseStamina(float amount)
        {
            if (amount < 0f)
            {
                throw new ArgumentOutOfRangeException(nameof(amount));
            }

            Stamina.BaseValue -= amount;
        }

        public void AddStrengthBonus(AttributeBonus bonus)
        {
            Strength.AddBonus(bonus);
        }
    }
}