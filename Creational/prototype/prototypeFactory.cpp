#include <iostream>
#include <string>
#include <memory>

using namespace std;

struct Address
{
    string street;
    string city;
    int suite;

    Address(const string &street, const string &city, const int suite)
        : street{street},
          city{city},
          suite{suite}
    {
    }

    Address(const Address &other)
        : street{other.street},
          city{other.city},
          suite{other.suite}
    {
    }

    friend ostream &operator<<(ostream &os, const Address &obj)
    {
        return os
               << "street: " << obj.street
               << " city: " << obj.city
               << " suite: " << obj.suite;
    }
};

class Contact
{
private:
    /* data */
public:
    string name;
    Address *address;
    Contact(const string &name, Address *address) : name(name), address(address) {}
    ~Contact() { delete address; }
    friend ostream &operator<<(ostream &os, const Contact &contact)
    {
        os << "name : " << contact.name << ", address : " << *contact.address;
        return os;
    }
};

struct EmployeeFactory
{
    static unique_ptr<Contact> newMainOfficeEmployee(const string &name, const int suite)
    {
        static Contact p{"", new Address{"123 dd", "London", 0}};
        return newEmployee(name, suite, p);
    }

private:
    static unique_ptr<Contact> newEmployee(const string &name, int suite, const Contact &prototype)
    {
        auto result = make_unique<Contact>(prototype);
        result->name = name;
        result->address->suite = suite;
        return result;
    }
};

int main(int argc, const char **argv)
{
    return 0;
}