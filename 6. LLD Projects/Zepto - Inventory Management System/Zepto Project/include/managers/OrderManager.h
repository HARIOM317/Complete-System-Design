#ifndef ORDER_MANAGER_H
#define ORDER_MANAGER_H

#include <vector>
#include "../models/Order.h"
#include "../models/User.h"
#include "../models/Cart.h"

class OrderManager
{
private:
    std::vector<Order *> *orders;
    static OrderManager *instance;
    OrderManager();

public:
    static OrderManager *getInstance();
    void placeOrder(User *user, Cart *cart);
    std::vector<Order *> getAllOrders();
    ~OrderManager();
};

#endif
