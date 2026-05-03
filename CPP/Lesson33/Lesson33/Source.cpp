#include <chrono>
#include <iostream>
#include <map>
#include <thread>
#include <vector>
#include <string>

using namespace std;

class Character;

struct EffectContext
{
    int duration;

    EffectContext(int inDuration)
    {
        duration = inDuration;
    }

    virtual ~EffectContext() = default;
};

class Effect
{
    Character* owner;
    int duration;
    int lasted;

    bool ended = false;

protected:
    virtual void OnTick() {}
    virtual void OnEnd() {}

public:
    Character* GetOwner() const { return owner; }

    bool IsEnded() const { return ended; }

    Effect(Character* inOwner, const EffectContext& inContext)
    {
        owner = inOwner;
        duration = inContext.duration;
        lasted = 0;
    }

    void End()
    {
        if (ended) return;

        ended = true;

        OnEnd();
    }

    virtual ~Effect()
    {
        End();
    }

    void Tick()
    {
        if (IsEnded()) return;

        if (duration <= lasted)
        {
            End();
            return;
        }

        OnTick();
        ++lasted;
    }
};


class Item
{
    
public:

    virtual string GetName() const
    {
        return "Item";
    }

    virtual void Use(Character* owner, Character* target = nullptr) {}

    virtual bool IsConsumable() const { return false; }

	virtual ~Item() = default;
};


struct CharacterContext
{
    int health = 0;
    int stamina = 0;
    int mana = 0;
    int damage = 0;
    int hunger = 0;
};

class Character
{
    map<string, float> properties;

    vector<Effect*> effects;
    vector<Item*> items;

public:
    float& Property(const string& name) { return properties[name]; }

    Character(const CharacterContext& inContext)
    {
        Property("Vitality.Health.Value") = Property("Vitality.Health.Max") = inContext.health;
        Property("Vitality.Stamina.Value") = Property("Vitality.Stamina.Max") = inContext.stamina;
        Property("Vitality.Mana.Value") = Property("Vitality.Mana.Max") = inContext.mana;
		Property("Vitality.Hunger.Value") = Property("Vitality.Hunger.Max") = inContext.hunger;
        Property("Vitality.Damage.Value") = inContext.damage;
    }

    ~Character()
    {
        for (Effect* effect : effects)
        {
            delete effect;
        }

        for (Item* item : items)
        {
            delete item;
        }
    }

    void Tick()
    {
        for (Effect* effect : effects)
        {
            effect->Tick();

            if (effect->IsEnded())
            {
                delete effect;

                std::erase(effects, effect);
            }
        }

        if (Property("Vitality.Hunger.Value") > 0)
        {
            --Property("Vitality.Hunger.Value");
        }
        else
        {
            Property("Vitality.Hunger.Value") = 0;
        }
    }

    template <typename T>
        requires std::derived_from<T, Effect>
    void AddEffect(const EffectContext& inContext)
    {
        effects.push_back(new T(this, inContext));
    }

    void AddItem(Item* item)
    {
        items.push_back(item);
	}

    void UseItem(int index, Character* target = nullptr)
    {
        if (index < 0 || index >= items.size()) return;

        items[index]->Use(this, target);

        if (items[index]->IsConsumable())
        {
            delete items[index];
            items.erase(items.begin() + index);   // чесно, скористався підказкою ШІ
        }
	}

    void ShowInventory() const
    {
        cout << "Inventory: " << endl;

        for (int i = 0; i < items.size(); i++)
        {
            cout << "[" << i << "] " << items[i]->GetName() << endl;
        }
    }

    void Print() const
    {
        for (const auto& property : properties)
        {
            cout << " * " << property.first << " - " << property.second << '\n';
        }
    }
};

struct StrengthEffectContext : EffectContext
{
    int bonus = 0;

    StrengthEffectContext(int inDuration, int inBonus) : EffectContext(inDuration)
    {
        bonus = inBonus;
    }
};

class StrengthEffect : public Effect
{
    int bonus = 0;

public:
    StrengthEffect(Character* inOwner, const EffectContext& inContext) : Effect(inOwner, inContext)
    {
        const StrengthEffectContext& castedContext = static_cast<const StrengthEffectContext&>(inContext);

        bonus = castedContext.bonus;

        GetOwner()->Property("Vitality.Damage.Bonus") += bonus;
    }

    void OnEnd() override
    {
        GetOwner()->Property("Vitality.Damage.Bonus") -= bonus;
    }

    ~StrengthEffect() override = default;
};

struct HealingEffectContext : EffectContext
{
    int heal = 0;
    bool instantHeal = false;

    HealingEffectContext(int inDuration, int inHeal, bool inInstantHeal = false) : EffectContext(inDuration)
    {
        heal = inHeal;
		instantHeal = inInstantHeal;
    }
};

class HealingEffect : public Effect
{
    int heal = 0;
	bool instantHeal = false;

public:

    HealingEffect(Character* inOwner, const EffectContext& inContext) : Effect(inOwner, inContext)
    {
        const HealingEffectContext& castedContext = static_cast<const HealingEffectContext&>(inContext);
		
        heal = castedContext.heal;
		instantHeal = castedContext.instantHeal;

        if (instantHeal)
        {
            GetOwner()->Property("Vitality.Health.Value") += heal;

            if (GetOwner()->Property("Vitality.Health.Value") > GetOwner()->Property("Vitality.Health.Max"))
            {
				GetOwner()->Property("Vitality.Health.Value") = GetOwner()->Property("Vitality.Health.Max");
            }
        }
    }

