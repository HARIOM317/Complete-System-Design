#include <iostream>

using namespace std;

// Encapsulation: Focuses on data security (Also, Object's characteristics and its behaviour are encapsulated together within that Object)

class SportCar
{
private:
    string brand;
    string model;
    bool isEngineOn;
    int currentSpeed;
    int currentGear;
    string tyreCompany;

public:
    SportCar(string b, string m)
    {
        this->brand = b;
        this->model = m;
        isEngineOn = false;
        currentSpeed = 0;
        currentGear = 0;
        tyreCompany = "MRF";
    }

    // _____ Getters _____
    int getSpeed()
    {
        return currentSpeed;
    }

    string getTyreCompany()
    {
        return tyreCompany;
    }

    // _____ Setters _____
    void setTyreCompany(string company)
    {
        this->tyreCompany = company;
    }

    // _____ Behaviour's _____
    void startEngine()
    {
        isEngineOn = true;
        cout << brand << " " << model << " : Engine starts with a roar!" << endl;
    }

    void shiftGear(int gear)
    {
        if (!isEngineOn)
        {
            cout << brand << " " << model << " : Engine is off! Cannot Shift Gear." << endl;
            return;
        }
        currentGear = gear;
        cout << brand << " " << model << " : Shifted to gear " << currentGear << endl;
    }

    void accelerate()
    {
        if (!isEngineOn)
        {
            cout << brand << " " << model << " : Engine is off! Cannot accelerate." << endl;
            return;
        }
        currentSpeed += 20;
        cout << brand << " " << model << " : Accelerating to " << currentSpeed << " km/h" << endl;
    }

    void brake()
    {
        currentSpeed -= 20;
        if (currentSpeed < 0)
            currentSpeed = 0;
        cout << brand << " " << model << " : Braking! Speed is now " << currentSpeed << " km/h" << endl;
    }

    void stopEngine()
    {
        isEngineOn = false;
        currentSpeed = 0;
        currentGear = 0;
        cout << brand << " " << model << " : Engine turned off." << endl;
    }

    ~SportCar() {}
};

int main()
{
    SportCar *mySportsCar = new SportCar("Ford", "Mustang");

    mySportsCar->startEngine();
    mySportsCar->shiftGear(1);
    mySportsCar->accelerate();
    mySportsCar->shiftGear(2);
    mySportsCar->accelerate();
    mySportsCar->brake();
    mySportsCar->stopEngine();

    cout << "Current Speed of My Sports Car is " << mySportsCar->getSpeed() << endl;

    delete mySportsCar;

    return 0;
}