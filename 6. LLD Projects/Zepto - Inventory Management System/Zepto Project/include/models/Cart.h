#ifndef CART_H
#define CART_H

#include <vector>
#include <utility>
#include "Product.h"

class Cart
{
public:
    std::vector<std::pair<Product *, int>> items;

    ~Cart();
    void addItem(int sku, int qty);
    double getTotal();
    std::vector<std::pair<Product *, int>> getItems();
};

#endif