    void OnTick() override
    {
        if (instantHeal) return;

		GetOwner()->Property("Vitality.Health.Value") += heal;

        if (GetOwner()->Property("Vitality.Health.Value") > GetOwner()->Property("Vitality.Health.Max"))
        {
			GetOwner()->Property("Vitality.Health.Value") = GetOwner()->Property("Vitality.Health.Max");
        }
    }

    ~HealingEffect() override = default;
};

struct FireEffectContext : EffectContext
{
    int damage = 0;

    FireEffectContext(int inDuration, int inDamage) : EffectContext(inDuration)
    {
        damage = inDamage;
    }
};

class FireEffect : public Effect
{
    int damage = 0;

public:

    FireEffect(Character* inOwner, const EffectContext& inContext) : Effect(inOwner, inContext)
    {
        const FireEffectContext& castedContext = static_cast<const FireEffectContext&>(inContext);
        
        damage = castedContext.damage;
	}

    void OnTick() override
	{
        GetOwner()->Property("Vitality.Health.Value") -= damage;
        
        if (GetOwner()->Property("Vitality.Health.Value") < 0)
        {
            GetOwner()->Property("Vitality.Health.Value") = 0;
        }
    }

	~FireEffect() override = default;
};


class Potion : public Item
{
    int heal = 0;

public:

    Potion(int inHeal)
    {
        heal = inHeal;
    }

    string GetName() const override
    {
        return "Potion of instant heal";
    }

    void Use(Character* owner, Character* target = nullptr) override
    {
        owner->AddEffect<HealingEffect>(HealingEffectContext(0, heal, true));
    }

    bool IsConsumable() const override { return true; }
};

class Food : public Item
{
    int hunger = 0;
    int heal = 0;
    int duration = 0;

public:

    Food(int inHunger, int inHeal, int inDuration)
    {
        hunger = inHunger;
        heal = inHeal;
        duration = inDuration;
    }

    string GetName() const override
    {
        return "Food"; 
    }

    void Use(Character* owner, Character* target = nullptr) override
    {
        owner->Property("Vitality.Hunger.Value") += hunger;

        if (owner->Property("Vitality.Hunger.Value") > owner->Property("Vitality.Hunger.Max"))
        {
            owner->Property("Vitality.Hunger.Value") = owner->Property("Vitality.Hunger.Max");
        }

        owner->AddEffect<HealingEffect>(HealingEffectContext(duration, heal));
    }

    bool IsConsumable() const override { return true; }
};

class Sword : public Item
{
    int damage = 0;
    bool hasFireAspect = false; // Ніби воно так називається в майнкрафті :D
    int fireDamage = 2;
    int fireDuration = 6;

public:

    Sword(int inDamage, bool hasFireAspect = false)
    {
        damage = inDamage;

        if (hasFireAspect)
        {
            this->hasFireAspect = hasFireAspect;
        }
    }

    string GetName() const override
    {
        if (hasFireAspect)
        {
            return "Sword with Fire Aspect enhancement";
        }

        return "Sword";
    }

    void Use(Character* owner, Character* target = nullptr) override
    {
        if (target == nullptr) return;

        target->Property("Vitality.Health.Value") -= damage + owner->Property("Vitality.Damage.Value") + owner->Property("Vitality.Damage.Bonus");

        if (target->Property("Vitality.Health.Value") < 0)
        {
            target->Property("Vitality.Health.Value") = 0;
        }

        if (hasFireAspect && target->Property("Vitality.Health.Value") > 0)
        {
            target->AddEffect<FireEffect>(FireEffectContext(fireDuration, fireDamage));
        }
    }
};


int main(int argc, char* argv[])
{
    CharacterContext characterContext;
    characterContext.health = 100;
    characterContext.stamina = 100;
    characterContext.mana = 100;
    characterContext.hunger = 100;
    characterContext.damage = 10;

    Character* character = new Character(characterContext);

    character->AddItem(new Potion(25));
    character->AddItem(new Food(10, 2, 5));
    character->AddItem(new Sword(6, true));


    CharacterContext enemyContext;
    enemyContext.health = 80;
    enemyContext.stamina = 100;
    enemyContext.mana = 50;
    enemyContext.hunger = 100;
    enemyContext.damage = 5;

    Character* enemy = new Character(enemyContext);

    enemy->AddItem(new Sword(5));

    for (int i = 0; i < 120; i++)
    {
        /*if (i == 5)
        {
            character->AddEffect<StrengthEffect>(StrengthEffectContext(10, 5));
        }

        if (i == 10)
        {
            character->AddEffect<FireEffect>(FireEffectContext(5,7));
        }

        if (i == 20)
        {
            character->AddEffect<HealingEffect>(HealingEffectContext(0, 25, true));
        }

        if (i == 30)
        {
            character->AddEffect<HealingEffect>(HealingEffectContext(5, 4));
        }*/

        if (i == 5)
        {
            character->UseItem(2, enemy);
        }
        
        if (i == 10)
        {
            enemy->UseItem(0, character);
        }

        if (i == 15)
        {
            character->UseItem(0);
        }

        if (i == 20)
        {
            enemy->UseItem(0, character);
        }

        if (i == 25)
        {
            character->UseItem(0);
        }


        character->Tick();
        enemy->Tick();

        system("cls");
        cout << "Character property (" << i << "): " << '\n';
        character->Print();
        character->ShowInventory();

        cout << "Enemy property (" << i << "): " << endl;
        enemy->Print();


        std::this_thread::sleep_for(std::chrono::seconds(1));
    }


    delete character;
    delete enemy;

    return 0;
}