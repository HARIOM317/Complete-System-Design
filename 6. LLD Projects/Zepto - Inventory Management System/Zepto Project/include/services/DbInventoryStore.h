#ifndef DB_INVENTORY_STORE_H
#define DB_INVENTORY_STORE_H

#include "InventoryStore.h"
#include <map>

class DbInventoryStore : public InventoryStore
{
private:
    std::map<int, int> *stock;
    std::map<int, Product *> *products;

public:
    DbInventoryStore();
    ~DbInventoryStore();
    void addProduct(Product *prod, int qty) override;
    void removeProduct(int sku, int qty) override;
    int checkStock(int sku) override;
    std::vector<Product *> listAvailableProducts() override;
};

#endif
