#include <iostream>

using namespace std;

class Car
{
protected:
    string brand;
    string model;
    bool isEngineOn;
    int currentSpeed;

public:
    Car(string brand, string model)
    {
        this->brand = brand;
        this->model = model;
        isEngineOn = false;
        currentSpeed = 0;
    }

    // Common methods for all cars
    void startEngine()
    {
        isEngineOn = true;
        cout << brand << " " << model << " : Engine started." << endl;
        ;
    }

    void stopEngine()
    {
        isEngineOn = false;
        currentSpeed = 0;
        cout << brand << " " << model << " : Engine turned off." << endl;
    }

    void accelerate()
    {
        if (!isEngineOn)
        {
            cout << brand << " " << model << " : Cannot accelerate! Engine is off." << endl;
            return;
        }
        currentSpeed += 20;
        cout << brand << " " << model << " : Accelerating to " << currentSpeed << " km/h." << endl;
    }

    void brake()
    {
        currentSpeed -= 20;
        if (currentSpeed < 0)
            currentSpeed = 0;
        cout << brand << " " << model << " : Braking! Speed is now " << currentSpeed << " km/h" << endl;
    }

    virtual ~Car() {}
};

// Inherits from Car
class ManualCar : public Car
{
private:
    int currentGear; // specific to Manual Car

public:
    ManualCar(string b, string m) : Car(b, m)
    {
        currentGear = 0;
    }

    // Specialized method for Manual Car
    void shiftGear(int gear)
    {
        if (!isEngineOn)
        {
            cout << brand << " " << model << " : Engine is off! Cannot shift gear." << endl;
            return;
        }
        currentGear = gear;
        cout << brand << " " << model << " : Shifted to gear " << currentGear << endl;
    }
};
// Inherits from Car
class ElectricCar : public Car
{
private:
    int batteryLevel; // specific to Electric Car

public:
    ElectricCar(string b, string m) : Car(b, m)
    {
        batteryLevel = 50;
    }

    // specialized method for Electric Car
    void chargeBattery()
    {
        batteryLevel += 10;
        if (batteryLevel >= 100)
        {
            batteryLevel = 100;
            cout << brand << " " << model << " : Battery fully charged!" << endl;
        }
        else
        {
            cout << "\n";
            cout << brand << " " << model << " : Charging..." << "(Current Battery Level: " << batteryLevel << "%)" << endl;
        }
    }

    void accelerate()
    {
        if (!isEngineOn)
        {
            cout << brand << " " << model << " : Cannot accelerate! Engine is off." << endl;
            return;
        }

        batteryLevel -= 5;
        if (batteryLevel <= 0)
        {
            isEngineOn = false;
            batteryLevel = 0;
            currentSpeed = 0;
            cout << "Shutting down...\n";
            return;
        }

        currentSpeed += 20;
        cout << brand << " " << model << " : Accelerating to " << currentSpeed << " km/h." << endl;
    }
};

int main()
{
    ManualCar *myManualCar = new ManualCar("Suzuki", "WagonR");

    myManualCar->startEngine();
    myManualCar->shiftGear(1);
    myManualCar->shiftGear(2);
    myManualCar->accelerate();
    myManualCar->brake();
    myManualCar->stopEngine();

    delete myManualCar;

    cout << "\n----------------------\n";

    ElectricCar *myElectricCar = new ElectricCar("Tesla", "Model S");

    myElectricCar->chargeBattery();
    myElectricCar->startEngine();
    myElectricCar->accelerate();
    myElectricCar->brake();
    myElectricCar->stopEngine();

    delete myElectricCar;

    return 0;
}