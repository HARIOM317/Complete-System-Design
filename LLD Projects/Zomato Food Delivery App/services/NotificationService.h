#ifndef NOTIFICATION_SERVICE_H
#define NOTIFICATION_SERVICE_H

#include <iostream>
#include "../models/Order.h"
using namespace std;

class NotificationService
{
public:
    static void notify(Order *order)
    {
        cout << "\n\nNotification: New " << order->getType() << " order placed!\n";
        cout << "-----------------------------------------\n";
        cout << "Order ID: " << order->getOrderId() << endl;
        cout << "Customer: " << order->getUser()->getName() << endl;
        cout << "Restaurant: " << order->getRestaurant()->getName() << endl;
        cout << "\nItems Ordered:\n";

        const vector<MenuItem> &items = order->getItems();
        for (const auto &item : items)
        {
            cout << "   - " << item.getName() << " (₹ " << item.getPrice() << ")\n";
        }

        cout << "\nTotal : ₹ " << order->getTotal() << endl;
        cout << "Scheduled For: " << order->getScheduled() << endl;
        cout << "Payment: Done" << endl;
        cout << "-----------------------------------------\n\n";
    }
};

#endif // NOTIFICATION_SERVICE_H