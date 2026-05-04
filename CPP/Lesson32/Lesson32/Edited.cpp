#include <iostream>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <string>
#include <thread>
#include <vector>

class Scene;

class Actor
{
    Scene* scene;
    bool isPendingDestroy = false;

public:
    bool IsPendingDestroy() const { return isPendingDestroy; }
    void SetPendingDestroy(bool value) { isPendingDestroy = value; }

    Scene* GetScene() const { return scene; }

    Actor(Scene* scene)
    {
        this->scene = scene;
    }

    void DestroyActor()
    {
        isPendingDestroy = true;
    }

    virtual void Tick() = 0;
    virtual void Print() = 0;

    virtual ~Actor() = default;
};

class Scene
{
    std::vector<Actor*> actors;
	std::vector<Actor*> actorsToAdd;
    int tick = 0;
    int cleaningRate = 60;
    bool isTicking = false;

public:
    template <typename T, typename... Args>
    T* SpawnActor(Args... args)
    {
        T* actor = new T(this, args...);

        if (isTicking)
        {
            actorsToAdd.push_back(actor);
        }
        else
        {
            actors.push_back(actor);
        }

        return actor;
    }

    void AddActor(Actor* actor)
    {
        actors.push_back(actor);
    }

    const std::vector<Actor*>& GetActors() const { return actors; }

    void DespawnActor(Actor* actor)
    {
        actor->DestroyActor();
    }

    void ClearPendingDestroy()
    {
        actors.erase(
            std::remove_if(actors.begin(), actors.end(), [](Actor* actor)
            {
                if (actor->IsPendingDestroy())
                {
                    delete actor;
                    return true;
                }

                return false;
            }),
            actors.end()
        );
    }

    void Tick()
    {
        tick++;
        isTicking = true;

        for (Actor* actor : actors)
        {
            if (!actor->IsPendingDestroy())
            {
                actor->Tick();
            }
        }

        isTicking = false;

        for (Actor* actor : actorsToAdd)
        {
			actors.push_back(actor);
		}

		actorsToAdd.clear();

        if (tick % cleaningRate == 0)
        {
            ClearPendingDestroy();
        }
    }

    void Print();

    ~Scene()
    {
        for (Actor* actor : actors)
        {
            delete actor;
        }

        for (Actor* actor : actorsToAdd)
        {
            delete actor;
        }
	}
};

class Field : public Actor
{
    int grass;
    int max_grass;
    int grow_speed;

public:
    int GetGrass() const { return grass; }

    int GatherGrass(const int value)
    {
        grass -= value;

        if (grass >= 0) return value;

        const int result = value + grass;

        grass = 0;

        return result;
    }

    Field(Scene* scene, const int grass, const int max_grass, const int grow_speed) : Actor(scene)
    {
        this->grass = std::min(grass, max_grass);
        this->max_grass = max_grass;
        this->grow_speed = grow_speed;
    }

    void Tick() override
    {
        grass = std::min(max_grass, grass + grow_speed);
    }

    void Print() override
    {
        std::cout << grass << '/' << max_grass << std::endl;
    }
};

class Animal : public Actor
{
protected:
    int hunger;
    int max_hunger;
    bool isAlive = true;
    int reproduction_cooldown = 0;
	int reproduction_timer = 0;

public:
    bool IsAlive() const { return isAlive; }

    void Kill()
    {
		isAlive = false;
        GetScene()->DespawnActor(this);
    }

	virtual bool isSameType(Animal* other) = 0;
	virtual Animal* Reproduce() = 0;

    Animal(Scene* scene, const int hunger, const int max_hunger, const int reproduction_cooldown) : Actor(scene)
    {
        this->hunger = hunger;
        this->max_hunger = max_hunger;
        this->reproduction_cooldown = reproduction_cooldown;
    }

    void TryToReproduce()
    {
        if (!isAlive) return;

        reproduction_timer++;

		if (reproduction_timer < reproduction_cooldown) return;

        for (Actor* actor : GetScene()->GetActors())
        {
            Animal* other = dynamic_cast<Animal*>(actor);

            if (other == nullptr) continue;
			if (other == this) continue;
			if (!other->IsAlive()) continue;

            if (isSameType(other))
            {
				Reproduce();
                reproduction_timer = 0;
				break;
            }
        }
	}

    void Tick() override
    {
		if (!isAlive) return;

        --hunger;

        if (hunger <= 0)
        {
            Kill();
            return;
        }

		TryToReproduce();
    }

