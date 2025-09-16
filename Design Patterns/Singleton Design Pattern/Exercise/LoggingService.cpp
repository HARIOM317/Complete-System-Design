#include <iostream>

using namespace std;

class Logger
{
private:
    static Logger *instance; // single instance
    Logger() {}              // private constructor (no direct object creation)

public:
    // static method to get the single instance
    static Logger *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new Logger();
        }
        return instance;
    }

    void log(string message)
    {
        cout << "[LOG]: " << message << endl;
    }
};

// Initialize static member
Logger *Logger::instance = nullptr;

int main()
{
    Logger *logger1 = Logger::getInstance();
    Logger *logger2 = Logger::getInstance();

    logger1->log("User logged in");
    logger2->log("User performed action");

    // Both logger1 and logger2 point to the same instance
    cout << (logger1 == logger2 ? "Same Instance" : "Different Instances") << endl;

    return 0;
}