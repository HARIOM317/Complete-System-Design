#include "../../include/managers/DarkStoreManager.h"
#include <algorithm>

using namespace std;

DarkStoreManager *DarkStoreManager::instance = nullptr;

DarkStoreManager::DarkStoreManager()
{
    darkStores = new vector<DarkStore *>();
}

DarkStoreManager *DarkStoreManager::getInstance()
{
    if (instance == nullptr)
    {
        instance = new DarkStoreManager();
    }
    return instance;
}

void DarkStoreManager::registerDarkStore(DarkStore *ds)
{
    darkStores->push_back(ds);
}

vector<DarkStore *> DarkStoreManager::getNearbyDarkStores(double ux, double uy, double maxDistance)
{
    vector<pair<double, DarkStore *>> distList;
    for (auto ds : *darkStores)
    {
        double d = ds->distanceTo(ux, uy);
        if (d <= maxDistance)
        {
            distList.push_back(make_pair(d, ds));
        }
    }
    sort(distList.begin(), distList.end(),
         [](auto &a, auto &b)
         { return a.first < b.first; });

    vector<DarkStore *> result;
    for (auto &p : distList)
    {
        result.push_back(p.second);
    }
    return result;
}

DarkStoreManager::~DarkStoreManager()
{
    for (auto ds : *darkStores)
    {
        delete ds;
    }
    delete darkStores;
}
