
#include "Product.h"
#include <iomanip>

Product::Product() {
    id = 0;
    name = "";
    category = "";
    price = 0;
    stock = 0;
}

Product::Product(int id, string name, string category,
                 double price, int stock) {
    this->id = id;
    this->name = name;
    this->category = category;
    this->price = price;
    this->stock = stock;
}

int Product::getId() const {
    return id;
}

string Product::getName() const {
    return name;
}

string Product::getCategory() const {
    return category;
}

double Product::getPrice() const {
    return price;
}

int Product::getStock() const {
    return stock;
}

void Product::setStock(int stock) {
    this->stock = stock;
}

void Product::display() const {
    cout << left << setw(6) << id
         << setw(28) << name
         << setw(18) << category
         << "Rs. " << fixed << setprecision(2)
         << price
         << " | Stock: " << stock << endl;
}
