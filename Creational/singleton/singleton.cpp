#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <fstream>

using namespace std;

/**
 * @brief Singleton database
 * 
 */
class sharedDatabase
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
};

int main(int argc, const char **argv)
{
    string city = "Tokyo";
    cout << city << " has population " << sharedDatabase::get().getPopulation("Tokyo") << endl;
    return 0;
}