    void Print() override
    {
        std::cout << hunger << '/' << max_hunger << std::endl;
    }

    void Eat(int value)
    {
        hunger = std::min(max_hunger, hunger + value);
    }
};

class Rabbit : public Animal
{
public:
    Rabbit(Scene* scene, const int hunger, const int max_hunger) : Animal(scene, hunger, max_hunger, 4) {}

    void Tick() override
    {
        Animal::Tick();

		if (!IsAlive()) return;

        int need_hunger = max_hunger - hunger;

        for (Actor* actor : GetScene()->GetActors())
        {
            Field* field = dynamic_cast<Field*>(actor);

            if (field == nullptr) continue;

            int gathered = field->GatherGrass(need_hunger);
            Eat(gathered);

            need_hunger -= gathered;

            if (need_hunger <= 0) break;
        }
    }

    bool isSameType(Animal* other) override
    {
        return dynamic_cast<Rabbit*>(other) != nullptr; //
	}

    Animal* Reproduce() override
    {
        const int max_hunger = std::rand() % 10 + 5;
		return GetScene()->SpawnActor<Rabbit>(max_hunger, max_hunger);
	}
};

class Fox : public Animal
{

public:

    Fox(Scene* scene, const int hunger, const int max_hunger) : Animal(scene, hunger, max_hunger, 6) {}

    void Tick() override
    {
        Animal::Tick();

        if (!IsAlive()) return;

        int need_hunger = max_hunger - hunger;

        if (need_hunger <= 0) return;

        for (Actor* actor : GetScene()->GetActors())
        {
            Rabbit* rabbit = dynamic_cast<Rabbit*>(actor);
			if (rabbit == nullptr) continue;
            if (!rabbit->IsAlive()) continue;

			rabbit->Kill();
            Eat(need_hunger);

            break;
        }
    }

    bool isSameType(Animal* other) override
    {
        return dynamic_cast<Fox*>(other) != nullptr;
	}

    Animal* Reproduce() override
    {
        const int max_hunger = std::rand() % 10 + 5;
        return GetScene()->SpawnActor<Fox>(max_hunger, max_hunger);
	}
};

void Scene::Print()
{
    int cout_grass = 0;
    int cout_rabbits = 0;
	int cout_foxes = 0;

    for (Actor* actor : actors)
    {
        if (Field* field = dynamic_cast<Field*>(actor))
        {
            cout_grass += field->GetGrass();
        }
        else if (Rabbit* rabbit = dynamic_cast<Rabbit*>(actor))
        {
            if (rabbit->IsAlive() && !rabbit->IsPendingDestroy())
            {
                cout_rabbits++;
            }
        }
        else if (Fox* fox = dynamic_cast<Fox*>(actor))
        {
            if (fox->IsAlive() && !fox->IsPendingDestroy())
            {
                cout_foxes++;
            }
		}
    }

    std::cout << "Grass: " << cout_grass << '\n' << "Rabbits: " << cout_rabbits << '\n' << "Foxes: " << cout_foxes << '\n';
}

int main()
{
    Scene* scene = new Scene();

    // === Fields Actors ===

    for (size_t i = 0; i < 5; i++)
    {
        scene->SpawnActor<Field>(
            std::rand() % 20 + 1,
            std::rand() % 20 + 1,
            std::rand() % 3 + 1
        );
    }

    // === Fields Actors ===

    for (size_t i = 0; i < 15; i++)
    {
        const int max_hunger = std::rand() % 10 + 5;
        scene->SpawnActor<Rabbit>(max_hunger, max_hunger);
    }

    // === Fields Actors ===

    for (size_t i = 0; i < 4; i++)
    {
        const int max_hunger = std::rand() % 12 + 8;
        scene->SpawnActor<Fox>(max_hunger, max_hunger);
    }

    // ======


    for (int i = 0; i < 60; i++)
    {
        scene->Tick();

        system("cls");

        std::cout << "Tick: " << i << std::endl;
        scene->Print();



        /*std::cout << " : Fields" << std::endl;
        for (Actor* actor : fields)
        {
            actor->Print();
        }
        std::cout << std::endl;

        std::cout << " : Rabbits" << std::endl;
        for (Actor* actor : rabbits)
        {
            actor->Print();
        }
        std::cout << std::endl;*/

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }








    // ========

    delete scene;

    return 0;
}
