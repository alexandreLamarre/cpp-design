#include <string>
#include <iostream>
#include <vector>

template <typename T>
struct Observer
{
    virtual void fieldChanged(
        T &source,
        const std::string &fieldName) = 0;
};

template <typename T>
struct Observable
{
    std::vector<Observer<T> *> observers;

public:
    void notify(T &source, const std::string &fieldName)
    {
        for (auto observer : observers)
        {
            observer->fieldChanged(source, fieldName);
        }
    }

    void subscribe(Observer<T> &observer)
    {
        observers.push_back(&observer);
    }
    void unsubscribe(Observer<T> &observer)
    {
        observers.erase(
            remove(observers.begin(), observers.end(), observer),
            observers.end());
    }
};

struct Person : public Observable<Person>
{
    int age;

public:
    Person(int age) : age(age) {}
    int getAge() const
    {
        return age;
    }

    void setAge(int age)
    {
        if (this->age == age)
            return;
        this->age = age;
        notify(*this, "age");
    }
};

struct ConsolePersonObserver : public Observer<Person>
{
    void fieldChanged(Person &source, const std::string &fieldName)
    {
        std::cout << "Person's " << fieldName << "has changed to : ";
        if (fieldName == "age")
            std::cout << source.getAge();
        std::cout << "\n";
    }
};

int main(int argc, const char **argv)
{
    Person person{10};
    ConsolePersonObserver cpo;
    person.subscribe(cpo);
    person.setAge(11);
    person.setAge(12);

    person.unsubscribe(cpo);
    person.setAge(1);

    return 0;
}