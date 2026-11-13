
#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>
using namespace std;

class Product {
private:
    int id;
    string name;
    string category;
    double price;
    int stock;

public:
    Product();
    Product(int, string, string, double, int);

    int getId() const;
    string getName() const;
    string getCategory() const;
    double getPrice() const;
    int getStock() const;

    void setStock(int);
    void display() const;
};

#endif
