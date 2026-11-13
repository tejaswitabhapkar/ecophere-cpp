
#include <iostream>
#include <limits>

#include "Product.h"
#include "Customer.h"
#include "Cart.h"
#include "Admin.h"
#include "Order.h"

using namespace std;

void showHome() {

    cout << "\n";
    cout << "============================================\n";
    cout << "             WELCOME TO ECOSPHERE\n";
    cout << "       Sustainable and Eco-Friendly Products\n";
    cout << "============================================\n";

    cout << "Choose Sustainability. Choose EcoSphere!\n";
}

void adminMenu(Admin &admin) {

    int choice;

    while (true) {

        cout << "\n========== ADMIN PANEL ==========\n";

        cout << "1. Display Products\n";
        cout << "2. Add New Product\n";
        cout << "3. Search Product\n";
        cout << "4. Logout\n";

        cout << "\nEnter Choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input!\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        cin.ignore(10000, '\n');

        switch (choice) {

            case 1:
                admin.displayProducts();
                break;

            case 2:
                admin.addProduct();
                break;

            case 3:
                admin.searchProduct();
                break;

            case 4:
                cout << "Admin Logged Out!\n";
                return;

            default:
                cout << "Invalid Choice!\n";
        }
    }
}

void customerMenu(Customer &customer, Admin &admin) {

    Cart cart;
    int choice;

    while (true) {

        cout << "\n========== CUSTOMER MENU ==========\n";

        cout << "Welcome, " << customer.getName() << "!\n";

        cout << "\n1. View All Products\n";
        cout << "2. Search Products\n";
        cout << "3. Add Product to Cart\n";
        cout << "4. View Cart\n";
        cout << "5. Remove Product from Cart\n";
        cout << "6. Checkout and Place Order\n";
        cout << "7. View My Orders\n";
        cout << "8. Logout\n";

        cout << "\nEnter Your Choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input!\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        cin.ignore(10000, '\n');

        switch (choice) {

            case 1:
                admin.displayProducts();
                break;

            case 2:
                admin.searchProduct();
                break;

            case 3: {

                admin.displayProducts();

                int id;

                cout << "\nEnter Product ID to Add: ";

                if (!(cin >> id)) {
                    cout << "Invalid product ID!\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                    break;
                }

                cin.ignore(10000, '\n');

                Product* p = admin.findProduct(id);

                if (p != nullptr) {
                    cart.addProduct(*p);
                }
                else {
                    cout << "Product Not Found!\n";
                }

                break;
            }

            case 4:
                cart.displayCart();
                break;

            case 5: {

                int id;

                cout << "Enter Product ID to Remove: ";

                if (!(cin >> id)) {
                    cout << "Invalid product ID!\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                    break;
                }

                cin.ignore(10000, '\n');

                cart.removeProduct(id);
                break;
            }

            case 6:
                Order::placeOrder(customer, cart, admin);
                break;

            case 7:
                Order::viewOrders(customer.getId());
                break;

            case 8:
                cout << "Customer Logged Out!\n";
                return;

            default:
                cout << "Invalid Choice!\n";
        }
    }
}

int main() {

    Admin admin;

    int choice;

    showHome();

    while (true) {

        cout << "\n========== MAIN MENU ==========\n";

        cout << "1. Customer Registration\n";
        cout << "2. Customer Login\n";
        cout << "3. Admin Login\n";
        cout << "4. Exit Application\n";

        cout << "\nEnter Your Choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input!\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        cin.ignore(10000, '\n');

        switch (choice) {

            case 1: {

                Customer customer =
                    Customer::registerCustomer();

                if (customer.isValid()) {
                    customerMenu(customer, admin);
                }

                break;
            }

            case 2: {

                Customer customer =
                    Customer::loginCustomer();

                if (customer.isValid()) {
                    customerMenu(customer, admin);
                }

                break;
            }

            case 3: {

                string password;

                cout << "Enter Admin Password: ";
                getline(cin, password);

                if (password == "1234") {

                    cout << "\nAdmin Login Successful!\n";

                    adminMenu(admin);
                }
                else {
                    cout << "\nIncorrect Admin Password!\n";
                }

                break;
            }

            case 4:

                cout << "\nThank You for Visiting EcoSphere!\n";
                cout << "Make Every Purchase Sustainable!\n";

                return 0;

            default:

                cout << "Invalid Choice! Try Again.\n";
        }
    }

    return 0;
}
