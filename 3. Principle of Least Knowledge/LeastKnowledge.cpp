#include <iostream>
using namespace std;

class Address
{
    string pinCode;

public:
    Address(string pin) : pinCode(pin) {}

    string getPin()
    {
        return pinCode;
    }
};

class Customer
{
    Address address;

public:
    Customer(Address a) : address(a) {}

    string getPin()
    {
        return address.getPin();
    }
};

class Order
{
    Customer customer;

public:
    Order(Customer c) : customer(c) {}

    string getCustomerPin()
    {
        return customer.getPin();
    }
};

int main()
{
    Address add("110092");
    Customer cus(add);
    Order order(cus);

    cout << order.getCustomerPin();

    return 0;
}