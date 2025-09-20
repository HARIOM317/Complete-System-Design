#include <iostream>
#include <vector>

using namespace std;

// Receiver
class BankAccount
{
    int balance = 0;

public:
    void deposit(int amount)
    {
        balance += amount;
        cout << "Deposited Rs " << amount << ", balance = Rs " << balance << endl;
    }

    void withdraw(int amount)
    {
        if (balance >= amount)
        {
            balance -= amount;
            cout << "Withdrew Rs " << amount << ", balance = Rs " << balance << endl;
        }
        else
        {
            cout << "Insufficient funds\n";
        }
    }
};

// Command Interface
class Command
{
public:
    virtual void execute() = 0;
    virtual ~Command() {}
};

// Concrete Command
class DepositCommand : public Command
{
    BankAccount &account;
    int amount;

public:
    DepositCommand(BankAccount &acc, int amt) : account(acc), amount(amt) {}

    void execute() override
    {
        account.deposit(amount);
    }
};

class WithdrawCommand : public Command
{
    BankAccount &account;
    int amount;

public:
    WithdrawCommand(BankAccount &acc, int amt) : account(acc), amount(amt) {}

    void execute() override
    {
        account.withdraw(amount);
    }
};

// Invoker
class TransactionManager
{
    vector<Command *> history;

public:
    void executeCommand(Command *cmd)
    {
        cmd->execute();
        history.push_back(cmd); // logging / can be used for undo
    }
};

int main()
{
    BankAccount account;
    TransactionManager manager;

    Command *deposit = new DepositCommand(account, 1000);
    Command *withdraw = new WithdrawCommand(account, 600);

    manager.executeCommand(deposit);
    manager.executeCommand(withdraw);

    return 0;
}