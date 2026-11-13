
#ifndef CART_H
#define CART_H

#include "Product.h"
#include <vector>

struct CartItem {
    Product product;
    int quantity;
};

class Cart {
private:
    vector<CartItem> items;

public:
    void addProduct(Product product);
    void removeProduct(int id);
    void displayCart() const;
    double calculateTotal() const;
    bool isEmpty() const;

    const vector<CartItem>& getItems() const;
    void clearCart();
};

#endif
