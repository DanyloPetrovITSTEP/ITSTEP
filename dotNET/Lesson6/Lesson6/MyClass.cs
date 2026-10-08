using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Text;
using System.Xml.Linq;

/*Практика
Створіть консольну гру з персонажами та простою бойовою системою.

* Абстрактний клас Character: Name, Health, Damage, TakeDamage(), Attack().
* Створіть класи Warrior, Mage, Archer.
* Кожен клас повинен мати власну характеристику та власну реалізацію Attack().
* Використайте base у конструкторах або методах.
* Додайте клас Enemy, від якого наслідуються мінімум 2 типи противників.
* Один тип противника повинен мати перевизначений Attack().
* Створіть List<Character> і додайте туди об'єкти різних типів.
* У циклі викликайте Attack() через посилання типу Character.
* Реалізуйте атаку одного персонажа по іншому через Attack(Character target).
* Після атаки у цілі має зменшуватись Health.
* Додайте перевірку смерті персонажа.
* Використайте is або pattern matching для роботи з конкретним типом.
* Перевизначте ToString() для виводу стану персонажа.
* Один раз продемонструйте різницю між override і new.
* Додайте один sealed клас.
* Покажіть upcasting: Character character = new Mage(...).*/


namespace Lesson6
{
    public abstract class Character
    {
        public string Name { get; set; }
        public int Health { get; set; }
        public int Damage { get; set; }
        public Character(string name, int health, int damage)
        {
            Name = name;
            Health = health;
            Damage = damage;
        }
        public void ThrowIfDead()
        {
            if (Health <= 0) throw new InvalidOperationException($"{Name} is dead.");
        }

        public void TakeDamage(int damage)
        {
            ThrowIfDead();
            Health -= damage;
        }
        public abstract void Attack(Character target);

        public void Heal(int amount)
        {
            ThrowIfDead();
            Health += amount;
            if (Health > 100) Health = 100;
        }

        public virtual string GetDescription()
        {
            return $"{GetType().Name} '{Name}': HP={Health}, DMG={Damage}";
        }

        public override string ToString() => GetDescription();
    }

    class Warrior : Character
    {
        public Warrior(string name, int health, int damage) : base(name, health, damage) { }
        public override void Attack(Character target)
        {
            if (target == null) return;
            target.TakeDamage(this.Damage);
        }

        public override string GetDescription()
        {
            return $"Warrior {Name} (HP={Health}, DMG={Damage}) - brave fighter";
        }
    }

    class Archer : Character
    {
        public Archer(string name, int health, int damage) : base(name, health, damage) { }
        public override void Attack(Character target)
        {
            if (target == null) return;
            target.TakeDamage(this.Damage);
        }

        public new string GetDescription()
        {
            return $"Archer {Name} (HP={Health}, DMG={Damage}) - ranged attacker (hidden)"; // при використанні new, цей метод буде викликатися лише через Archer
        }
    }

    sealed class Mage : Character
    {
        public Mage(string name, int health, int damage) : base(name, health, damage) { }
        public override void Attack(Character target)
        {
            if (target == null) return;
            target.TakeDamage(this.Damage);
        }
    }



    class Enemy : Character
    {
        public Enemy(string name, int health, int damage) : base(name, health, damage) { }
        public override void Attack(Character target)
        {
            if (target == null) return;
            target.TakeDamage(this.Damage);
        }
    }

    class Ork : Enemy
    {
        public Ork(string name, int health, int damage) : base(name, health, damage) { }
        public override void Attack(Character target)
        {
            base.Attack(target);
        }
    }

    class Goblin : Enemy
    {
        public Goblin(string name, int health, int damage) : base(name, health, damage) { }
        public override void Attack(Character target)
        {
            base.Attack(target);
        }
        public void LifeSteal(Character target)
        {
            if (target == null) return;
            if (target.Health >= 20)
            {
                target.TakeDamage(15);
                this.Heal(15);
            }
        }
    }
}