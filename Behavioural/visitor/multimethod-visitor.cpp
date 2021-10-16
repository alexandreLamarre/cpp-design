#include <iostream>
#include <sstream>
#include <string>
#include <typeindex>
#include <map>
#include <utility>

using namespace std;
struct GameObject;

void collide(GameObject &first, GameObject &second);

struct GameObject
{
    virtual type_index type() const = 0;
    virtual void collide(GameObject &other)
    {
        ::collide(*this, other);
    }
};

//CRTP
template <typename T>
struct GameObjectImpl : GameObject
{
    type_index type() const override
    {
        return typeid(T);
    }
};

struct Planet : GameObjectImpl<Planet>
{
};
struct Asteroid : GameObjectImpl<Asteroid>
{
};
struct Spaceship : GameObjectImpl<Spaceship>
{
};

void spaceship_planet() { cout << "spaceship lands on a planet\n"; }
void asteroid_planet() { cout << "asteroid burns up in the atmosphere\n"; }
void asteroid_spaceship() { cout << "asterpod hits and destroys the spaceship"; }

map<pair<type_index, type_index>, void (*)(void)> outcomes{
    {{typeid(Spaceship), typeid(Planet)}, spaceship_planet},
    {{typeid(Asteroid), typeid(Planet)}, asteroid_planet},
    {{typeid(Asteroid), typeid(Spaceship)}, asteroid_spaceship}};

void collide(GameObject &first, GameObject &second)
{
    auto it = outcomes.find({first.type(), second.type()});
    if (it == outcomes.end())
    {
        it = outcomes.find({second.type(), first.type()});
        if (it == outcomes.end())
        {
            cout << "objects pass each other harmlessly\n";
            return;
        }
    }
    it->second();
}

int main(int argc, const char **argv)
{
    Spaceship spaceship;
    Asteroid asteroid;
    Planet planet;

    collide(planet, spaceship);
    collide(asteroid, planet);
    collide(asteroid, spaceship);
    return 0;
}