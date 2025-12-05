#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

// _____ FORWARD DECLARATION _____
class CardPayment;
class UpiPayment;
class WalletPayment;

// _____ VISITOR INTERFACE _____
class PaymentVisitor
{
public:
    virtual void visit(CardPayment &) = 0;
    virtual void visit(UpiPayment &) = 0;
    virtual void visit(WalletPayment &) = 0;

    virtual ~PaymentVisitor() = default;
};

// _____ ELEMENTS INTERFACE _____
class PaymentMethod
{
public:
    virtual void accept(PaymentVisitor &v) = 0;
    virtual ~PaymentMethod() = default;
};

// CONCRETE PAYMENT METHODS (ELEMENTS)
class CardPayment : public PaymentMethod
{
public:
    string cardNumber;
    double amount;

    CardPayment(string c, double a) : cardNumber(c), amount(a) {}

    void accept(PaymentVisitor &v) override
    {
        v.visit(*this);
    }
};

class UpiPayment : public PaymentMethod
{
public:
    string upiId;
    double amount;

    UpiPayment(string id, double a) : upiId(id), amount(a) {}

    void accept(PaymentVisitor &v) override
    {
        v.visit(*this);
    }
};

class WalletPayment : public PaymentMethod
{
public:
    string walletId;
    double amount;

    WalletPayment(string id, double a) : walletId(id), amount(a) {}

    void accept(PaymentVisitor &v) override
    {
        v.visit(*this);
    }
};

// _____ CONCRETE VISITORS (OPERATIONS) _____
class FraudCheckVisitor : public PaymentVisitor
{
public:
    void visit(CardPayment &cp) override
    {
        cout << "[FraudCheck] Checking card: " << cp.cardNumber << endl;
    }

    void visit(UpiPayment &upi) override
    {
        cout << "[FraudCheck] Checking UPI: " << upi.upiId << endl;
    }

    void visit(WalletPayment &wp) override
    {
        cout << "[FraudCheck] Checking Wallet: " << wp.walletId << endl;
    }
};

class EncryptTransactionVisitor : public PaymentVisitor
{
public:
    void visit(CardPayment &cp) override
    {
        cout << "[Encrypting Transaction] ----> Card: " << cp.cardNumber << endl;
    }

    void visit(UpiPayment &upi) override
    {
        cout << "[Encrypting Transaction] ----> UPI: " << upi.upiId << endl;
    }

    void visit(WalletPayment &wp) override
    {
        cout << "[Encrypting Transaction] ----> Wallet: " << wp.walletId << endl;
    }
};

class FeeCalculationVisitor : public PaymentVisitor
{
public:
    double fee = 0;

    void visit(CardPayment &cp) override
    {
        fee = cp.amount * 0.02; // 2% card fee
        cout << "[FeeCalculation] Card fee: " << fee << endl;
    }

    void visit(UpiPayment &upi) override
    {
        fee = upi.amount * 0.005; // 0.5% UPI fee
        cout << "[FeeCalculation] UPI fee: " << fee << endl;
    }

    void visit(WalletPayment &wp) override
    {
        fee = wp.amount * 0.01; // 1% Wallet fee
        cout << "[FeeCalculation] Wallet fee: " << fee << endl;
    }
};

class LoggingVisitor : public PaymentVisitor
{
public:
    void visit(CardPayment &cp) override
    {
        cout << "[Log] Card Payment of " << cp.amount << " from " << cp.cardNumber << endl;
    }

    void visit(UpiPayment &upi) override
    {
        cout << "[Log] UPI Payment of " << upi.amount << " from " << upi.upiId << endl;
    }

    void visit(WalletPayment &wp) override
    {
        cout << "[Log] Wallet Payment of " << wp.amount << " from " << wp.walletId << endl;
    }
};

int main()
{
    vector<shared_ptr<PaymentMethod>> payments;

    payments.push_back(make_shared<CardPayment>("4111-1111-1111-1111", 1000));
    payments.push_back(make_shared<UpiPayment>("hariom@upi", 500));
    payments.push_back(make_shared<WalletPayment>("wallet123", 800));

    FraudCheckVisitor fraud;
    EncryptTransactionVisitor encrypt;
    FeeCalculationVisitor feeCalc;
    LoggingVisitor logV;

    cout << "\n--- Fraud Check ---\n";
    for (auto &p : payments)
        p->accept(fraud);

    cout << "\n--- Encrypting Transaction ---\n";
    for (auto &p : payments)
        p->accept(encrypt);

    cout << "\n--- Fee Calculation ---\n";
    for (auto &p : payments)
        p->accept(feeCalc);

    cout << "\n--- Logging ---\n";
    for (auto &p : payments)
        p->accept(logV);

    return 0;
}