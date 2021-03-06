using namespace std;
#include <iostream>
#include <memory>
#include <vector>

class Memento
{
    int balance;

public:
    Memento(int balance) : balance(balance) {}

    friend class BankAccount;
    friend class BankAccount2;
};

class BankAccount
{
    int balance{0};

public:
    BankAccount(int balance) : balance(balance) {}

    Memento deposit(int amount)
    {
        balance += amount;
        return {balance};
    }

    void restore(const Memento &m)
    {
        balance = m.balance;
    }

    friend ostream &operator<<(ostream &os, const BankAccount &account)
    {
        os << "balance " << account.balance;
        return os;
    }
};

class BankAccount2
{
    int balance{0};
    vector<shared_ptr<Memento>> changes;
    int current; // timeline
public:
    BankAccount2(int balance) : balance(balance)
    {
        changes.emplace_back(make_shared<Memento>(balance));
        current = 0;
    }

    shared_ptr<Memento> deposit(int amount)
    {
        balance += amount;
        auto m = make_shared<Memento>(balance);
        changes.push_back(m);
        ++current;
        return m;
    }

    void restore(const shared_ptr<Memento> &m)
    {
        if (m)
        {
            balance = m->balance;
            changes.push_back(m);
            current = changes.size() - 1;
        }
    }

    shared_ptr<Memento> undo()
    {
        if (current > 0)
        {
            --current;
            auto m = changes[current];
            balance = m->balance;
            return m;
        }
        return {};
    }

    shared_ptr<Memento> redo()
    {
        if (current + 1 < changes.size())
        {
            ++current;
            auto m = changes[current];
            balance = m->balance;
            return m;
        }
        return {};
    }

    friend ostream &operator<<(ostream &os, const BankAccount2 &account)
    {
        os << "balance " << account.balance;
        return os;
    }
};

int main(int argc, char const *argv[])
{
    BankAccount2 ba{100};
    ba.deposit(50);
    ba.deposit(100);

    cout << ba << endl;
    ba.undo();
    cout << "Undo 1 " << ba << endl;
    ba.undo();
    cout << "Undo 2 " << ba << endl;
    ba.redo();
    cout << "Redo 1 " << ba << endl;
    ba.redo();
    cout << "Redo 2 " << ba << endl;

    return 0;
}
