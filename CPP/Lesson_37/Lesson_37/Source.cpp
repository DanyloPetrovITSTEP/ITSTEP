#include <iostream>
#include <vector>
#include <list>

using namespace std;



template<typename... Args>
void Print(Args... args)
{
	cout << (... + args) << endl; // 1, 2, 3     ((1 + 2) + 3) ... + _ +

	(cout << ... << args) << endl; // (((cout << 1) << 2) << 3)
}



class Actor
{
	
public:

	Actor() = default;
};

class Warrior : public Actor
{

public:

	Warrior(int health, int maxHealth)
	{

	}
};


class Scene
{
	vector<Actor> actors;

public:

	template<typename T, typename... Args>
	requires derived_from<T, Actor>
	void SpawnActor(Args&&... args)
	{
		Actor* actor = new T(std::forward<Args>(args)...);
		actors.push_back(*actor);
	}

	~Scene()
	{
		for (Actor& actor : actors)
		{
			delete& actor;
		}
	}
};






int main()
{
	Print(1, 2, 3);

	////////////
	

	Scene scene;

	scene.SpawnActor<Warrior>(10, 10);

	////////////

	// id, name, score
	using row = tuple<int, string, int>;
	
	row test_row = { 0, "asd", 123 };

	vector<row> rows;

	rows.emplace_back(0, "Bob", 568);


	////////////

	initializer_list<int> init_list{1, 2, 3};

	vector<int> vec(init_list);

	list<int> list(init_list);


	return 0;
}