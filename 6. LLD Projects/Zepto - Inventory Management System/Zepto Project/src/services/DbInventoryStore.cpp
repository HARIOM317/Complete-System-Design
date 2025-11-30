#include "../../include/services/DbInventoryStore.h"

using namespace std;

DbInventoryStore::DbInventoryStore()
{
    stock = new map<int, int>();
    products = new map<int, Product *>();
}

DbInventoryStore::~DbInventoryStore()
{
    for (auto it : *products)
    {
        delete it.second;
    }
    delete products;
    delete stock;
}

void DbInventoryStore::addProduct(Product *prod, int qty)
{
    int sku = prod->getSku();
    if (products->count(sku) == 0)
    {
        (*products)[sku] = prod;
    }
    else
    {
        delete prod;
    }
    (*stock)[sku] += qty;
}

void DbInventoryStore::removeProduct(int sku, int qty)
{
    if (stock->count(sku) == 0)
        return;

    int currentQuantity = (*stock)[sku];
    int remainingQuantity = currentQuantity - qty;
    if (remainingQuantity > 0)
    {
        (*stock)[sku] = remainingQuantity;
    }
    else
    {
        stock->erase(sku);
    }
}

int DbInventoryStore::checkStock(int sku)
{
    if (stock->count(sku) == 0)
        return 0;
    return (*stock)[sku];
}

vector<Product *> DbInventoryStore::listAvailableProducts()
{
    vector<Product *> available;
    for (auto it : *stock)
    {
        int sku = it.first;
        int qty = it.second;
        if (qty > 0 && products->count(sku))
        {
            available.push_back((*products)[sku]);
        }
    }
    return available;
}
