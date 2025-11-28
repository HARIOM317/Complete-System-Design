#include <iostream>

using namespace std;

class Printer
{
public:
    virtual void print() = 0;
    virtual ~Printer() {}
};

class RealPrinter : public Printer
{
public:
    void print() override
    {
        cout << "Printing document...\n\n";
    }
};

class SmartPrinterProxy : public Printer
{
    RealPrinter *printer;
    int callCount;

public:
    SmartPrinterProxy() : printer(new RealPrinter()), callCount(0) {}

    void print() override
    {
        callCount++;
        cout << "Log: print() called " << callCount << " times.\n";

        if (callCount > 5)
        {
            cout << "Rate limit exceeded! Try later.\n\n";
            return;
        }

        printer->print();
    }

    ~SmartPrinterProxy()
    {
        delete printer;
    }
};

int main()
{
    Printer *p = new SmartPrinterProxy();

    for (int i = 0; i < 7; i++)
    {
        p->print();
    }

    delete p;

    return 0;
}