#include <iostream>

using namespace std;

// _____ Implementation Interface _____
class Color
{
public:
    virtual string fill() = 0;
    virtual ~Color() {}
};

// _____ Concrete Color Implementations _____
class Red : public Color
{
public:
    string fill() override { return "Red"; }
};

class Green : public Color
{
public:
    string fill() override { return "Green"; }
};

class Blue : public Color
{
public:
    string fill() override { return "Blue"; }
};

// _____ Create Shape Abstraction _____
class Shape
{
protected:
    Color *color; // Bridge

public:
    Shape(Color *c) : color(c) {}
    virtual void draw() = 0;
    virtual ~Shape() {}
};

// _____ Concrete Shape Implementations _____
class Circle : public Shape
{
public:
    Circle(Color *c) : Shape(c) {}
    void draw() override
    {
        cout << "Drawing Circle in " << color->fill() << " color" << endl;
    }
};

class Square : public Shape
{
public:
    Square(Color *c) : Shape(c) {}
    void draw() override
    {
        cout << "Drawing Square in " << color->fill() << " color" << endl;
    }
};

int main()
{
    Color *red = new Red();
    Color *blue = new Blue();

    Shape *circle = new Circle(red);
    Shape *square = new Square(blue);

    circle->draw(); // Drawing Circle in Red color
    square->draw(); // Drawing Square in Blue color

    delete red;
    delete blue;
    delete circle;
    delete square;

    return 0;
}