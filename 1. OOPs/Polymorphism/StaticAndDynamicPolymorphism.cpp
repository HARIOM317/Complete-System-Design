#include <iostream>

using namespace std;

// Base Car class
class Car
{
protected:
    string brand;
    string model;
    bool isEngineOn;
    int currentSpeed;

public:
    Car(string b, string m)
    {
        brand = b;
        model = m;
        isEngineOn = false;
        currentSpeed = 0;
    }

    // Common methods for All cars.
    void startEngine()
    {
        isEngineOn = true;
        cout << brand << " " << model << " : Engine started." << endl;
    }

    void stopEngine()
    {
        isEngineOn = false;
        currentSpeed = 0;
        cout << brand << " " << model << " : Engine turned off." << endl;
    }

    virtual void accelerate() = 0; // Abstract method for Dynamic Polymorphism

    virtual void accelerate(int speed) = 0; // Abstract method for Static Polymorphism

    virtual void brake() = 0; // Abstract method for Dynamic Polymorphism

    virtual ~Car() {}
};

class ManualCar : public Car
{
private:
    int currentGear;

public:
    ManualCar(string brand, string model) : Car(brand, model)
    {
        currentGear = 0;
    }

    // Specialized method for Manual Car
    void shiftGear(int gear)
    {
        currentGear = gear;
        cout << brand << " " << model << " : Shifted to gear " << currentGear << endl;
    }

    // Overriding accelerate - Dynamic Polymorphism
    void accelerate()
    {
        if (!isEngineOn)
        {
            cout << brand << " " << model << " : Cannot accelerate! Engine is off." << endl;
            return;
        }
        currentSpeed += 20;
        cout << brand << " " << model << " : Accelerating to " << currentSpeed << " km/h" << endl;
    }

    // overriding and overloading accelerate at the same time.
    void accelerate(int speed)
    {
        if (!isEngineOn)
        {
            cout << brand << " " << model << " : Cannot accelerate! Engine is off." << endl;
            return;
        }
        currentSpeed += speed;
        cout << brand << " " << model << " : Accelerating to " << currentSpeed << " km/h" << endl;
    }

    // Overriding brake - Dynamic Polymorphism
    void brake()
    {
        currentSpeed -= 20;
        if (currentSpeed < 0)
            currentSpeed = 0;
        cout << brand << " " << model << " : Braking! Speed is now " << currentSpeed << " km/h" << endl;
    }
};

class ElectricCar : public Car
{
private:
    int batteryLevel;

public:
    ElectricCar(string brand, string model) : Car(brand, model)
    {
        batteryLevel = 50;
    }

    // specialized method for Electric Car
    void chargeBattery()
    {
        batteryLevel = 100;
        cout << brand << " " << model << " : Battery fully charged!" << endl;
    }

    // Overriding accelerate - Dynamic Polymorphism
    void accelerate()
    {
        if (!isEngineOn)
        {
            cout << brand << " " << model << " : Cannot accelerate! Engine is off." << endl;
            return;
        }
        if (batteryLevel <= 0)
        {
            cout << brand << " " << model << " : Battery dead! Cannot accelerate." << endl;
            return;
        }
        batteryLevel -= 10;
        currentSpeed += 15;
        cout << brand << " " << model << " : Accelerating to " << currentSpeed << " km/h. Battery at " << batteryLevel << "%." << endl;
    }

    // Overriding and Overload accelerate
    void accelerate(int speed)
    {
        if (!isEngineOn)
        {
            cout << brand << " " << model << " : Cannot accelerate! Engine is off." << endl;
            return;
        }
        if (batteryLevel <= 0)
        {
            cout << brand << " " << model << " : Battery dead! Cannot accelerate." << endl;
            return;
        }
        batteryLevel -= (speed / 2);
        currentSpeed += speed;
        cout << brand << " " << model << " : Accelerating to " << currentSpeed << " km/h. Battery at " << batteryLevel << "%." << endl;
    }

    // Overriding brake - Dynamic Polymorphism
    void brake()
    {
        currentSpeed -= 15;
        if (batteryLevel < 90)
            batteryLevel += 5;

        if (currentSpeed < 0)
            currentSpeed = 0;

        cout << brand << " " << model << " : Regenerative braking! Speed is now " << currentSpeed << " km/h. Battery at " << batteryLevel << "%." << endl;
    }
};

int main()
{
    Car *manualCar = new ManualCar("Ford", "Mustang");

    manualCar->startEngine();
    manualCar->accelerate();
    manualCar->accelerate(30);
    manualCar->brake();
    manualCar->stopEngine();

    cout << "\n-------------------------\n\n";

    Car *electricCar = new ElectricCar("Tesla", "Model S");

    electricCar->startEngine();
    electricCar->accelerate();
    electricCar->accelerate(45);
    electricCar->brake();
    electricCar->stopEngine();

    // Cleanup
    delete manualCar;
    delete electricCar;

    return 0;
}