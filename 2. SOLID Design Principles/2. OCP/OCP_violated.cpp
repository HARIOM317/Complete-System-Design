#include <iostream>
#include <string>

using namespace std;

// Wrong Design - Violating OCP Principle
class Payment
{
private:
    string type;

public:
    Payment(string type)
    {
        this->type = type;
    }

    // required changes in existing code to add new payment method in future
    void pay(double amount)
    {
        if (type == "credit")
        {
            cout << "Paid Rs " << amount << " using Credit Card.\n";
        }
        else if (type == "upi")
        {
            cout << "Paid Rs " << amount << " using UPI.\n";
        }
        else if (type == "paypal")
        {
            cout << "Paid Rs " << amount << " using Paypal.\n";
        }
    }
};

int main()
{
    Payment p1("upi");
    p1.pay(5000);

    Payment p2("credit");
    p2.pay(2500);

    return 0;
}