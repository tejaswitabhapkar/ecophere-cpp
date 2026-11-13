
#include "Admin.h"
#include <fstream>
#include <sstream>
#include <iomanip>

Admin::Admin() {
    loadProducts();
}

void Admin::loadProducts() {

    ifstream in("products.txt");

    if (!in) {
        products.push_back(Product(
            1, "Recycled Fabric Backpack",
            "Accessories", 1299, 20));

        products.push_back(Product(
            2, "Bamboo Water Bottle",
            "Home Products", 499, 30));

        products.push_back(Product(
            3, "Organic Cotton T-Shirt",
            "Clothing", 799, 25));

        products.push_back(Product(
            4, "Reusable Shopping Bag",
            "Accessories", 199, 50));

        products.push_back(Product(
            5, "Bamboo Toothbrush",
            "Personal Care", 99, 100));

        saveProducts();
        return;
    }

    string line;

    while (getline(in, line)) {
        stringstream ss(line);

        string id, name, category, price, stock;

        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, category, '|');
        getline(ss, price, '|');
        getline(ss, stock, '|');

        try {
            products.push_back(Product(
                stoi(id), name, category,
                stod(price), stoi(stock)));
        }
        catch (...) {
            // Skip invalid records.
        }
    }

    in.close();

    if (products.empty()) {
        products.push_back(Product(
            1, "Recycled Fabric Backpack",
            "Accessories", 1299, 20));

        products.push_back(Product(
            2, "Bamboo Water Bottle",
            "Home Products", 499, 30));

        products.push_back(Product(
            3, "Organic Cotton T-Shirt",
            "Clothing", 799, 25));

        products.push_back(Product(
            4, "Reusable Shopping Bag",
            "Accessories", 199, 50));

        products.push_back(Product(
            5, "Bamboo Toothbrush",
            "Personal Care", 99, 100));

        saveProducts();
    }
}

void Admin::saveProducts() const {

    ofstream out("products.txt");

    for (const auto &p : products) {
        out << p.getId() << "|"
            << p.getName() << "|"
            << p.getCategory() << "|"
            << p.getPrice() << "|"
            << p.getStock() << "\n";
    }

    out.close();
}

void Admin::displayProducts() const {

    cout << "\n========== ECOSPHERE PRODUCTS ==========\n";

    cout << left << setw(6) << "ID"
         << setw(28) << "Product"
         << setw(18) << "Category"
         << "Price\n";

    cout << "-----------------------------------------------------\n";

    for (const auto &p : products) {
        p.display();
    }
}

void Admin::addProduct() {

    string name, category;
    double price;
    int stock;
    int id = 1;

    cout << "\n--- ADD NEW PRODUCT ---\n";

    for (const auto &p : products) {
        if (p.getId() >= id)
            id = p.getId() + 1;
    }

    cout << "Enter Product Name: ";
    getline(cin, name);

    cout << "Enter Category: ";
    getline(cin, category);

    cout << "Enter Price: ";

    if (!(cin >> price) || price <= 0) {
        cout << "Invalid price!\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    cout << "Enter Stock: ";

    if (!(cin >> stock) || stock < 0) {
        cout << "Invalid stock!\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    cin.ignore(10000, '\n');

    if (name.empty() || category.empty() ||
        name.find('|') != string::npos ||
        category.find('|') != string::npos) {
        cout << "Invalid product details!\n";
        return;
    }

    products.push_back(Product(
        id, name, category, price, stock));

    saveProducts();

    cout << "\nProduct Added Successfully!\n";
}

Product* Admin::findProduct(int id) {

    for (auto &p : products) {
        if (p.getId() == id)
            return &p;
    }

    return nullptr;
}

void Admin::reduceStock(int id, int quantity) {

    Product* p = findProduct(id);

    if (p != nullptr && quantity > 0 &&
        p->getStock() >= quantity) {

        p->setStock(p->getStock() - quantity);
        saveProducts();
    }
}

void Admin::searchProduct() const {

    string keyword;
    bool found = false;

    cout << "\nEnter Product Name or Category: ";
    getline(cin, keyword);

    cout << "\n--- SEARCH RESULTS ---\n";

    for (const auto &p : products) {

        if (p.getName().find(keyword) != string::npos ||
            p.getCategory().find(keyword) != string::npos) {

            p.display();
            found = true;
        }
    }

    if (!found) {
        cout << "No matching products found!\n";
    }
}
