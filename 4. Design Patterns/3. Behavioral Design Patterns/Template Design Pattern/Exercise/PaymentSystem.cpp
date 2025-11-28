#include <iostream>

using namespace std;

// Base Class [template]
class PaymentProcessor
{
public:
    // Template Method - defines the algorithm
    void process()
    {
        validateRequest();
        authenticateUser();
        makePayment(); // variable step
        sendNotification();
        cout << "---------------------------\n";
    }

protected:
    void validateRequest()
    {
        cout << "Validating payment request..." << endl;
    }

    void authenticateUser()
    {
        cout << "Authenticating user..." << endl;
    }

    virtual void makePayment() = 0; // must be overridden

    void sendNotification()
    {
        cout << "Sending payment notification..." << endl;
    }
};

// Subclass 1 : Card Payment
class cardPayment : public PaymentProcessor
{
protected:
    void makePayment() override
    {
        cout << "Processing card payment..." << endl;
    }
};

// Subclass 2 : UPI Payment
class UPIPayment : public PaymentProcessor
{
protected:
    void makePayment() override
    {
        cout << "Processing UPI payment..." << endl;
    }
};

// Driver code
int main()
{
    PaymentProcessor *p1 = new cardPayment();
    p1->process();

    PaymentProcessor *p2 = new UPIPayment();
    p2->process();

    // Cleanup
    delete p1;
    delete p2;

    return 0;
}