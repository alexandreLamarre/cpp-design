#include <iostream>
#include <vector>

using namespace std;

struct BankAccount
{
    int balance{0};
    int overdraftLimit{-500};

    void deposit(int amount)
    {
        balance += amount;
        cout << "deposited " << amount << ",  balance is now " << balance << endl;
    }

    void withdraw(int amount)
    {
        if (balance - amount >= overdraftLimit)
        {
            balance -= amount;
            cout << "withdrew " << amount
                 << " , balance is now " << balance << endl;
        }
    }
};

struct Command
{
    virtual void call() = 0;
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

    BankAccountCommand(BankAccount &account, Action action, int amount) : account(account), action(action), amount(amount) {}

    void call() override
    {
        switch (action)
        {
        case deposit:
            account.deposit(amount);
            break;
        case withdraw:
            account.withdraw(amount);
        default:
            break;
        }
    }
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

    cout << ba.balance << endl;
    return 0;
}