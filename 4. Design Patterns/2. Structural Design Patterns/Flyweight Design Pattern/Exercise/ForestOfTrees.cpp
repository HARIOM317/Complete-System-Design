#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

// Flyweight Class (Shared Data)
class TreeType
{
public:
    string name;
    string color;
    string texture;

    TreeType(string name, string color, string texture) : name(name), color(color), texture(texture) {}

    void draw(int x, int y)
    {
        cout << "Drawing " << name << " tree at ("
             << x << ", " << y << ") with color "
             << color << " and texture " << texture << endl;
    }
};

// Flyweight Factory - Reuses objects using a map
class TreeFactory
{
    unordered_map<string, TreeType *> treeTypes;

public:
    TreeType *getTreeType(string name, string color, string texture)
    {
        string key = name + color + texture;

        if (treeTypes.find(key) == treeTypes.end())
        {
            treeTypes[key] = new TreeType(name, color, texture);
        }
        return treeTypes[key];
    }
};

// Tree Object (Extrinsic Data)
class Tree
{
public:
    int x, y;
    TreeType *type;

    Tree(int x, int y, TreeType *type) : x(x), y(y), type(type) {}

    void draw()
    {
        type->draw(x, y);
    }
};

int main()
{
    TreeFactory factory;

    // Shared type created once
    TreeType *mango = factory.getTreeType("Mango", "Green", "Rough");

    // Multiple trees with same type
    Tree t1(10, 20, mango);
    Tree t2(15, 40, mango);

    t1.draw();
    t2.draw();

    return 0;
}