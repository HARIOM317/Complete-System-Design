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

// Violating SRP: Order class is handling multiple responsibilities
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

    // Responsibility-1: Calculates total price in cart
    double calculateTotalPrice()
    {
        double total = 0;
        for (auto p : products)
        {
            total += p->price;
        }
        return total;
    }

    // Responsibility-2: Save to database
    void saveToDatabase()
    {
        cout << "Saving shopping cart to database..." << endl;
    }

    // Responsibility-3: Print invoice
    void printInvoice()
    {
        cout << "Shopping Cart Invoice:\n";
        for (auto p : products)
        {
            cout << p->name << " - Rs " << p->price << endl;
        }
        cout << "Total: Rs " << calculateTotalPrice() << endl;
    }

    // Responsibility-4: Notifications
    void sendEmailToCustomer()
    {
        cout << "Sending email to customer..." << endl;
    }
};

int main()
{
    Order *cart = new Order();

    cart->addProduct(new Product("Laptop", 50000));
    cart->addProduct(new Product("Mouse", 1500));

    cart->printInvoice();
    cart->saveToDatabase();
    cart->sendEmailToCustomer();

    return 0;
}