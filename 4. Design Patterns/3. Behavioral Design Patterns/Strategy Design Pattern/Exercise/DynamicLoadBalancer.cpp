#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <algorithm>

using namespace std;

// Step-1: Strategy Interface
class LoadBalancingStrategy
{
public:
    virtual int selectServer(const vector<int> &servers, const vector<int> &connections) = 0;

    virtual ~LoadBalancingStrategy() {}
};

// Step-2: Concrete Strategies

// Round Robin Strategy
class RoundRobinStrategy : public LoadBalancingStrategy
{
    int index = 0;

public:
    int selectServer(const vector<int> &servers, const vector<int> &connections) override
    {
        int server = servers[index];
        index = (index + 1) % servers.size();
        return server;
    }
};

// Least Connections Strategy
class LeastConnectionStrategy : public LoadBalancingStrategy
{
public:
    int selectServer(const vector<int> &servers, const vector<int> &connections) override
    {
        int minIndex = 0;
        for (int i = 1; i < connections.size(); i++)
        {
            if (connections[i] < connections[minIndex])
                minIndex = i;
        }
        return servers[minIndex];
    }
};

// Random Strategy
class RandomStrategy : public LoadBalancingStrategy
{
public:
    int selectServer(const vector<int> &servers, const vector<int> &connections) override
    {
        int randomIndex = rand() % servers.size();
        return servers[randomIndex];
    }
};

// Step-3: Context
class LoadBalancer
{
    vector<int> servers;     // server IDs
    vector<int> connections; // active connections on each server
    unique_ptr<LoadBalancingStrategy> strategy;

public:
    LoadBalancer(const vector<int> &s, LoadBalancingStrategy *strat) : servers(s), connections(s.size(), 0), strategy(strat) {}

    void setStrategy(LoadBalancingStrategy *strat)
    {
        strategy.reset(strat);
    }

    void handleRequest()
    {
        int server = strategy->selectServer(servers, connections);
        int index = find(servers.begin(), servers.end(), server) - servers.begin();

        connections[index]++; // simulate assigning request
        cout << "Request handled by Server " << server << " | Active Connections: " << connections[index] << endl;
    }
};

int main()
{
    vector<int> servers = {101, 102, 103}; // Server IDs

    // Start with Round Robin
    LoadBalancer lb(servers, new RoundRobinStrategy());
    cout << "==== Round Robin ====\n";
    for (int i = 0; i < 6; i++)
        lb.handleRequest();

    // Switch to Least Connections
    lb.setStrategy(new LeastConnectionStrategy());
    cout << "\n==== Least Connections ====\n";
    for (int i = 0; i < 6; i++)
        lb.handleRequest();

    // Switch to Random
    lb.setStrategy(new RandomStrategy());
    cout << "\n==== Random ====\n";
    for (int i = 0; i < 6; i++)
        lb.handleRequest();

    return 0;
}