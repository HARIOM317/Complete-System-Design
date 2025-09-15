#include <iostream>

using namespace std;

// A Postcondition must be satisfied after a method is executed.
// Sub classes can strengthen the Postcondition but cannot weaken it.

class Car
{
protected:
    int speed;

public:
    Car()
    {
        speed = 0;
    }

    void accelerate()
    {
        cout << "Accelerating..." << endl;
        speed += 20;
    }

    // PostCondition : Speed must reduce after brake
    virtual void brake()
    {
        cout << "Applying Brakes..." << endl;
        speed -= 20;
    }
};

// Subclass can strengthen postcondition - Does not violate LSP
class HybridCar : public Car
{
private:
    int charge;

public:
    HybridCar() : Car()
    {
        charge = 0;
    }

    // PostCondition : Speed must reduce after brake
    // PostCondition : Charge must increase.
    void brake()
    {
        cout << "Applying Brakes..." << endl;
        speed -= 20;
        charge += 10; // this should be followed by its sub-classes
    }
};

int main()
{
    Car *hybridCar = new HybridCar();
    hybridCar->brake(); // Works fine: HybridCar reduces speed and also increases charge.

    // Client feels no difference in substituting Hybrid car in place of Car.

    return 0;
}