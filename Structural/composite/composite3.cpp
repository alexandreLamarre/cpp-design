// class Creature
// {
//     int strength, agility, intelligence;

// public:
//     int getStrength() const
//     {
//         return strength;
//     }
//     int getAgility() const
//     {
//         return agility;
//     }
//     int getIntelligence() const
//     {
//         return intelligence;
//     }

//     double sum() const
//     {
//     }

//     double average() const
//     {
//     }

//     int max() const
//     {
//     }
// };
#include <array>
#include <numeric>
#include <iostream>
using namespace std;
class Creature
{
    enum Abilities
    {
        str,
        agl,
        intl,
        count
    };
    array<int, count> abilities;

public:
    void setStrength(int strength)
    {
        abilities[str] = strength;
    }
    void setAgility(int agility)
    {
        abilities[agl] = agility;
    }
    void setIntelligence(int intelligence)
    {
        abilities[intl] = intelligence;
    }
    int getStrength() const { return abilities[str]; }
    int getAgility() const { return abilities[agl]; }
    int getIntelligence() const { return abilities[intl]; }

    int sum() const
    {
        return accumulate(abilities.begin(), abilities.end(), 0);
    }
    double average() const
    {
        return sum() / (double)count;
    }
    int max() const
    {
        return *max_element(abilities.begin(), abilities.end());
    }
};

int main(int argc, char const *argv[])
{
    Creature orc;
    orc.setStrength(16);
    orc.setIntelligence(9);
    orc.setAgility(11);

    cout << "The orc has an average stat of " << orc.average() << endl;
    return 0;
}
