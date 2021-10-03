#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
    vector<string> names{"john", "jane", "jill", "jack"};
    vector<string>::iterator it = names.begin(); // exists as member function or global function, i.e. begin(names)
    cout << "first name is " << *it << endl;

    ++it;
    it->append(string(" goodall"));
    cout << " second name is " << *it << endl;

    while (++it != names.end()) //.end() points to a memory location after the last element of the container
    {
        cout << "another name " << *it << endl;
    }

    //reverse order
    // similarly, rend exists as a member function and global function
    // rend points to the memory directly preceding the first element of the container
    for (auto ri = rbegin(names); ri != rend(names); ++ri)
    {
        cout << *ri;
        if (ri + 1 != rend(names))
        {
            cout << ", ";
        }
        cout << endl;
    }
    // const iterators do not allow append operations to modify the collection
    vector<string>::const_reverse_iterator jack = crbegin(names);

    for (auto &name : names) // requires begin & end to be implemented on the collection, returns *it to &name at each iteration
        cout << "name = " << name << endl;

    return 0;
}
