#include <iostream>

using namespace std;

// Target Inteface (what the system expect)
class PaymentProcessor
{
public:
    virtual void pay(int amount) = 0;
};

// Existing class (Paypal already works fine)
class Paypal : public PaymentProcessor
{
public:
    void pay(int amount) override
    {
        cout << "Paid " << amount << " using PayPal" << endl;
    }
};

// Incompatible class (Stripe API is different)
class Stripe
{
public:
    void makePayment(int amountInCents)
    {
        cout << "Paid " << amountInCents / 100 << " using Stripe" << endl;
    }
};

// Adapter (makes Stripe compatible with PaymentProcessor)
class StripeAdapter : public PaymentProcessor
{
private:
    Stripe *stripe;

public:
    StripeAdapter(Stripe *s) : stripe(s) {}

    void pay(int amount) override
    {
        stripe->makePayment(amount * 100); // converting dollars to cents
    }
};

int main()
{
    Paypal paypal;
    paypal.pay(100); // Works directly

    Stripe stripe;
    StripeAdapter stripeAdapter(&stripe);
    stripeAdapter.pay(200); // Works via adapter

    return 0;
}