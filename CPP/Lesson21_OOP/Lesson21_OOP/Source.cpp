#include <iostream>
#include <string>
using namespace std;

class character
{
	string name;
	float health;
	float max_health;
	bool is_dead;
	void UpdateIsDead() {
		this->is_dead = getHealth() <= 0;
		if (is_dead) {
			cout << this->name << " has died!" << endl;
		}
	}
public:
	character(string name, float health)
	{
		this->name = name;
		this->health = health;
		UpdateIsDead();
	}

	void getinfo()
	{
		cout << "Name: " << name << "; Health: " << health << "/" << max_health << ";\n";
	}
	float getHealth() {
		return health;
	}
	void setHealth(float health) {
		this->health = health;
		if (health < 0) {
			this->health = 0;
		}
		if (health > max_health) {
			this->health = max_health;
		}
		UpdateIsDead();
	}
	void heal(float heal) {
		setHealth(getHealth() + heal);
	}
	void damage(float damage) {
		setHealth(getHealth() - damage);
	}
	string getName() {
		return name;
	}
};



class warrior :public character
{
	float strength;
public:
	void attack(character* victim)
	{
		victim->damage(strength);
	}
	float getDamage() {
		return strength;
	}
	warrior(string name, float health, float strength) : character(name, health) {
		this->strength = strength;

	}
	void getinfo()
	{
		cout << "Name: " << getName() << "; Health: " << getHealth() << "; Strength: " << getDamage() << ";\n";
	}
};



class zealot :public character
{
	float mana;
public:
	void heal(character* target, float heal)
	{
		if (heal > mana) {
			cout << "Not enough mana!" << endl;
			return;
		}
		target->heal(heal);
		this->mana -= heal;
	}
	float getMana() {
		return mana;
	}
	void getinfo()
	{
		cout << "Name: " << getName() << "; Health: " << getHealth() << "; Mana: " << getMana() << ";\n";
	}
	zealot(string name, float health, float mana) : character(name, health) {
		this->mana = mana;
	}
};



int main()
{
	warrior w1("uno", 100, 150);
	warrior w2("dos", 100, 30);
	zealot zealot1("tres", 100, 10);
	w1.getinfo();
	cout << endl;
	w2.getinfo();
	cout << "--------------------" << endl;
	w1.attack(&w2);
	w2.attack(&w1);
	w1.getinfo();
	cout << endl;
	w2.getinfo();
	cout << "--------------------" << endl;
	zealot1.getinfo();
	zealot1.heal(&w1, 5);
	cout << endl;
	w1.getinfo();
	cout << "--------------------" << endl;
	zealot1.getinfo();


	return 0;
}