#include <iostream>

using namespace std;

// A Precondition must be satisfied before a method can be executed.
// Sub classes can weaken the precondition but cannot strengthen it.

class User
{
public:
    // Precondition: Password must be at least 8 characters long
    virtual void setPassword(string password)
    {
        if (password.length() < 8)
        {
            throw invalid_argument("Password must be at least 8 characters long!");
        }
        cout << "Password set successfully!" << endl;
    }
};

// Less restricted that parent
class AdminUser : public User
{
public:
    // Precondition: Password must be at least 6 characters
    void setPassword(string password)
    {
        if (password.length() < 6)
        {
            throw invalid_argument("Password must be at least 6 characters long!");
        }
        cout << "Password set successfully!" << endl;
    }
};

int main()
{
    User *user = new AdminUser();
    user->setPassword("Admin1"); // works fine: AdminUser allows shorter passwords

    return 0;
}