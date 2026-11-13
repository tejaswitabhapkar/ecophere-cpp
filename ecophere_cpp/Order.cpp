
#include "Order.h"
#include "Payment.h"
#include <fstream>
#include <iomanip>
#include <memory>
#include <sstream>

int Order::nextOrderId = 1;

void Order::placeOrder(
    const Customer& customer,
    Cart& cart,
    Admin& admin) {

    if (cart.isEmpty()) {
        cout << "\nYour cart is empty!\n";
        return;
    }

    // Check stock before checkout.
    for (const auto &item : cart.getItems()) {

        Product* p = admin.findProduct(
            item.product.getId());

        if (p == nullptr ||
            p->getStock() < item.quantity) {

            cout << "Insufficient stock for "
                 << item.product.getName() << endl;
            return;
        }
    }

    double total = cart.calculateTotal();

    cout << "\n========== ORDER BILL ==========\n";
    cout << "Customer: " << customer.getName() << endl;
    cout << "Email: " << customer.getEmail() << endl;

    for (const auto &item : cart.getItems()) {
        cout << item.product.getName()
             << " x " << item.quantity
             << " = Rs. "
             << fixed << setprecision(2)
             << item.product.getPrice() * item.quantity
             << endl;
    }

    cout << "\nTotal Amount: Rs. " << total << endl;

    cout << "\nSelect Payment Method:\n";
    cout << "1. UPI\n";
    cout << "2. Card\n";
    cout << "3. Cash on Delivery\n";

    int choice;

    cout << "Enter Choice: ";

    if (!(cin >> choice) || choice < 1 || choice > 3) {
        cout << "Invalid payment choice!\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    cin.ignore(10000, '\n');

    string method;
    unique_ptr<Payment> paymentMethod;

    if (choice == 1) {
        method = "UPI";
        paymentMethod = make_unique<UPIPayment>();
    }
    else if (choice == 2) {
        method = "Card";
        paymentMethod = make_unique<CardPayment>();
    }
    else {
        method = "Cash on Delivery";
        paymentMethod = make_unique<CODPayment>();
    }

    if (!paymentMethod->pay(total)) {
        cout << "Payment failed!\n";
        return;
    }

    ofstream out("orders.txt", ios::app);

    if (!out) {
        cout << "Unable to save order!\n";
        return;
    }

    int orderId = nextOrderId++;

    for (const auto &item : cart.getItems()) {

        out << orderId << "|"
            << customer.getId() << "|"
            << customer.getName() << "|"
            << item.product.getId() << "|"
            << item.product.getName() << "|"
            << item.quantity << "|"
            << item.product.getPrice() * item.quantity
            << "|" << method << "\n";
    }

    out.close();

    // Update product stock.
    for (const auto &item : cart.getItems()) {
        admin.reduceStock(
            item.product.getId(),
            item.quantity
        );
    }

    cart.clearCart();

    cout << "\n================================\n";
    cout << "       ORDER PLACED SUCCESSFULLY\n";
    cout << "================================\n";

    cout << "Order ID: " << orderId << endl;
    cout << "Payment Method: " << method << endl;
    cout << "Total Amount: Rs. " << total << endl;

    cout << "\nThank you for choosing EcoSphere!\n";
}

void Order::viewOrders(int customerId) {

    ifstream in("orders.txt");

    if (!in) {
        cout << "\nNo orders available!\n";
        return;
    }

    string line;
    bool found = false;

    cout << "\n========== MY ORDERS ==========\n";

    while (getline(in, line)) {

        stringstream ss(line);

        string fields[8];

        for (int i = 0; i < 8; i++) {
            if (!getline(ss, fields[i], '|')) {
                break;
            }
        }

        try {
            if (fields[1] != "" &&
                stoi(fields[1]) == customerId) {

                cout << "\nOrder ID: " << fields[0];
                cout << "\nProduct: " << fields[4];
                cout << "\nQuantity: " << fields[5];
                cout << "\nAmount: Rs. " << fields[6];
                cout << "\nPayment: " << fields[7];
                cout << "\n-----------------------------\n";

                found = true;
            }
        }
        catch (...) {
            // Ignore invalid records.
        }
    }

    in.close();

    if (!found) {
        cout << "You have not placed any orders yet.\n";
    }
}
