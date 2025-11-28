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
    // Double check locking..
    static Singleton *getInstance()
    {
        // first check (no locking)
        if (instance == nullptr)
        {
            lock_guard<mutex> lock(mtx); // Lock only if needed

            // second check (after acquiring lock)
            if (instance == nullptr)
            {
                instance = new Singleton();
            }
        }
        return instance;
    }
};

// Initialize static members
Singleton *Singleton::instance = nullptr;
mutex Singleton::mtx;

int main()
{
    Singleton *s1 = Singleton::getInstance();
    Singleton *s2 = Singleton::getInstance();

    cout << "s1 == s2 : " << (s1 == s2 ? "Yes" : "No") << endl;

    return 0;
}