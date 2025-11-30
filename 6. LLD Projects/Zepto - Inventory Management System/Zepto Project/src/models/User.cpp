#include "../../include/models/User.h"

User::User(std::string n, double x_coord, double y_coord)
{
    name = n;
    x = x_coord;
    y = y_coord;
    cart = new Cart();
}

User::~User()
{
    delete cart;
}

Cart *User::getCart()
{
    return cart;
}
