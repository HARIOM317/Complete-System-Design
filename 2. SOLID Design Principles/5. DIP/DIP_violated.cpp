#include <iostream>

using namespace std;

// Low-Level Module
class MySQLDatabase
{
public:
    void saveToSQL(string data)
    {
        cout << "Executing SQL QueryL INSERT INTO users VALUES('" << data << "');" << endl;
    }
};

// Low-Level Module
class MongoDBDatabase
{
public:
    void saveToMongo(string data)
    {
        cout << "Executing MongoDB Function: db.users.insert({name: '" << data << "'})" << endl;
    }
};

// High-level module (Tightly coupled)
class UserService
{
private:
    MySQLDatabase sqlDb;     // Direct dependency on MySQL
    MongoDBDatabase mongoDb; // Direct dependency on MongoDB

public:
    void storeUserToSQL(string user)
    {
        // MySQL-specific code
        sqlDb.saveToSQL(user);
    }

    void storeUserToMongo(string user)
    {
        // MongoDB-specific code
        mongoDb.saveToMongo(user);
    }
};

int main()
{
    UserService service;
    service.storeUserToSQL("Hariom Singh Rajput");
    service.storeUserToMongo("Hariom Singh Rajput");

    return 0;
}