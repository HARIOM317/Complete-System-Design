#include <iostream>
#include <unordered_map>

using namespace std;

class DataFetcher
{
public:
    virtual int getData(int key) = 0;
    virtual ~DataFetcher() {}
};

class RealDataFetcher : public DataFetcher
{
public:
    int getData(int key) override
    {
        cout << "Real fetch for key: " << key << endl;
        return key * 10; // Simulate expensive computation
    }
};

class CachingProxy : public DataFetcher
{
    RealDataFetcher *realFetcher;
    unordered_map<int, int> cache;

public:
    CachingProxy() : realFetcher(new RealDataFetcher()) {}

    int getData(int key) override
    {
        if (cache.count(key))
        {
            cout << "Returning cached result for key: " << key << endl;
            return cache[key];
        }

        int result = realFetcher->getData(key);
        cache[key] = result;

        return result;
    }

    ~CachingProxy()
    {
        delete realFetcher;
    }
};

int main()
{
    DataFetcher *fetcher = new CachingProxy();

    cout << fetcher->getData(5) << endl; // Real fetch
    cout << fetcher->getData(5) << endl; // Cached

    delete fetcher;

    return 0;
}