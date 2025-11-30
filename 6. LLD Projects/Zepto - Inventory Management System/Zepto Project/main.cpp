#include <iostream>
#include "include/utils/ZeptoHelper.h"
#include "include/models/User.h"
#include "include/managers/OrderManager.h"
#include "include/managers/DarkStoreManager.h"

using namespace std;

int main()
{
    // 1) Initialize.
    ZeptoHelper::initialize();

    // 2) A User comes on Platform
    User *user = new User("Hariom", 1.0, 1.0);
    cout << "\nUser with name " << user->name << " comes on platform" << endl;

    // 3) Show all available items via Zepto
    ZeptoHelper::showAllItems(user);

    // 4) User adds items to cart
    cout << "\nAdding items to cart\n";
    Cart *cart = user->getCart();
    cart->addItem(101, 4);
    cart->addItem(102, 3);
    cart->addItem(103, 2);

    // 5) Place Order
    OrderManager::getInstance()->placeOrder(user, user->getCart());

    // 6) Cleanup
    delete user;
    // DarkStoreManager singleton cleanup logic would typically go here
    // or be handled by a specific cleanup routine.

    return 0;
}
