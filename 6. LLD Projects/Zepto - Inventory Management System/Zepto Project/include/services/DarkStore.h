#ifndef DARKSTORE_H
#define DARKSTORE_H

#include <string>
#include <vector>
#include <map>
#include <cmath>
#include "../managers/InventoryManager.h"
#include "../strategies/ReplenishStrategy.h"

class DarkStore
{
private:
    std::string name;
    double x, y;
    InventoryManager *inventoryManager;
    ReplenishStrategy *replenishStrategy;

public:
    DarkStore(std::string n, double x_coord, double y_coord);
    ~DarkStore();

    double distanceTo(double ux, double uy);
    void runReplenishment(std::map<int, int> itemsToReplenish);

    // Delegation Methods
    std::vector<Product *> getAllProducts();
    int checkStock(int sku);
    void removeStock(int sku, int qty);
    void addStock(int sku, int qty);

    // Getters & Setters
    void setReplenishStrategy(ReplenishStrategy *strategy);
    std::string getName();
    double getXCoordinate();
    double getYCoordinate();
    InventoryManager *getInventoryManager();
};

#endif
