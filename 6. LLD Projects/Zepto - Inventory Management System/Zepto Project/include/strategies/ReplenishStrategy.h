#ifndef REPLENISH_STRATEGY_H
#define REPLENISH_STRATEGY_H

#include <map>

// Forward Declaration to avoid circular dependency
class InventoryManager;

class ReplenishStrategy
{
public:
    virtual void replenish(InventoryManager *manager, std::map<int, int> itemsToReplenish) = 0;
    virtual ~ReplenishStrategy() {}
};

#endif
