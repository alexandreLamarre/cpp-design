#include <iostream>
#include <memory>

using namespace std;

struct BankAccount
{
    virtual ~BankAccount() = default;
    virtual void deposit(int amount);
    virtual void withdraw(int amount);
};

struct CurrentAccount : BankAccount
{
    int balance;
    explicit CurrentAccount(const int balance) : balance(balance) {}

    void deposit(int amount)
    {
        balance += amount;
    }

    void withdraw(int amount)
    {
        if (amount <= balance)
            balance -= amount;
    }

    friend ostream &operator<<(ostream &os, const CurrentAccount &obj)
    {
        return os << "balance " << obj.balance;
    }
};

int main(int argc, const char **argv)
{
    BankAccount *a = new CurrentAccount(123);
    a->deposit(321);
    delete a;

    auto b = make_shared<CurrentAccount>(123); // proxy : looks and behaves like a pointer but is a smart pointer
    BankAccount *actual = b.get();
    return 0;
}