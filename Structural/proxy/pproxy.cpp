#include <iostream>

using namespace std;

template <typename T>
struct Property
{
    T value;

    Property(T value)
    {
        *this = value;
    }

    T operator=(T new_value)
    {
        cout << "Assignment!\n";
        return value = new_value;
    }
};

struct Creature
{
    Property<int> strength{10};
    Property<int> agility{5};
};

/**
 * @brief Property proxy
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */

int main(int argc, const char **argv)
{
    Creature c;
    c.strength = 5;

    return 0;
}