#include <functional>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

template <typename... Args>
class event
{
    using handler = function<void(Args...)>;

    vector<handler> handlers_;

public:
	template <typename T>
    void subscribe(shared_ptr<T> owner, handler handler)
    {
        weak_ptr<T> weak_owner = owner;

        handlers_.push_back([weak_owner, handler](Args... args)
        {
            if (auto locked = weak_owner.lock())
            {
                    handler(args...);
			}
        });
    }


    void Notify(Args... args)
    {
        for (auto& handler : handlers)
        {
            handler(args...);
        }
    }
};

class Warrior
{
    int health;
    int maxHealth;

    bool isAlive;

    void setAlive(bool value)
    {
        if (isAlive == value) return;

        isAlive = value;
        aliveChanged.Notify(isAlive);
    }

public:
    event<bool> aliveChanged;
    event<int> healthChanged;

    void setHealth(int health)
    {
        this->health = health;
        healthChanged.Notify(health);
    }

    int getHealth() const
    {
        return this->health;
    }

    bool IsAlive() const
    {
        return isAlive;
    }


    Warrior(int health)
    {
        this->maxHealth = this->health = health;

        auto updateAlive = [this](int health)
            {
                setAlive(health > 0);
            };

        updateAlive(health);
        healthChanged.subscribe(make_shared(this), updateAlive);
    }

    void Damage(int value)
    {
        setHealth(getHealth() - value);
    }


    void Foo(int value)
    {
        //...
    }
};

int main()
{
    Warrior warrior(10);

    warrior.aliveChanged.Subscribe([](bool value)
        {
            if (value == false)
            {
                cout << "Warrior dead" << endl;
            }
        });

    /*Warrior warrior_1(10);

    {
        Warrior warrior_2(10);

        warrior_1.aliveChanged.Subscribe(warrior_2.Foo); // Will be runtime error
    }*/

    return 0;
}