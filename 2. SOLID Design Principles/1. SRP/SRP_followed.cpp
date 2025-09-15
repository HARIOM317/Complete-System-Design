#include <iostream>
#include <vector>

using namespace std;

// Product class representing any item of any E-Commerce
class Product
{
public:
    string name;
    double price;

    Product(string name, double price)
    {
        this->name = name;
        this->price = price;
    }
};

// 1. Order: (Responsibility: Only responsible for Cart related business logic)
class Order
{
private:
    vector<Product *> products;

public:
    void addProduct(Product *p)
    {
        products.push_back(p);
    }

    const vector<Product *> &getProducts()
    {
        return products;
    }

    // Calculates total price in cart
    double calculateTotalPrice()
    {
        double total = 0;
        for (auto p : products)
        {
            total += p->price;
        }
        return total;
    }
};

// _____________________________________

// 2. OrderRepository: (Responsibility: Only responsible for saving cart to DB)
class OrderRepository
{
private:
    Order *cart; // association

public:
    OrderRepository(Order *cart)
    {
        this->cart = cart;
    }

    // Save to database
    void saveToDatabase()
    {
        cout << "Saving shopping cart to database..." << endl;
    }
};

// _____________________________________

// 3. ShoppingCartPrinter: (Responsibility: Only responsible for printing invoices)
class ShoppingCartPrinter
{
private:
    Order *cart; // association

public:
    ShoppingCartPrinter(Order *cart)
    {
        this->cart = cart;
    }

    // Print invoice
    void printInvoice()
    {
        cout << "Shopping Cart Invoice:\n";
        for (auto p : cart->getProducts())
        {
            cout << p->name << " - Rs " << p->price << endl;
        }
        cout << "Total: Rs " << cart->calculateTotalPrice() << endl;
    }
};

// _____________________________________

// 4. NotificationService: (Responsibility: Only responsible to send notifications)
class NotificationService
{
private:
    Order *cart; // association

public:
    NotificationService(Order *cart)
    {
        this->cart = cart;
    }

    // Send email to customer
    void sendEmailToCustomer()
    {
        cout << "Sending email to customer..." << endl;
    }
};

int main()
{
    // Correctly Following SRP (Single Responsibility Principle)
    Order *cart = new Order();
    cart->addProduct(new Product("Laptop", 50000));
    cart->addProduct(new Product("Mouse", 1500));

    ShoppingCartPrinter *printer = new ShoppingCartPrinter(cart);
    printer->printInvoice();

    OrderRepository *db = new OrderRepository(cart);
    db->saveToDatabase();

    NotificationService *notification = new NotificationService(cart);
    notification->sendEmailToCustomer();

    return 0;
}