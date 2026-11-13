
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <string>
using namespace std;

class Customer {
private:
    int id;
    string name;
    string email;
    string password;

public:
    Customer();
    Customer(int, string, string, string);

    int getId() const;
    string getName() const;
    string getEmail() const;

    static Customer registerCustomer();
    static Customer loginCustomer();

    bool isValid() const;
};

#endif
