
#include "Cart.h"
#include <iomanip>

void Cart::addProduct(Product product) {

    if (product.getStock() <= 0) {
        cout << "Product is out of stock!\n";
        return;
    }

    for (auto &item : items) {
        if (item.product.getId() == product.getId()) {

            if (item.quantity >= product.getStock()) {
                cout << "Maximum stock reached!\n";
                return;
            }

            item.quantity++;
            cout << "Product quantity increased!\n";
            return;
        }
    }

    CartItem item;
    item.product = product;
    item.quantity = 1;

    items.push_back(item);

    cout << "Product added to cart successfully!\n";
}

void Cart::removeProduct(int id) {

    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->product.getId() == id) {
            items.erase(it);
            cout << "Product removed successfully!\n";
            return;
        }
    }

    cout << "Product not found in cart!\n";
}

void Cart::displayCart() const {

    if (items.empty()) {
        cout << "\nYour cart is empty!\n";
        return;
    }

    cout << "\n========== YOUR CART ==========\n";

    for (const auto &item : items) {
        cout << "\nProduct: " << item.product.getName();
        cout << "\nQuantity: " << item.quantity;
        cout << "\nSubtotal: Rs. "
             << fixed << setprecision(2)
             << item.product.getPrice() * item.quantity;
        cout << "\n---------------------------\n";
    }

    cout << "Total: Rs. " << calculateTotal() << endl;
}

double Cart::calculateTotal() const {

    double total = 0;

    for (const auto &item : items) {
        total += item.product.getPrice() * item.quantity;
    }

    return total;
}

bool Cart::isEmpty() const {
    return items.empty();
}

const vector<CartItem>& Cart::getItems() const {
    return items;
}

void Cart::clearCart() {
    items.clear();
}
