#ifndef NET_BANKING_PAYMENT_STRATEGY_H
#define NET_BANKING_PAYMENT_STRATEGY_H

#include "PaymentStrategy.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class NetBankingPaymentStrategy : public PaymentStrategy
{
private:
    string accountNumber;

public:
    NetBankingPaymentStrategy(const string &accNum)
    {
        accountNumber = accNum;
    }

    void pay(double amount) override
    {
        cout << "Paid ₹ " << amount << " using Net banking (" << accountNumber << ")" << endl;
    }
};

#endif // NET_BANKING_PAYMENT_STRATEGY_H