#include "../../include/services/DarkStore.h"
#include "../../include/services/DbInventoryStore.h"
#include "../../include/factories/ProductFactory.h"

using namespace std;

DarkStore::DarkStore(string n, double x_coord, double y_coord)
{
    name = n;
    x = x_coord;
    y = y_coord;
    inventoryManager = new InventoryManager(new DbInventoryStore);
    replenishStrategy = nullptr;
}

DarkStore::~DarkStore()
{
    delete inventoryManager;
    if (replenishStrategy)
        delete replenishStrategy;
}

double DarkStore::distanceTo(double ux, double uy)
{
    return sqrt((x - ux) * (x - ux) + (y - uy) * (y - uy));
}

void DarkStore::runReplenishment(map<int, int> itemsToReplenish)
{
    if (replenishStrategy)
    {
        replenishStrategy->replenish(inventoryManager, itemsToReplenish);
    }
}

vector<Product *> DarkStore::getAllProducts()
{
    return inventoryManager->getAvailableProducts();
}

int DarkStore::checkStock(int sku)
{
    return inventoryManager->checkStock(sku);
}

void DarkStore::removeStock(int sku, int qty)
{
    inventoryManager->removeStock(sku, qty);
}

void DarkStore::addStock(int sku, int qty)
{
    inventoryManager->addStock(sku, qty);
}

void DarkStore::setReplenishStrategy(ReplenishStrategy *strategy)
{
    this->replenishStrategy = strategy;
}

string DarkStore::getName() { return this->name; }
double DarkStore::getXCoordinate() { return this->x; }
double DarkStore::getYCoordinate() { return this->y; }
InventoryManager *DarkStore::getInventoryManager() { return this->inventoryManager; }
