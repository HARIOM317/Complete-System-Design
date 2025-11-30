#ifndef DARKSTORE_MANAGER_H
#define DARKSTORE_MANAGER_H

#include <vector>
#include "../services/DarkStore.h"

class DarkStoreManager
{
private:
    std::vector<DarkStore *> *darkStores;
    static DarkStoreManager *instance;
    DarkStoreManager();

public:
    static DarkStoreManager *getInstance();
    void registerDarkStore(DarkStore *ds);
    std::vector<DarkStore *> getNearbyDarkStores(double ux, double uy, double maxDistance);
    ~DarkStoreManager();
};

#endif
