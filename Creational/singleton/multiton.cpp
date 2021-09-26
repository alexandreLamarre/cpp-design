#include <map>
#include <memory>
#include <iostream>
#include <string>

using namespace std;

enum class Importance
{
    primary,
    secondary,
    tertiary
};

template <typename T, typename Key = std::string>
class Multiton
{
public:
    static shared_ptr<T> get(const Key &key)
    {
        if (const auto it = instances.find(key); it != instances.end())
        {
            return it->second;
        }

        auto instance = make_shared<T>();
        instances[key] = instance;
        return instance;
    }

protected:
    Multiton() = default;
    virtual ~Multiton() = default;

private:
    static map<Key, shared_ptr<T>> instances;
};

template <typename T, typename Key>
map<Key, shared_ptr<T>> Multiton<T, Key>::instances;

class Printer
{
private:
    static int totalInstanceCount;

public:
    Printer()
    {
        ++Printer::totalInstanceCount;
        cout << "A total of " << Printer::totalInstanceCount << " have been created" << endl;
    }
};

int Printer::totalInstanceCount = 0;

int main(int argc, const char **argv)
{
    typedef Multiton<Printer, Importance> mt;
    auto main = mt::get(Importance::primary);
    auto aux = mt::get(Importance::secondary);
    auto aux2 = mt::get(Importance::secondary);

    return 0;
}