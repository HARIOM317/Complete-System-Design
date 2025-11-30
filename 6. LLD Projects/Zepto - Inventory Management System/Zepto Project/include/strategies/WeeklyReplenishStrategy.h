#ifndef WEEKLY_REPLENISH_STRATEGY_H
#define WEEKLY_REPLENISH_STRATEGY_H

#include "ReplenishStrategy.h"

class WeeklyReplenishStrategy : public ReplenishStrategy
{
public:
    WeeklyReplenishStrategy() {}
    void replenish(InventoryManager *manager, std::map<int, int> itemsToReplenish) override;
};

#endif
