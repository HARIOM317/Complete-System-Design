#include "../../include/models/Order.h"

int Order::nextId = 1;

Order::Order(User *u)
{
    orderId = nextId++;
    user = u;
    totalAmount = 0.0;
}
