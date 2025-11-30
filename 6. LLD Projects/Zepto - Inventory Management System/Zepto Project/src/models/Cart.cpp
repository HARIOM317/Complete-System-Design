#include "../../include/models/Cart.h"
#include "../../include/factories/ProductFactory.h"
#include <iostream>

using namespace std;

void Cart::addItem(int sku, int qty)
{
    Product *prod = ProductFactory::createProduct(sku);
    items.push_back(make_pair(prod, qty));
    cout << "[Cart] Added SKU " << sku << " (" << prod->getName()
         << ") x" << qty << endl;
}

double Cart::getTotal()
{
    double sum = 0.0;
    for (auto &it : items)
    {
        sum += (it.first->getPrice() * it.second);
    }
    return sum;
}

vector<pair<Product *, int>> Cart::getItems()
{
    return items;
}

Cart::~Cart()
{
    for (auto &it : items)
    {
        delete it.first;
    }
}
