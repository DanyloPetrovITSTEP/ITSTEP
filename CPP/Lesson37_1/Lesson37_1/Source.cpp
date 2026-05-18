#include <functional>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

template <typename... Args>
class Event
{
    using Handler = function<void(Args...)>;

    vector<Handler> handlers;

public:
    void Subscribe(Handler handler)
    {
        handlers.push_back(std::move(handler));
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
    Event<bool> aliveChanged;
    Event<int> healthChanged;

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
        healthChanged.Subscribe(updateAlive);
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