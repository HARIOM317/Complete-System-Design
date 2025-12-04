#include <iostream>

using namespace std;

// State Interface
class OrderState
{
public:
    virtual void nextState(class Order *order) = 0;
    virtual void prevState(class Order *order) = 0;
    virtual void printStatus() = 0;
    virtual ~OrderState() {}
};

// Forward declaration
class Order;

// __________ Different Concrete States __________

// New State
class NewState : public OrderState
{
public:
    void nextState(Order *order) override;
    void prevState(Order *order) override
    {
        cout << "New order. No previous state.\n";
    }
    void printStatus() override
    {
        cout << "Order is NEW.\n";
    }
};

// Packed State
class PackedState : public OrderState
{
public:
    void nextState(Order *order) override;
    void prevState(Order *order) override;
    void printStatus() override
    {
        cout << "Order is PACKED.\n";
    }
};

// Shipped State
class ShippedState : public OrderState
{
public:
    void nextState(Order *order) override;
    void prevState(Order *order) override;
    void printStatus() override
    {
        cout << "Order is SHIPPED\n";
    }
};

// Delivered State
class DeliveredState : public OrderState
{
public:
    void nextState(Order *order) override
    {
        cout << "Order already delivered. No next state.\n";
    }
    void prevState(Order *order) override
    {
        cout << "Cannot go back from Delivered.\n";
    }
    void printStatus() override
    {
        cout << "Order is DELIVERED.\n";
    }
};

// Context Class (Order)
class Order
{
private:
    OrderState *state;

public:
    Order()
    {
        state = new NewState();
    }

    void setState(OrderState *newState)
    {
        delete state; // Replace previous state
        state = newState;
    }

    void nextState()
    {
        state->nextState(this);
    }

    void prevState()
    {
        state->prevState(this);
    }

    void printStatus()
    {
        state->printStatus();
    }

    ~Order()
    {
        delete state;
    }
};

// __________ Define Transitions __________

// New → Packed
void NewState::nextState(Order *order)
{
    order->setState(new PackedState());
}

// Packed → Shipped
void PackedState::nextState(Order *order)
{
    order->setState(new ShippedState());
}
void PackedState::prevState(Order *order)
{
    order->setState(new NewState());
}

// Shipped → Delivered
void ShippedState::nextState(Order *order)
{
    order->setState(new DeliveredState());
}
void ShippedState::prevState(Order *order)
{
    order->setState(new PackedState());
}

int main()
{
    Order order;

    order.printStatus();
    order.nextState();

    order.printStatus();
    order.nextState();

    order.printStatus();
    order.nextState();

    order.printStatus();

    return 0;
}