#include <iostream>
#include <string>

using namespace std;

// __________ Handler Interface __________
class Handler
{
protected:
    Handler *next;

public:
    Handler() : next(nullptr) {}

    void setNext(Handler *next)
    {
        this->next = next;
    }

    virtual void handleRequest(string level, string message)
    {
        if (next != nullptr)
        {
            next->handleRequest(level, message);
        }
    }
};

// __________ Concrete Handlers __________
class InfoLogger : public Handler
{
public:
    void handleRequest(string level, string message) override
    {
        if (level == "INFO")
        {
            cout << "[INFO] " << message << endl;
        }
        else if (next != nullptr)
        {
            next->handleRequest(level, message);
        }
    }
};

class WarningLogger : public Handler
{
public:
    void handleRequest(string level, string message) override
    {
        if (level == "WARNING")
        {
            cout << "[WARNING] " << message << endl;
        }
        else if (next != nullptr)
        {
            next->handleRequest(level, message);
        }
    }
};

class ErrorLogger : public Handler
{
public:
    void handleRequest(string level, string message) override
    {
        if (level == "ERROR")
        {
            cout << "[ERROR] " << message << endl;
        }
        else if (next != nullptr)
        {
            next->handleRequest(level, message);
        }
    }
};

// __________ Build a Chain and Use It __________
int main()
{
    Handler *info = new InfoLogger();
    Handler *warn = new WarningLogger();
    Handler *error = new ErrorLogger();

    // Build chain: INFO → WARNING → ERROR
    info->setNext(warn);
    warn->setNext(error);

    info->handleRequest("INFO", "System is Running...");
    info->handleRequest("WARNING", "Low Disk Space!");
    info->handleRequest("ERROR", "System crashed!!");

    return 0;
}