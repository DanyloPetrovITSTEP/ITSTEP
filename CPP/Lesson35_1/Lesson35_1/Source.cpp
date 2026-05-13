#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

class player;

class hero
{
    int health_;
    int max_health_;
    int damage_;

public:
    int get_health() const { return health_; }
	int get_max_health() const { return max_health_; }
    int get_damage() const { return damage_; }

    virtual string get_name() const = 0;

    bool IsAlive() const { return health_ > 0; }

    hero(const int health, const int damage) : health_(health), max_health_(health), damage_(damage) {}
    virtual ~hero() = default;

    virtual void make_action(player* teammate, player* enemy, vector<string>& history) = 0;

    void damage(int value)
    {
        health_ -= value;

        if (health_ < 0)
        {
            health_ = 0;
        }
    }

    void heal(int value)
    {
        health_ += value;

        if (health_ > max_health_)
        {
            health_ = max_health_;
        }
    }
};

class player
{
    vector<hero*> heroes_;

public:
    template<typename T, typename... Args>
    void add_hero(Args&&... args)
    {
        hero* new_hero = new T(std::forward<Args>(args)...);

        heroes_.push_back(new_hero);
    }

    const vector<hero*>& get_heroes() const { return heroes_; }

    vector<hero*> get_alive_heroes() const
    {
        vector<hero*> alive_heroes;

        for (hero* hero : heroes_)
        {
            if (hero->IsAlive())
            {
                alive_heroes.push_back(hero);
            }
        }

        return alive_heroes;
    }

    vector<hero*> get_damaged_heroes() const
    {
        vector<hero*> damaged_heroes;

        for (hero* hero : heroes_)
        {
            if (hero->IsAlive() && hero->get_health() < hero->get_max_health())
            {
                damaged_heroes.push_back(hero);
            }
        }

        return damaged_heroes;
    }

    bool isDefeated() const
    {
        for (const hero* hero : heroes_)
        {
            if (hero->IsAlive())
            {
                return false;
            }
        }

        return true;
    }

    void clear_heroes()
    {
        for (const hero* hero : heroes_)
        {
            delete hero;
        }
    }

    virtual ~player()
    {
        clear_heroes();
    }

    void make_turn(player* enemy, vector<string>& history)
    {
        if (heroes_.empty())
        {
            return;
        }

        int heroes_count = heroes_.size();

        for (int i = 0; i < heroes_count; i++)
        {
            hero* current_hero = heroes_[0];

            heroes_.erase(heroes_.begin());
            heroes_.push_back(current_hero);

            if (!current_hero->IsAlive())
            {
                continue;
            }

            current_hero->make_action(this, enemy, history);
            return;
        }

        history.push_back("No heroes alive");
    }
};

class warrior : public hero
{
public:
    void make_action(player* teammate, player* enemy, vector<string>& history) override;
    
    virtual string get_name() const override { return "Warrior"; }

    warrior(const int health, const int damage) : hero(health, damage) {}
};

class mage : public hero
{
public:
    void make_action(player* teammate, player* enemy, vector<string>& history) override;

    virtual string get_name() const override { return "Mage"; }

    mage(const int health, const int damage) : hero(health, damage) {}
};

class robber : public hero
{
public:
    void make_action(player* teammate, player* enemy, vector<string>& history) override;

    virtual string get_name() const override { return "Robber"; }

    robber(const int health, const int damage) : hero(health, damage) {}
};


void PrintPlayer(const player& player, const string& player_name)
{
    cout << player_name << endl;

    for (const hero* hero : player.get_heroes())
    {
		cout << "  | " << hero->get_name() << " HP: " << hero->get_health() << "/" << hero->get_max_health() << " DMG: " << hero->get_damage() << endl;
    }

    cout << endl;
}

void PrintHistory(const vector<string>& history)
{
    cout << "History:" << endl;

    for (const string& event : history)
    {
        cout << " " << event << endl;
    }
}



void warrior::make_action(player* teammate, player* enemy, vector<string>& history)
{
    vector<hero*> targets = enemy->get_alive_heroes();

    if (targets.empty())
    {
        history.push_back("Warrior tried to attack, but found no enemies");
        return;
    }

    int random_index = rand() % targets.size();
    hero* target = targets[random_index];

    target->damage(get_damage());

    history.push_back("Warrior attacked " + target->get_name());
}

void mage::make_action(player* teammate, player* enemy, vector<string>& history)
{
    vector<hero*> targets = teammate->get_damaged_heroes();

    if (targets.empty())
    {
        history.push_back("Mage tried to heal, but no teammates were damaged");
        return;
    }

    int random_index = rand() % targets.size();
    hero* target = targets[random_index];

    target->heal(get_damage());

    history.push_back("Mage healed " + target->get_name());
}

void robber::make_action(player* teammate, player* enemy, vector<string>& history)
{
    vector<hero*> targets = enemy->get_alive_heroes();

    if (targets.empty())
    {
        history.push_back("Robber tried to attack, but found no enemies");
        return;
    }

    int random_index = rand() % targets.size();
    hero* target = targets[random_index];

    bool isInStealth = rand() % 2 == 0;

    if (isInStealth)
    {
        int buffed_damage = get_damage() * 3;

        target->damage(buffed_damage);

        history.push_back("Robber sneaked to " + target->get_name() + " and dealt buffed damage");
    }
    else
    {
        target->damage(get_damage());

        history.push_back("Robber was noticed by " + target->get_name() + " and dealt default damage");
    }
}

int main(int argc, char* argv[])
{
    srand(time(nullptr));

    player player_1;
    player_1.add_hero<warrior>(20, 6);
    player_1.add_hero<mage>(10, 5);
    player_1.add_hero<robber>(15, 3);

    player player_2;
    player_2.add_hero<warrior>(20, 6);
    player_2.add_hero<mage>(10, 5);
    player_2.add_hero<robber>(15, 3);

    vector<string> history;

    for (int i = 0; i < 10; i++)
    {
        system("cls");

        history.push_back("=== Tick " + to_string(i + 1) + " ===");

        history.push_back("Player 1 turn:");
        player_1.make_turn(&player_2, history);

        if (player_2.isDefeated())
        {
            history.push_back("Player 1 wins! All Player 2 heroes are defeated!");
			history.push_back("");

            PrintPlayer(player_1, "Player 1");
            PrintPlayer(player_2, "Player 2");
			PrintHistory(history);
            break;
        }

        history.push_back("Player 2 turn:");
        player_2.make_turn(&player_1, history);

        if (player_1.isDefeated())
        {
            history.push_back("Player 2 wins! All Player 1 heroes are defeated!");
            history.push_back("");

            PrintPlayer(player_1, "Player 1");
            PrintPlayer(player_2, "Player 2");
            PrintHistory(history);
            break;
        }

        history.push_back("");

        PrintPlayer(player_1, "Player 1");
        PrintPlayer(player_2, "Player 2");
        
        PrintHistory(history);

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
