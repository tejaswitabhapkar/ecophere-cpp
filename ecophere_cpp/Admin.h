
#ifndef ADMIN_H
#define ADMIN_H

#include "Product.h"
#include <vector>

class Admin {
private:
    vector<Product> products;

    void loadProducts();
    void saveProducts() const;

public:
    Admin();

    void displayProducts() const;
    void addProduct();
    void searchProduct() const;

    Product* findProduct(int id);
    void reduceStock(int id, int quantity);
};

#endif
