#pragma once
#include <string>
#include <vector>
#include "OrderItem.h"
using namespace std;

class Order {
public:
    int order_id;
    string customer;
    int customer_id;
    string phone;
    string delivery_address;
    string status;
    vector<OrderItem> items;
    int discount;
    string comment;
    time_t created_at;
    time_t updated_at;
    int total_price;

    // Конструктор 1: звичайний (12 полів, порядок як у файлі)
    Order(int order_id, string customer_name, int customer_id, string phone,
          string delivery_address, vector<OrderItem> items,
          int discount, string comment, int total_price)
    {
        this->order_id         = order_id;
        this->customer         = customer_name;
        this->customer_id      = customer_id;
        this->phone            = phone;
        this->delivery_address = delivery_address;
        this->status           = "created";
        this->items            = items;
        this->discount         = discount;
        this->comment          = comment;
        this->created_at       = time(nullptr);
        this->updated_at       = time(nullptr);
        this->total_price      = total_price;
    };

    // Конструктор 2: з файлу (делегує Конструктору 1)
    Order(int order_id, string customer_name, int customer_id, string phone,
          string delivery_address, string status, vector<OrderItem> items,
          int discount, string comment, time_t created_at, time_t updated_at,
          int total_price)
    {
        this->order_id         = order_id;
        this->customer         = customer_name;
        this->customer_id      = customer_id;
        this->phone            = phone;
        this->delivery_address = delivery_address;
        this->status           = status;
        this->items            = items;
        this->discount         = discount;
        this->comment          = comment;
        this->created_at       = created_at;
        this->updated_at       = updated_at;
        this->total_price      = total_price;
    }

    int get_order_id()    { return order_id; }
    int get_total_price() { return total_price; }
    string get_status()   { return status; }
    string get_customer() { return customer; }
};