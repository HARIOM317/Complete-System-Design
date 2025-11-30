#include "../../include/strategies/ReplenishStrategy.h"
#include "../../include/strategies/ThresholdReplenishStrategy.h"
#include "../../include/strategies/WeeklyReplenishStrategy.h"
#include "../../include/managers/InventoryManager.h"
#include <iostream>

using namespace std;

// Threshold Strategy Implementation
ThresholdReplenishStrategy::ThresholdReplenishStrategy(int threshold)
{
    this->threshold = threshold;
}

void ThresholdReplenishStrategy::replenish(InventoryManager *manager, map<int, int> itemsToReplenish)
{
    cout << "[ThresholdReplenish] Checking threshold... \n";
    for (auto it : itemsToReplenish)
    {
        int sku = it.first;
        int qtyToAdd = it.second;
        int current = manager->checkStock(sku);
        if (current < threshold)
        {
            manager->addStock(sku, qtyToAdd);
            cout << "  -> SKU " << sku << " was " << current
                 << ", replenished by " << qtyToAdd << endl;
        }
    }
}

// Weekly Strategy Implementation
void WeeklyReplenishStrategy::replenish(InventoryManager *manager, map<int, int> itemsToReplenish)
{
    cout << "[WeeklyReplenish] Weekly replenishment triggered for inventory.\n";
}
