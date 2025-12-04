#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Cloneble (Prototype) interface
class Cloneble
{
public:
    virtual Cloneble *clone() const = 0;
    virtual ~Cloneble() {}
};

class NPC : public Cloneble
{
public:
    string name;
    int health;
    int attack;
    int defense;

    NPC(const string &name, int health, int attack, int defense)
    {
        // call database, complex calc (time consuming operations)
        this->name = name;
        this->health = health;
        this->attack = attack;
        this->defense = defense;

        cout << "Setting up template NPC '" << name << "'\n";
    }

    // copy‐constructor used by clone()
    NPC(const NPC &other)
    {
        name = other.name;
        health = other.health;
        attack = other.attack;
        defense = other.defense;
        cout << "Cloning NPC '" << name << "'\n";
    }

    // the clone method required by prototype
    Cloneble *clone() const override
    {
        return new NPC(*this);
    }

    void describe()
    {
        cout << "NPC " << name << " [HP = " << health << ", ATK = " << attack << ", DEF = " << defense << "]\n\n";
    }

    // setters to tweak the clone…
    void setName(const string &n)
    {
        name = n;
    }

    void setHealth(int h)
    {
        health = h;
    }

    void setAttack(int a)
    {
        attack = a;
    }

    void setDefense(int d)
    {
        defense = d;
    }
};

int main()
{
    // 1) build one “heavy” template
    NPC *alien = new NPC("Alien", 30, 5, 2);

    // 2) quickly clone + tweak as many variants as you like:
    NPC *alienCopied1 = dynamic_cast<NPC *>(alien->clone());
    alienCopied1->describe();

    NPC *alienCopied2 = dynamic_cast<NPC *>(alien->clone());
    alienCopied2->setName("Powerful Alien");
    alienCopied2->setHealth(80);
    alienCopied2->setDefense(6);
    alienCopied2->describe();

    // cleanup
    delete alien;
    delete alienCopied1;
    delete alienCopied2;

    return 0;
}