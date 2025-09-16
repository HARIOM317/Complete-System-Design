#include <iostream>
#include <mutex>

using namespace std;

class Singleton
{
private:
    static Singleton *instance;
    static mutex mtx;

    Singleton()
    {
        cout << "Singleton Constructor Called!" << endl;
    }

public:
    static Singleton *getInstance()
    {
        lock_guard<mutex> lock(mtx); // Lock for thread safety
        if (instance == nullptr)
        {
            instance = new Singleton();
        }
        return instance;
    }
};

// Initialize static members
Singleton *Singleton::instance = nullptr;

int main()
{
    Singleton *s1 = Singleton::getInstance();
    Singleton *s2 = Singleton::getInstance();

    cout << "s1 == s2 : " << (s1 == s2 ? "Yes" : "No") << endl;

    return 0;
}