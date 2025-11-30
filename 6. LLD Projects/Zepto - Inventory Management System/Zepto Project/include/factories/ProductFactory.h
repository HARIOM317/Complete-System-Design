#ifndef PRODUCT_FACTORY_H
#define PRODUCT_FACTORY_H

#include "../models/Product.h"

class ProductFactory
{
public:
    static Product *createProduct(int sku);
};

#endif
