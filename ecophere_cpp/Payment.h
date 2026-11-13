
#ifndef PAYMENT_H
#define PAYMENT_H

#include <iostream>
using namespace std;

class Payment {
public:
    virtual bool pay(double amount) = 0;

    virtual ~Payment() {}
};

class UPIPayment : public Payment {
public:
    bool pay(double amount) override {
        cout << "\nUPI Payment Simulation\n";
        cout << "Amount: Rs. " << amount << endl;
        cout << "Payment Successful!\n";
        return true;
    }
};

class CardPayment : public Payment {
public:
    bool pay(double amount) override {
        cout << "\nCard Payment Simulation\n";
        cout << "Amount: Rs. " << amount << endl;
        cout << "Payment Successful!\n";
        return true;
    }
};

class CODPayment : public Payment {
public:
    bool pay(double amount) override {
        cout << "\nCash on Delivery Selected\n";
        cout << "Amount Payable: Rs. " << amount << endl;
        return true;
    }
};

#endif
