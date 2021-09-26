#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <fstream>

using namespace std;

class Database
{
public:
    virtual int getPopulation(const string &name) {}
};

/**
 * @brief Singleton database
 * 
 */
class sharedDatabase : public Database
{
    /**
     * @brief Construct a new shared Database object
     * 
     */
    sharedDatabase()
    {
        cout << "Initializing database" << endl;
        std::ifstream ifs("capitals.txt");

        string s, s2;
        while (getline(ifs, s))
        {
            getline(ifs, s2);
            int population = stoi(s2);
            data[s] = population;
        }
    }
    map<string, int> data;

public:
    sharedDatabase(sharedDatabase const &) = delete;
    void operator=(sharedDatabase const &) = delete;

    static sharedDatabase &get()
    {
        static sharedDatabase db;
        return db;
    }

    int getPopulation(const string &name)
    {
        return data[name];
    }

    class DummyDatabase : public Database
    {
        map<string, int> data2;

    public:
        DummyDatabase()
        {
            data2["a"] = 1;
            data2["b"] = 3;
            data2["c"] = 4;
        }
    };

    struct sharedRecordFinder
    {
        int totalPopulation(vector<string> names)
        {
            int result = 0;
            for (auto &name : names)
            {
                result += sharedDatabase::get().getPopulation(name);
            }
            return result;
        }
    };

    struct ConfigurableRecordFinder
    {
        Database &db;

        ConfigurableRecordFinder(Database &db) : db(db) {}

        int totalPopulation(vector<string> names)
        {
            int result = 0;
            for (auto &name : names)
            {
                result += db.getPopulation(name);
            }
            return result;
        }
    };
};

int main(int argc, const char **argv)
{
    string city = "Tokyo";
    cout << city << " has population " << sharedDatabase::get().getPopulation("Tokyo") << endl;
    return 0;
}