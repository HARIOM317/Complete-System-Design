#include "../../include/managers/InventoryManager.h"
#include "../../include/factories/ProductFactory.h"
#include <iostream>

using namespace std;

InventoryManager::InventoryManager(InventoryStore *store)
{
    this->store = store;
}

void InventoryManager::addStock(int sku, int qty)
{
    Product *prod = ProductFactory::createProduct(sku);
    store->addProduct(prod, qty);
    cout << "[InventoryManager] Added SKU " << sku << " Qty " << qty << endl;
}

void InventoryManager::removeStock(int sku, int qty)
{
    store->removeProduct(sku, qty);
}

int InventoryManager::checkStock(int sku)
{
    return store->checkStock(sku);
}

vector<Product *> InventoryManager::getAvailableProducts()
{
    return store->listAvailableProducts();
}
