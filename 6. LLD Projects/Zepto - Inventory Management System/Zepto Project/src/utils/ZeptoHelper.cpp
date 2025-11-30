#include "../../include/utils/ZeptoHelper.h"
#include "../../include/managers/DarkStoreManager.h"
#include "../../include/strategies/ThresholdReplenishStrategy.h"
#include <iostream>
#include <map>

using namespace std;

void ZeptoHelper::showAllItems(User *user)
{
    cout << "\n[Zepto] All Available products within 5 KM for " << user->name << ":\n";

    DarkStoreManager *dsManager = DarkStoreManager::getInstance();
    vector<DarkStore *> nearbyStores = dsManager->getNearbyDarkStores(user->x, user->y, 5.0);

    map<int, double> skuToPrice;
    map<int, string> skuToName;

    for (DarkStore *darkStore : nearbyStores)
    {
        vector<Product *> products = darkStore->getAllProducts();
        for (Product *product : products)
        {
            int sku = product->getSku();
            if (skuToPrice.count(sku) == 0)
            {
                skuToPrice[sku] = product->getPrice();
                skuToName[sku] = product->getName();
            }
        }
    }

    for (auto &entry : skuToPrice)
    {
        int sku = entry.first;
        double price = entry.second;
        cout << "  SKU " << sku << " - " << skuToName[sku] << " @ " << price << "\n";
    }
}

void ZeptoHelper::initialize()
{
    auto dsManager = DarkStoreManager::getInstance();

    // DarkStore A
    DarkStore *darkStoreA = new DarkStore("DarkStoreA", 0.0, 0.0);
    darkStoreA->setReplenishStrategy(new ThresholdReplenishStrategy(3));
    cout << "\nAdding stocks in DarkStoreA...." << endl;
    darkStoreA->addStock(101, 5);
    darkStoreA->addStock(102, 2);

    // DarkStore B
    DarkStore *darkStoreB = new DarkStore("DarkStoreB", 4.0, 1.0);
    darkStoreB->setReplenishStrategy(new ThresholdReplenishStrategy(3));
    cout << "\nAdding stocks in DarkStoreB...." << endl;
    darkStoreB->addStock(101, 3);
    darkStoreB->addStock(103, 10);

    // DarkStore C
    DarkStore *darkStoreC = new DarkStore("DarkStoreC", 2.0, 3.0);
    darkStoreC->setReplenishStrategy(new ThresholdReplenishStrategy(3));
    cout << "\nAdding stocks in DarkStoreC...." << endl;
    darkStoreC->addStock(102, 5);
    darkStoreC->addStock(201, 7);

    dsManager->registerDarkStore(darkStoreA);
    dsManager->registerDarkStore(darkStoreB);
    dsManager->registerDarkStore(darkStoreC);
}
