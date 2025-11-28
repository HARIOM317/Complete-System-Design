#include <iostream>
#include <memory>
using namespace std;

// Step-1: Strategy Interface
class PaymentStrategy
{
public:
    virtual void pay(int amount) = 0;
    virtual ~PaymentStrategy() {}
};

// Step-2: Concrete Strategy
class CreditCardPayment : public PaymentStrategy
{
public:
    void pay(int amount) override
    {
        cout << "Paid Rs " << amount << " using Credit Card.\n";
    }
};

class UPIPayment : public PaymentStrategy
{
public:
    void pay(int amount) override
    {
        cout << "Paid Rs " << amount << " using UPI.\n";
    }
};

class NetBanking : public PaymentStrategy
{
public:
    void pay(int amount) override
    {
        cout << "Paid Rs " << amount << " using Net Banking.\n";
    }
};

// Step-3: Context
class PaymentContext
{
private:
    unique_ptr<PaymentStrategy> strategy; // runtime strategy

public:
    PaymentContext(PaymentStrategy *s) : strategy(s) {}

    void setStrategy(PaymentStrategy *s)
    {
        strategy.reset(s); // replace strategy at runtime
    }

    void executePayment(int amount)
    {
        strategy->pay(amount);
    }
};

// Step-4: Client
int main()
{
    PaymentContext context(new CreditCardPayment());
    context.executePayment(500);

    context.setStrategy(new UPIPayment());
    context.executePayment(1000);

    context.setStrategy(new NetBanking());
    context.executePayment(700);

    return 0;
}