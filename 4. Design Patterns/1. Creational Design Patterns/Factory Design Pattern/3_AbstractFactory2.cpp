#include <iostream>
#include <memory>
using namespace std;

// Product Interface
class Button
{
public:
    virtual void render() = 0;
    virtual ~Button() {}
};

class Checkbox
{
public:
    virtual void render() = 0;
    virtual ~Checkbox() {}
};

// Concrete Products (Windows)
class WindowsButton : public Button
{
public:
    void render() override
    {
        cout << "Windows Button" << endl;
    }
};

class WindowsCheckbox : public Checkbox
{
public:
    void render() override
    {
        cout << "Windows Checkbox" << endl;
    }
};

// Concrete Products (Mac)
class MacButton : public Button
{
public:
    void render() override
    {
        cout << "Mac Button" << endl;
    }
};

class MacCheckbox : public Checkbox
{
public:
    void render() override
    {
        cout << "Mac Checkbox" << endl;
    }
};

// Abstract Factory
class GUIFactory
{
public:
    virtual unique_ptr<Button> createButton() = 0;
    virtual unique_ptr<Checkbox> createCheckbox() = 0;
    virtual ~GUIFactory() {}
};

// Concrete Factories
class WindowsFactory : public GUIFactory
{
public:
    unique_ptr<Button> createButton() override
    {
        return make_unique<WindowsButton>();
    }

    unique_ptr<Checkbox> createCheckbox() override
    {
        return make_unique<WindowsCheckbox>();
    }
};

class MacFactory : public GUIFactory
{
public:
    unique_ptr<Button> createButton() override
    {
        return make_unique<MacButton>();
    }

    unique_ptr<Checkbox> createCheckbox() override
    {
        return make_unique<MacCheckbox>();
    }
};

// Client
int main()
{
    unique_ptr<GUIFactory> factory;

    // Suppose we are on Mac
    factory = make_unique<MacFactory>();

    auto button = factory->createButton();
    auto checkbox = factory->createCheckbox();

    button->render();
    checkbox->render();

    return 0;
}