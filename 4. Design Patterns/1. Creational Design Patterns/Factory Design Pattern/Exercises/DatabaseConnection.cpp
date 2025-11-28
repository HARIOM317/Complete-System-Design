#include <iostream>
#include <memory>
#include <string>

using namespace std;

// Step-1: Product Interface
class DBConnection
{
public:
    virtual void connect() = 0;
    virtual void executeQuery(const string &query) = 0;

    virtual ~DBConnection() {}
};

// Step-2: Concrete Products
class MySQLConnection : public DBConnection
{
public:
    void connect() override
    {
        cout << "Connected to MySQL Database" << endl;
    }

    void executeQuery(const string &query) override
    {
        cout << "Executing on MySQL: " << query << endl;
    }
};

class PostGreSQLConnection : public DBConnection
{
public:
    void connect() override
    {
        cout << "Connected to PostgreSQL Database" << endl;
    }

    void executeQuery(const string &query) override
    {
        cout << "Executing on PostgreSQL: " << query << endl;
    }
};

class MongoDBConnection : public DBConnection
{
public:
    void connect() override
    {
        cout << "Connected to MongoDB Database" << endl;
    }

    void executeQuery(const string &query) override
    {
        cout << "Executing on MongoDB: " << query << endl;
    }
};

// Step-3: Abstract Factory
class DBFactory
{
public:
    virtual unique_ptr<DBConnection> createConnection() = 0;

    virtual ~DBFactory() {}
};

// Step-4: Concrete Factories
class MySQLfactory : public DBFactory
{
public:
    unique_ptr<DBConnection> createConnection() override
    {
        return make_unique<MySQLConnection>();
    }
};

class PostgreSQLFactory : public DBFactory
{
public:
    unique_ptr<DBConnection> createConnection() override
    {
        return make_unique<PostGreSQLConnection>();
    }
};

class MongoDBFactory : public DBFactory
{
public:
    unique_ptr<DBConnection> createConnection() override
    {
        return make_unique<MongoDBConnection>();
    }
};

// Step-5: Client Code
int main()
{
    unique_ptr<DBFactory> factory;

    // Suppose we want PostgreSQl
    factory = make_unique<PostgreSQLFactory>();
    auto connection = factory->createConnection();

    connection->connect();
    connection->executeQuery("SELECT * FROM users");

    // Switching t o MongoDB (no client code changes in creation logic!)
    factory = make_unique<MongoDBFactory>();
    auto mongoConn = factory->createConnection();

    mongoConn->connect();
    mongoConn->executeQuery("{ find: 'users' }");

    return 0;
}