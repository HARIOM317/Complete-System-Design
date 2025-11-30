#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include "../services/InventoryStore.h"
#include <vector>

class InventoryManager
{
    InventoryStore *store;

public:
    InventoryManager(InventoryStore *store);
    void addStock(int sku, int qty);
    void removeStock(int sku, int qty);
    int checkStock(int sku);
    std::vector<Product *> getAvailableProducts();
};

#endif
