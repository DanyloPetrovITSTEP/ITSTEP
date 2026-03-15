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
		this->max_health = health;
		UpdateIsDead();
	}

	void getInfo()
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
	float getMaxHealth()
	{
		return max_health;
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
	void getInfo()
	{
		cout << "Name: " << getName() << "; Health: " << getHealth() << "; Strength: " << getDamage() << "; Class: Warrior" << endl;
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
	void getInfo()
	{
		cout << "Name: " << getName() << "; Health: " << getHealth() << "; Mana: " << getMana() << "; Class: Zealot" << endl;
	}
	zealot(string name, float health, float mana) : character(name, health) {
		this->mana = mana;
	}
};


class necromancer :public character
{
	float mana;
public:
	void revive(character* target)
	{
		if (target->getHealth() > 0)
		{
			cout << "Revive target is not dead!" << endl;
			return;
		}

		if (mana < 10)
		{
			cout << "Not enough mana!" << endl;
			return;
		}

		target->setHealth(target->getMaxHealth() * 0.15f);
		mana -= 10;

		cout << target->getName() << " has been revived by " << getName() << "!" << endl;
	}
	
	float getMana() {
		return mana;
	}

	void getInfo()
	{
		cout << "Name: " << getName() << "; Health: " << getHealth() << "; Mana: " << getMana() << "; Class: Necromancer" << endl;
	}

	necromancer(string name, float health, float mana) : character(name, health)
	{
		this->mana = mana;
	}
};


class thief : public warrior
{
public:
	thief(string name, float health, float strength) : warrior(name, health, strength) {}
	
	void lifeSteal(character* target)
	{
		float damage = getDamage() * 0.5f;
		float oldHealth = target->getHealth();
		target->damage(damage);
		float realDamage = oldHealth - target->getHealth();
		heal(realDamage);
		cout << getName() << " stole " << realDamage << " HP from " << target->getName() << "!" << endl;
	}

	void getInfo()
	{
		cout << "Name: " << getName() << "; Health: " << getHealth() << "; Strength: " << getDamage() << "; Class: Thief" << endl;
	}
};


int main()
{
	warrior w1("Warrior1", 100, 60);
	warrior w2("Warrior2", 100, 50);
	zealot zealot("Zealot", 80, 20);
	necromancer necro("Necro", 70, 40);
	thief thief("Thief", 90, 30);

	cout << "Game initial state: " << endl;
	w1.getInfo();
	w2.getInfo();
	zealot.getInfo();
	necro.getInfo();
	thief.getInfo();
	cout << "------------------------------" << endl;

	w1.attack(&w2);
	cout << w1.getName() << " attacked " << w2.getName() << "!" << endl;
	w2.getInfo();
	cout << "------------------------------" << endl;

	w2.attack(&w1);
	cout << w2.getName() << " attacked " << w1.getName() << "!" << endl;
	w1.getInfo();
	cout << "------------------------------" << endl;
	
	zealot.heal(&w1, 10);
	cout << zealot.getName() << " healed " << w1.getName() << " by 10 HP!" << endl;
	w1.getInfo();
	zealot.getInfo();
	cout << "------------------------------" << endl;

	thief.lifeSteal(&w1);
	thief.getInfo();
	w1.getInfo();
	cout << "------------------------------" << endl;

	cout << w1.getName() << " attacked " << w2.getName() << "!" << endl;
	w1.attack(&w2);
	cout << "------------------------------" << endl;

	necro.revive(&w2);
	w2.getInfo();
	necro.getInfo();
	cout << "------------------------------" << endl;

	return 0;
}

/*
	1. Що таке клас в C++?     Це опис об'єкта, в якому визначені поля (різні дані) та методи для цього об'єкта.
	2. Що таке об'єкт класу?     Об'єкт - це реальна копія класу, яка навідміну від класу займає пам'ять, а також може виконувати методи класу.
	3. Что такое конструктор?     Конструктор - це функція класу, яка викликається при створенні об'єкту для ініціалізації полів.
	4. Для чого використовується ключове слово private?     Поля та методи прописані під private стають доступними тільки всередині класу, за межами класу вони не будуть доступними.
	5. Для чого використовується ключове слово public?     public робить прописані під ним поля та методи доступними з будь-якого місця програми.
	6. Что такое наследование?     Це коли один клас успадковує властивості та методи з іншого, батьківского класу.
	7. Що означає запис "class Warrior : public Character"?     Цей запис означає, що створений клас Warrior буде успадковувати дані публічно з класу Character, тобто public і protected Character'а будуть такими ж в Warrior.
	8. Для чого використовуються геттери (наприклад getHealth())?     Геттери використовуються для читання приватних даних класів, не порушуючи інкапсуляцію.
	9. Що робить оператор -> в C++?     -> Використовується для доступу до полів та методів об'єкта через вказівник.
	10. Для чого використовується інкапсуляція?     Інкапсуляція захищає дані від неправильного використовування, та приховує внутрішні дані класу обмежуючи доступ до них.
	11. Що робить оператор this?     Це вказівник, який вказує на об'єкт класу, для розрізнювання локальніх змінних, та полів класу.
*/