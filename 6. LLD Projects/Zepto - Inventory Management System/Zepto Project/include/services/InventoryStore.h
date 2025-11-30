#ifndef INVENTORY_STORE_H
#define INVENTORY_STORE_H

#include <vector>
#include "../models/Product.h"

class InventoryStore
{
public:
    virtual ~InventoryStore() {}
    virtual void addProduct(Product *prod, int qty) = 0;
    virtual void removeProduct(int sku, int qty) = 0;
    virtual int checkStock(int sku) = 0;
    virtual std::vector<Product *> listAvailableProducts() = 0;
};

#endif
