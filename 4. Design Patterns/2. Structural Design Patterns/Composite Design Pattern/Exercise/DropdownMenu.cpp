#include <iostream>
#include <vector>

using namespace std;

class MenuComponent
{
public:
    virtual void display(int indent = 0) = 0;
};

class MenuItem : public MenuComponent
{
    string name;

public:
    MenuItem(string name) : name(name) {}

    void display(int indent = 0) override
    {
        cout << string(indent, ' ') << name << endl;
    }
};

class Menu : public MenuComponent
{
    string name;
    vector<MenuComponent *> items;

public:
    Menu(string name) : name(name) {}

    void add(MenuComponent *item)
    {
        items.push_back(item);
    }

    void display(int indent = 0) override
    {
        cout << string(indent, ' ') << name << ":" << endl;
        for (auto item : items)
        {
            item->display(indent + 4);
        }
    }
};

int main()
{
    Menu *electronics = new Menu("Electronics");
    electronics->add(new MenuItem("Mobiles"));
    electronics->add(new MenuItem("Laptops"));

    Menu *home = new Menu("Home Appliances");
    home->add(new MenuItem("Refrigerators"));
    home->add(new MenuItem("Microwave"));

    Menu *mainMenu = new Menu("Main Menu");
    mainMenu->add(electronics);
    mainMenu->add(home);

    mainMenu->display();

    return 0;
}