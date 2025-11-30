#include "../../include/managers/OrderManager.h"
#include "../../include/managers/DarkStoreManager.h"
#include "../../include/factories/ProductFactory.h"
#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

OrderManager *OrderManager::instance = nullptr;

OrderManager::OrderManager()
{
    orders = new vector<Order *>();
}

OrderManager *OrderManager::getInstance()
{
    if (instance == nullptr)
    {
        instance = new OrderManager();
    }
    return instance;
}

void OrderManager::placeOrder(User *user, Cart *cart)
{
    cout << "\n[OrderManager] Placing Order for: " << user->name << "\n";

    vector<pair<Product *, int>> requestedItems = cart->getItems();

    // 1) Find nearby dark stores within 5 KM
    double maxDist = 5.0;
    vector<DarkStore *> nearbyDarkStores = DarkStoreManager::getInstance()->getNearbyDarkStores(user->x, user->y, maxDist);

    if (nearbyDarkStores.empty())
    {
        cout << "  No dark stores within 5 KM. Cannot fulfill order.\n";
        return;
    }

    // 2) Check if closest store has all items
    DarkStore *firstStore = nearbyDarkStores.front();

    bool allInFirst = true;
    for (pair<Product *, int> &item : requestedItems)
    {
        int sku = item.first->getSku();
        int qty = item.second;
        if (firstStore->checkStock(sku) < qty)
        {
            allInFirst = false;
            break;
        }
    }

    Order *order = new Order(user);

    // One delivery partner required
    if (allInFirst)
    {
        cout << "  All items at: " << firstStore->getName() << "\n";
        for (pair<Product *, int> &item : requestedItems)
        {
            int sku = item.first->getSku();
            int qty = item.second;
            firstStore->removeStock(sku, qty);
            order->items.push_back({item.first, qty});
        }
        order->totalAmount = cart->getTotal();
        order->partners.push_back(new DeliveryPartner("Partner1"));
        cout << "  Assigned Delivery Partner: Partner1\n";
    }
    // Multiple delivery partners required
    else
    {
        cout << "  Splitting order across stores...\n";
        map<int, int> allItems; // SKU --> Qty
        for (pair<Product *, int> &item : requestedItems)
        {
            allItems[item.first->getSku()] = item.second;
        }

        int partnerId = 1;
        for (DarkStore *store : nearbyDarkStores)
        {
            if (allItems.empty())
                break;
            cout << "   Checking: " << store->getName() << "\n";

            bool assigned = false;
            vector<int> toErase;

            for (auto &[sku, qtyNeeded] : allItems)
            {
                int availableQty = store->checkStock(sku);
                if (availableQty <= 0)
                    continue;

                int takenQty = min(availableQty, qtyNeeded);
                store->removeStock(sku, takenQty);

                cout << "     " << store->getName() << " supplies SKU " << sku
                     << " x" << takenQty << "\n";

                order->items.push_back({ProductFactory::createProduct(sku), takenQty});

                if (qtyNeeded > takenQty)
                {
                    allItems[sku] = qtyNeeded - takenQty;
                }
                else
                {
                    toErase.push_back(sku);
                }
                assigned = true;
            }

            for (int sku : toErase)
                allItems.erase(sku);

            if (assigned)
            {
                string pname = "Partner" + to_string(partnerId++);
                order->partners.push_back(new DeliveryPartner(pname));
                cout << "     Assigned: " << pname << " for " << store->getName() << "\n";
            }
        }

        if (!allItems.empty())
        {
            cout << "  Could not fulfill:\n";
            for (auto &[sku, qty] : allItems)
            {
                cout << "    SKU " << sku << " x" << qty << "\n";
            }
        }

        double sum = 0;
        for (auto &item : order->items)
        {
            sum += item.first->getPrice() * item.second;
        }
        order->totalAmount = sum;
    }

    cout << "\n[OrderManager] Order #" << order->orderId << " Summary:\n";
    cout << "  User: " << user->name << "\n  Items:\n";
    for (auto &item : order->items)
    {
        cout << "    SKU " << item.first->getSku()
             << " (" << item.first->getName() << ") x" << item.second
             << " @ " << item.first->getPrice() << "\n";
    }
    cout << "  Total: " << order->totalAmount << "\n  Partners:\n";
    for (auto *dp : order->partners)
    {
        cout << "    " << dp->name << "\n";
    }
    cout << endl;

    orders->push_back(order);
    for (auto *dp : order->partners)
        delete dp;
    for (auto &item : order->items)
        delete item.first;
}

vector<Order *> OrderManager::getAllOrders()
{
    return *orders;
}

OrderManager::~OrderManager()
{
    for (auto ord : *orders)
    {
        delete ord;
    }
    delete orders;
}
