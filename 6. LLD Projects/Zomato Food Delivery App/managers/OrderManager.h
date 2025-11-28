#ifndef ORDER_MANAGER_H
#define ORDER_MANAGER_H

#include <iostream>
#include <vector>
#include "../models/Order.h"

using namespace std;

// Singleton class
class OrderManager
{
private:
    vector<Order *> orders;
    static OrderManager *instance;

    OrderManager()
    {
        // Private Constructor
    }

public:
    static OrderManager *getInstance()
    {
        if (!instance)
        {
            instance = new OrderManager();
        }
        return instance;
    }

    void addOrder(Order *order)
    {
        orders.push_back(order);
    }

    void listOrder()
    {
        cout << "\n\n_____ All Orders _____\n";
        for (auto order : orders)
        {
            cout << order->getType()
                 << " order for "
                 << order->getUser()->getName()
                 << " | Total: ₹ " << order->getTotal()
                 << " | At: " << order->getScheduled()
                 << "\n\n";
        }
    }
};

OrderManager *OrderManager::instance = nullptr;

#endif // ORDER_MANAGER_H