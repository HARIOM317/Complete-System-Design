#include <iostream>
using namespace std;

// --- Strategy Interface for Walk ---
class WalkableRobot
{
public:
    virtual void walk() = 0;
    virtual ~WalkableRobot() {}
};

// --- Concrete Strategy for Walk ---
class NormalWalk : public WalkableRobot
{
public:
    void walk() override
    {
        cout << "Walking normally..." << endl;
    }
};

class NoWalk : public WalkableRobot
{
public:
    void walk() override
    {
        cout << "Cannot walk." << endl;
    }
};

// __________________________________________________

// --- Strategy Interface for Talk ---
class TalkableRobot
{
public:
    virtual void talk() = 0;
    virtual ~TalkableRobot() {}
};

// --- Concrete Strategy for Talk ---
class NormalTalk : public TalkableRobot
{
public:
    void talk() override
    {
        cout << "Talking normally..." << endl;
    }
};

class NoTalk : public TalkableRobot
{
public:
    void talk() override
    {
        cout << "Cannot talk." << endl;
    }
};

// __________________________________________________

// --- Strategy Interface for Fly ---
class FlyableRobot
{
public:
    virtual void fly() = 0;
    virtual ~FlyableRobot() {}
};

// --- Concrete Strategy for Walk ---
class NormalFly : public FlyableRobot
{
public:
    void fly() override
    {
        cout << "Flying normally..." << endl;
    }
};

class NoFly : public FlyableRobot
{
public:
    void fly() override
    {
        cout << "Cannot fly." << endl;
    }
};

// __________________________________________________

// Robot Base class
class Robot
{
    WalkableRobot *walkBehavior;
    TalkableRobot *talkBehavior;
    FlyableRobot *flyBehavior;

public:
    Robot(WalkableRobot *w, TalkableRobot *t, FlyableRobot *f)
    {
        this->walkBehavior = w;
        this->talkBehavior = t;
        this->flyBehavior = f;
    }

    void walk()
    {
        walkBehavior->walk();
    }

    void talk()
    {
        talkBehavior->talk();
    }

    void fly()
    {
        flyBehavior->fly();
    }

    virtual void projection() = 0; // Abstract method for subclasses
};

// --- Concrete Robot Types ---
class CompanionRobot : public Robot
{
public:
    CompanionRobot(WalkableRobot *w, TalkableRobot *t, FlyableRobot *f) : Robot(w, t, f) {}

    void projection() override
    {
        cout << "Displaying friendly companion features..." << endl;
    }
};

class WorkerRobot : public Robot
{
public:
    WorkerRobot(WalkableRobot *w, TalkableRobot *t, FlyableRobot *f) : Robot(w, t, f) {}

    void projection() override
    {
        cout << "Displaying worker efficiency stats..." << endl;
    }
};

// ___ Main Function ___
int main()
{
    Robot *robot1 = new CompanionRobot(new NormalWalk(), new NormalTalk(), new NoFly());

    robot1->walk();
    robot1->talk();
    robot1->fly();
    robot1->projection();

    cout << "\n--------------------------\n\n";

    Robot *robot2 = new WorkerRobot(new NoWalk(), new NoTalk(), new NormalFly());

    robot2->walk();
    robot2->talk();
    robot2->fly();
    robot2->projection();

    return 0;
}