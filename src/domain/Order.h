#pragma once
#include <string>

using namespace std;

class Order
{
public:
    int order_id;
    int product_id;     // який продукт замовлено
    int quantity;       // скільки одиниць
    int total_price;    // загальна вартість у копійках
    string customer;    // ім'я/логін покупця
    string status;      // напр. "new", "paid", "shipped"

public:
    // ===== КОНСТРУКТОР 1: звичайний (створення вручну) =====
    // Порядок параметрів узгоджено з Конструктором 2 та з полями файлу:
    // order_id, product_id, quantity, total_price, customer, status
    Order(int order_id, int product_id, int quantity,
          int total_price, string customer, string status)
    {
        this->order_id    = order_id;
        this->product_id  = product_id;
        this->quantity    = quantity;
        this->total_price = total_price;
        this->customer    = customer;
        this->status      = status;
    };

    // ===== КОНСТРУКТОР 2: для читання з файлу orders.txt =====
    // Приймає всі поля і записує у відповідні поля класу.
    // Останній bool from_file — щоб відрізнити від конструктора 1.
    // Делегує всю роботу Конструктору 1, щоб не дублювати код.
    Order(int order_id,
          int product_id,
          int quantity,
          int total_price,
          string customer,
          string status,
          bool from_file)
        : Order(order_id, product_id, quantity, total_price, customer, status)
    {
        // from_file навмисно не використовується —
        // він потрібен лише для розрізнення перевантаження.
    }

    int get_order_id() {
        return order_id;
    };

    int get_total_price() {
        return total_price;
    };

    string get_status() {
        return status;
    };
};