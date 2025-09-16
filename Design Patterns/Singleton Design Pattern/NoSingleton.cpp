#include <iostream>

using namespace std;

class NoSingleton
{
public:
    NoSingleton()
    {
        cout << "Singleton Constructor Called. New Object Created!" << endl;
    }
};

int main()
{
    NoSingleton *s1 = new NoSingleton();
    NoSingleton *s2 = new NoSingleton();

    cout << "s1 == s2 : " << (s1 == s2 ? "Yes" : "No") << endl;

    return 0;
}