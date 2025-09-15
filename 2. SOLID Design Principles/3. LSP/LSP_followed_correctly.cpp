#include <iostream>
#include <vector>
#include <typeinfo>
#include <stdexcept>

using namespace std;

// interface 1
class DepositOnlyAccount
{
public:
    virtual void deposit(double amount) = 0;
};

// interface 2
class WithdrawableAccounts : public DepositOnlyAccount
{
public:
    virtual void withdraw(double amount) = 0;
};

// ____________________________________________

class SavingAccount : public WithdrawableAccounts
{
private:
    double balance;

public:
    SavingAccount()
    {
        balance = 0;
    }

    void deposit(double amount)
    {
        balance += amount;
        cout << "Deposited: " << amount << " in Savings Account. New Balance: " << balance << endl;
    }

    void withdraw(double amount)
    {
        if (balance >= amount)
        {
            balance -= amount;
            cout << "Withdrawn: " << amount << " from Savings Account. New Balance: " << balance << endl;
        }
        else
        {
            cout << "Insufficient funds in Savings Account!\n";
        }
    }
};

class CurrentAccount : public WithdrawableAccounts
{
private:
    double balance;

public:
    CurrentAccount()
    {
        balance = 0;
    }

    void deposit(double amount)
    {
        balance += amount;
        cout << "Deposited: " << amount << " in Current Account. New Balance: " << balance << endl;
    }

    void withdraw(double amount)
    {
        if (balance >= amount)
        {
            balance -= amount;
            cout << "Withdrawn: " << amount << " from Current Account. New Balance: " << balance << endl;
        }
        else
        {
            cout << "Insufficient funds in Current Account!\n";
        }
    }
};

class FixedTermAccount : public DepositOnlyAccount
{
private:
    double balance;

public:
    FixedTermAccount()
    {
        balance = 0;
    }

    void deposit(double amount)
    {
        balance += amount;
        cout << "Deposited: " << amount << " in Fixed Term Account. New Balance: " << balance << endl;
    }
};

// Client class
class BankClient
{
private:
    vector<WithdrawableAccounts *> withdrawableAccounts;
    vector<DepositOnlyAccount *> depositOnlyaccounts;

public:
    BankClient(vector<WithdrawableAccounts *> withdrawableAccounts, vector<DepositOnlyAccount *> depositOnlyaccounts)
    {
        this->withdrawableAccounts = withdrawableAccounts;
        this->depositOnlyaccounts = depositOnlyaccounts;
    }

    void processTransactions()
    {
        for (WithdrawableAccounts *acc : withdrawableAccounts)
        {
            acc->deposit(1000);
            acc->withdraw(500);
        }

        for (DepositOnlyAccount *acc : depositOnlyaccounts)
        {
            acc->deposit(1000);
        }
    }
};

int main()
{
    vector<WithdrawableAccounts *> withdrawableAccounts;
    withdrawableAccounts.push_back(new SavingAccount());
    withdrawableAccounts.push_back(new CurrentAccount());

    vector<DepositOnlyAccount *> depositOnlyaccounts;
    depositOnlyaccounts.push_back(new FixedTermAccount());

    BankClient *client = new BankClient(withdrawableAccounts, depositOnlyaccounts);
    client->processTransactions();

    return 0;
}