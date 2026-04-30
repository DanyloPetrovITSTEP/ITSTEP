#include <iostream>
#include <string>
#include <thread>
#include <vector>

class Scene;

class Actor
{
    Scene* scene;

public:
    Scene* GetScene() const { return scene; }

    Actor(Scene* scene)
    {
        this->scene = scene;
    }

    virtual void Tick() = 0;
    virtual void Print() = 0;
};

class Scene
{
    std::vector<Actor*> actors;

public:
    void AddActor(Actor* actor)
    {
        actors.push_back(actor);
    }

    void RemoveActor(Actor* actor)
    {
        actors.erase(
            std::remove(actors.begin(), actors.end(), actor),
            actors.end()
        );
    }

    const std::vector<Actor*>& GetActors() const { return actors; }

    void Tick()
    {
        for (Actor* actor : actors)
        {
            actor->Tick();
        }
    }

    void Print();
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

public:
    bool IsAlive() const { return isAlive; }

    Animal(Scene* scene, const int hunger, const int max_hunger) : Actor(scene)
    {
        this->hunger = hunger;
        this->max_hunger = max_hunger;
    }

    void Tick() override
    {
        --hunger;

        if (hunger <= 0)
        {
            isAlive = false;
        }
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
    Rabbit(Scene* scene, const int hunger, const int max_hunger) : Animal(scene, hunger, max_hunger) {}

    void Tick() override
    {
        Animal::Tick();

        int need_huger = max_hunger - hunger;

        for (Actor* actor : GetScene()->GetActors())
        {
            Field* field = dynamic_cast<Field*>(actor);

            if (field == nullptr) continue;

            int gathered = field->GatherGrass(need_huger);
            Eat(gathered);

            need_huger -= gathered;

            if (need_huger <= 0) break;
        }
    }
};

void Scene::Print()
{
    int cout_grass = 0;
    int cout_rabbits = 0;

    for (Actor* actor : actors)
    {
        if (Field* field = dynamic_cast<Field*>(actor))
        {
            cout_grass += field->GetGrass();
        }
        else if (Rabbit* rabbit = dynamic_cast<Rabbit*>(actor))
        {
            if (rabbit->IsAlive())
            {
                cout_rabbits++;
            }
        }
    }

    std::cout << "Grass: " << cout_grass << '\n' << "Rabbits: " << cout_rabbits << '\n';
}

int main()
{
    Scene* scene = new Scene();

    // === Fields Actors ===

    std::vector<Field*> fields;

    fields.reserve(5);
    for (size_t i = 0; i < 5; i++)
    {
        fields.push_back(new Field(
            scene,
            std::rand() % 20 + 1,
            std::rand() % 20 + 1,
            std::rand() % 3 + 1
        ));
    }

    // === Fields Actors ===

    std::vector<Rabbit*> rabbits;

    rabbits.reserve(15);
    for (size_t i = 0; i < 15; i++)
    {
        const int max_hunger = std::rand() % 10 + 5;
        rabbits.push_back(new Rabbit(scene, max_hunger, max_hunger));
    }

    // =======

    for (Actor* actor : fields)
    {
        scene->AddActor(actor);
    }

    for (Actor* actor : rabbits)
    {
        scene->AddActor(actor);
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
