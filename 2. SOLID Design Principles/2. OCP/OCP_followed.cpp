#include <iostream>

using namespace std;

// Interface
class PaymentMethod
{
public:
    virtual void pay(double amount) = 0;

    virtual ~PaymentMethod() {}
};

// Credit Card Payment
class CreditCardPayment : public PaymentMethod
{
public:
    void pay(double amount) override
    {
        cout << "Paid Rs " << amount << " using Credit Card.\n";
    }
};

// UPI Payment
class UPIPayment : public PaymentMethod
{
public:
    void pay(double amount) override
    {
        cout << "Paid Rs " << amount << " using UPI.\n";
    }
};

// New Paypal Payment
class PayPalPayment : public PaymentMethod
{
public:
    void pay(double amount) override
    {
        cout << "Paid Rs " << amount << " using PayPal.\n";
    }
};

// Payment Service
class PaymentService
{
public:
    void makePayment(PaymentMethod *method, double amount)
    {
        method->pay(amount);
    }
};

int main()
{
    // Correct Design: Follow OCP (Open-Close Principle)
    PaymentService service;

    CreditCardPayment cc;
    PayPalPayment paypal;
    UPIPayment upi;

    service.makePayment(&cc, 1200);
    service.makePayment(&paypal, 5000);
    service.makePayment(&upi, 10000);

    return 0;
}