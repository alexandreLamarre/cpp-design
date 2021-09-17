//
// Created by Alexandre Lamarre on 2021-09-17.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

/**
 * Datatype that represents a Journal with a title and entires
 */
struct Journal{
    string title;
    vector<string> entries;
    Journal(const string &title) : title(title) {}

    void add_entry(const string& entry)
    {
        static int count = 1;
        entries.push_back(to_string(count++) + " : " + entry);
    }
};

/**
 * Separation of concerns :
 *        - Controls persistence of data
 */
struct PersistenceManager
{
    static void save(const Journal& j, const string& filename)
    {
        ofstream ofs(filename);
        for(auto &e : j.entries)
            ofs << e << endl;
    }
};

int main(){
    Journal journal {"Dear diary"};
    journal.add_entry("I ate a bug");
    journal.add_entry("I cried today");

    PersistenceManager pm;
    pm.save(journal, "diary.txt");
}