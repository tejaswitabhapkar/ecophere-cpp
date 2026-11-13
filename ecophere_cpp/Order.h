
#ifndef ORDER_H
#define ORDER_H

#include "Customer.h"
#include "Cart.h"
#include "Admin.h"

class Order {
private:
    static int nextOrderId;

public:
    static void placeOrder(
        const Customer& customer,
        Cart& cart,
        Admin& admin
    );

    static void viewOrders(int customerId);
};

#endif
