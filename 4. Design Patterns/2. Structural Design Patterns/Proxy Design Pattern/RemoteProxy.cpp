#include <iostream>
using namespace std;

// Remote Interface
class Service
{
public:
    virtual void fetchData() = 0;
    virtual ~Service() {}
};

// Real object on remote server
class RemoteService : public Service
{
public:
    void fetchData() override
    {
        cout << "Fetching data from remote server...\n";
    }
};

// Local proxy that communicates with remote server
class RemoteServiceProxy : public Service
{
    RemoteService *remote;

public:
    RemoteServiceProxy() : remote(nullptr) {}

    void fetchData() override
    {
        cout << "Proxy: Establishing network connection...\n";

        if (remote == nullptr)
        {
            remote = new RemoteService();
        }

        remote->fetchData();
    }

    ~RemoteServiceProxy()
    {
        delete remote;
    }
};

int main()
{
    Service *service = new RemoteServiceProxy();
    service->fetchData();

    delete service;

    return 0;
}