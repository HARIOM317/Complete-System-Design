#include <iostream>

using namespace std;

// Exception Rule:
// A subclass should throw fewer or narrower exceptions
// (but not additional or broader exceptions) than the parent.
// C++ does not enforces this. Hence no compilation error.

/*
├── std::logic_error        <-- For logical errors detected before runtime
│   ├── std::invalid_argument   <-- Invalid function argument
│   ├── std::domain_error       <-- Function argument domain error
│   ├── std::length_error       <-- Exceeding valid length limits
│   ├── std::out_of_range       <-- Array or container index out of bounds
│
├── std::runtime_error      <-- For errors that occur at runtime
│   ├── std::range_error        <-- Numeric result out of range
│   ├── std::overflow_error     <-- Arithmetic overflow
│   ├── std::underflow_error
*/

class Parent
{
public:
    // Parent throws logic_error exception
    virtual void getValue() noexcept(false)
    {
        throw logic_error("Parent error");
    }
};

class Child : public Parent
{
public:
    // Child throws out_of_range exception
    void getValue() noexcept(false) override
    {
        throw out_of_range("Child error"); // Correct
        // throw runtime_error("Child Error"); // This is Wrong
    }
};

class Client
{
private:
    Parent *p;

public:
    Client(Parent *p)
    {
        this->p = p;
    }

    void takeValue()
    {
        try
        {
            p->getValue();
        }
        catch (const logic_error &e)
        {
            cout << "Logical error exception occurred : " << e.what() << endl;
        }
    }
};

int main()
{
    Parent *parent = new Parent();
    Child *child = new Child();

    Client *client1 = new Client(parent);
    client1->takeValue();

    Client *client2 = new Client(child);
    client2->takeValue();

    return 0;
}