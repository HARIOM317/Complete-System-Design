#ifndef USER_H
#define USER_H

#include <string>
#include "Cart.h"

class User
{
public:
    std::string name;
    double x, y;
    Cart *cart;

    User(std::string n, double x_coord, double y_coord);
    ~User();
    Cart *getCart();
};

#endif
