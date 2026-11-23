#pragma once
#include <string>
#include "Product.h"
using namespace std;

class OrderItem {
public:
    int product_id;
    string name;
    int price;
    int quantity;
    int cost;

    // Конструктор 1: з Product (ручне створення)
    OrderItem(Product product, int quantity) {
        this->product_id = product.product_id;
        this->name       = product.get_name();
        this->price      = product.get_price();
        this->quantity   = quantity;
        this->cost       = quantity * price;
    };

    // Конструктор 2: з файлу (порядок як у файлі: id, name, price, qty, cost)
    OrderItem(int product_id, string name, int price, int quantity, int cost, bool from_file) {
        this->product_id = product_id;
        this->name       = name;
        this->price      = price;
        this->quantity   = quantity;
        this->cost       = cost;
    };

    int get_cost() { return cost; }

    string to_string() {
        return std::to_string(product_id) + "\t" + name + "\t"
             + std::to_string(price) + "\t"
             + std::to_string(quantity) + "\t"
             + std::to_string(cost);
    }
};