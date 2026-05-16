#include <iostream>
#include <map>
#include <memory>
#include <ostream>
using namespace std;

class engine
{
    int power_ = 0;

public:
    int get_power() const { return power_; }
    void set_power(const int power) { power_ = power; }
};

class car
{
    unique_ptr<engine> engine_ = make_unique<engine>();

public:
    void replace_engine(unique_ptr<engine>& new_engine)
    {
        engine_ = std::move(new_engine);
    }
};

class asset
{

};

class texture : public asset
{
    char* bytes = nullptr;
};

class wooden_texture : public texture
{

};

class metal_texture : public texture
{

};

class material : public asset
{
    shared_ptr<texture> texture_;

public:

    material(const shared_ptr<texture>& texture) : texture_(texture) {}
};

class AssetManager
{
public:
    map<string, weak_ptr<asset>> assets;

    void load_asset(const string& asset_name)
    {
        // load asset
    }
};

template <typename T>
    requires derived_from<T, texture>
shared_ptr<material> make_material()
{
    return make_shared<material>(make_shared<T>());
}

int main()
{
    // unique_ptr<int> ptr_1; // тільки один власник
    // shared_ptr<int> ptr_2; // може бути декілька власників
	// weak_ptr<int> ptr_3; // не володіє ресурсом, але може отримати доступ до нього, якщо він ще існує

    car car1;

    unique_ptr<engine> engine_1 = make_unique<engine>();
    engine_1->set_power(5);

    car1.replace_engine(engine_1);

    // ====================

    //make_material<wooden_texture>();

    weak_ptr<int> weak_test;

    {
        shared_ptr<int> shared_test = make_shared<int>(9);

        weak_test = shared_test;
    }

    if (shared_ptr<int> temp = weak_test.lock())
    {
        (*temp) += 1;
    }

    // ===============

    AssetManager asset_manager;

    auto asset = asset_manager.assets["Textures/Cat.png"];

    if (auto temp = asset.lock())
    {
        // asdasdasdasdasd
    }
    else
    {
        asset_manager.load_asset("Textures/Cat.png");
    }

    return 0;
}