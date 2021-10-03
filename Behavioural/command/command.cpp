#include <iostream>
#include <vector>

using namespace std;

struct BankAccount
{
    int balance{0};
    int overdraftLimit{-500};

    bool deposit(int amount)
    {
        balance += amount;
        cout << "deposited " << amount << ",  balance is now " << balance << endl;
        return true;
    }

    bool withdraw(int amount)
    {
        if (balance - amount >= overdraftLimit)
        {
            balance -= amount;
            cout << "withdrew " << amount
                 << " , balance is now " << balance << endl;
            return true;
        }
        return false;
    }
};

struct Command
{
    bool completed;
    virtual void call() = 0;
    virtual void undo() = 0;
};

struct BankAccountCommand : Command
{
    BankAccount &account;
    enum Action
    {
        deposit,
        withdraw
    } action;
    int amount;

    BankAccountCommand(BankAccount &account, Action action, int amount) : account(account), action(action), amount(amount)
    {
        completed = false;
    }

    void call() override
    {
        switch (action)
        {
        case deposit:
            completed = account.deposit(amount);
            break;
        case withdraw:
            completed = account.withdraw(amount);
        default:
            break;
        }
    }

    void undo() override
    {
        if (!completed)
            return;
        switch (action)
        {
        case deposit:
            account.withdraw(amount);
            break;
        case withdraw:
            account.deposit(amount);
        default:
            break;
        }
    }
};

struct CompositeBankAccountCommand : vector<BankAccountCommand>, Command
{
};

int main()
{
    BankAccount ba;
    vector<BankAccountCommand> commands{
        BankAccountCommand{ba, BankAccountCommand::deposit, 100},
        BankAccountCommand{ba, BankAccountCommand::withdraw, 200},
    };

    cout << ba.balance << endl;

    for (auto comm : commands)
        comm.call();
    for (auto it = commands.rbegin(); it != commands.rend(); it++)
    {
        it->undo();
    }

    cout << ba.balance << endl;
    return 0;
}