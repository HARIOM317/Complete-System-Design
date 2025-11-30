#ifndef DELIVERY_PARTNER_H
#define DELIVERY_PARTNER_H

#include <string>

class DeliveryPartner
{
public:
    std::string name;
    DeliveryPartner(std::string n) : name(n) {}
};

#endif
