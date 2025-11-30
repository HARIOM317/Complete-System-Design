#ifndef THRESHOLD_REPLENISH_STRATEGY_H
#define THRESHOLD_REPLENISH_STRATEGY_H

#include "ReplenishStrategy.h"

class ThresholdReplenishStrategy : public ReplenishStrategy
{
private:
    int threshold;

public:
    ThresholdReplenishStrategy(int threshold);
    void replenish(InventoryManager *manager, std::map<int, int> itemsToReplenish) override;
};

#endif
