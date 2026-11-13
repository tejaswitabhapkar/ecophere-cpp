
#include "Customer.h"
#include <fstream>
#include <sstream>

Customer::Customer() {
    id = 0;
}

Customer::Customer(int id, string name,
                   string email, string password) {
    this->id = id;
    this->name = name;
    this->email = email;
    this->password = password;
}

int Customer::getId() const {
    return id;
}

string Customer::getName() const {
    return name;
}

string Customer::getEmail() const {
    return email;
}

bool Customer::isValid() const {
    return id != 0;
}

Customer Customer::registerCustomer() {
    string name, email, password, line;
    int newId = 1;

    ifstream in("customers.txt");

    while (getline(in, line)) {
        stringstream ss(line);
        string idText;

        getline(ss, idText, '|');

        try {
            int oldId = stoi(idText);
            if (oldId >= newId)
                newId = oldId + 1;
        }
        catch (...) {}
    }
    in.close();

    cout << "\n--- CUSTOMER REGISTRATION ---\n";

    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter Email: ";
    getline(cin, email);

    cout << "Create Password: ";
    getline(cin, password);

    if (name.empty() || email.empty() || password.empty() ||
        name.find('|') != string::npos ||
        email.find('|') != string::npos ||
        password.find('|') != string::npos) {
        cout << "Invalid details!\n";
        return Customer();
    }

    ifstream check("customers.txt");

    while (getline(check, line)) {
        stringstream ss(line);
        string oldId, oldName, oldEmail;

        getline(ss, oldId, '|');
        getline(ss, oldName, '|');
        getline(ss, oldEmail, '|');

        if (oldEmail == email) {
            cout << "Email already registered!\n";
            return Customer();
        }
    }
    check.close();

    ofstream out("customers.txt", ios::app);

    if (!out) {
        cout << "Unable to save customer!\n";
        return Customer();
    }

    out << newId << "|" << name << "|"
        << email << "|" << password << "\n";

    out.close();

    cout << "\nRegistration Successful!\n";

    return Customer(newId, name, email, password);
}

Customer Customer::loginCustomer() {
    string email, password, line;

    cout << "\n--- CUSTOMER LOGIN ---\n";

    cout << "Enter Email: ";
    getline(cin, email);

    cout << "Enter Password: ";
    getline(cin, password);

    ifstream in("customers.txt");

    while (getline(in, line)) {
        stringstream ss(line);

        string idText, name, savedEmail, savedPassword;

        getline(ss, idText, '|');
        getline(ss, name, '|');
        getline(ss, savedEmail, '|');
        getline(ss, savedPassword, '|');

        if (savedEmail == email &&
            savedPassword == password) {

            in.close();

            cout << "\nLogin Successful!\n";

            return Customer(stoi(idText), name,
                            savedEmail, savedPassword);
        }
    }

    in.close();

    cout << "\nInvalid Email or Password!\n";

    return Customer();
}
