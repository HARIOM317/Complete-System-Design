#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include <utility>
#include "User.h"
#include "Product.h"
#include "DeliveryPartner.h"

class Order
{
public:
    static int nextId;
    int orderId;
    User *user;
    std::vector<std::pair<Product *, int>> items;
    std::vector<DeliveryPartner *> partners;
    double totalAmount;

    Order(User *u);
};

#endif
