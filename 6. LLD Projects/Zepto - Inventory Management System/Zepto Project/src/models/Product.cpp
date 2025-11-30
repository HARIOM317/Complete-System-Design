#include "../../include/models/Product.h"

Product::Product(int id, std::string nm, double pr)
{
    sku = id;
    name = nm;
    price = pr;
}

int Product::getSku() { return this->sku; }
std::string Product::getName() { return this->name; }
double Product::getPrice() { return this->price; }
