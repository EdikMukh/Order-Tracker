#include <string>
#include <vector>
#include <ctime>
#include "Orderitem.h"
#include "Customer.h"

using namespace std;

class Order
{
public:
    int order_id;
    int user_id;
    string user_name;
    string phone;
    string adress;
    vector<OrderItem> items;
    string order_status;
    int total;
    string product_id;
    int quantity;
    string status;
    time_t created_at;
    time_t updated_at;
    int discount;

    // ===== КОНСТРУКТОР 1: створення нового замовлення з Customer =====
    Order(Customer customer)
    {
        // ---- order_id генеруємо тут ----
        this->order_id = (int)time(nullptr);

        // ---- значення з customer ----
        this->user_id   = customer.user_id;
        this->user_name = customer.user_name;
        this->phone     = customer.phone;
        this->adress    = customer.address;

        // ---- items поки що порожній (заповнюється через add_item) ----
        // this->items вже є порожнім вектором

        // ---- статус при створенні ----
        this->status       = "created";
        this->order_status = "created";

        // ---- total: перебираємо items і додаємо cost ----
        this->total = 0;
        for (int i = 0; i < items.size(); i++) {
            this->total += items[i].get_cost();
        }

        // ---- дати ----
        this->created_at = time(nullptr);
        this->updated_at = time(nullptr);

        // ---- окремо підписуємо ----
        this->discount = 0;
    }

    // ===== КОНСТРУКТОР 2: для читання з файлу =====
    // Приймає всі поля як аргументи і записує їх у відповідні поля класу
    Order(int order_id,
          int user_id,
          string user_name,
          string phone,
          string adress,
          vector<OrderItem> items,
          string order_status,
          int total,
          string product_id,
          int quantity,
          string status,
          time_t created_at,
          time_t updated_at,
          int discount)
    {
        this->order_id     = order_id;
        this->user_id      = user_id;
        this->user_name    = user_name;
        this->phone        = phone;
        this->adress       = adress;
        this->items        = items;
        this->order_status = order_status;
        this->total        = total;
        this->product_id   = product_id;
        this->quantity     = quantity;
        this->status       = status;
        this->created_at   = created_at;
        this->updated_at   = updated_at;
        this->discount     = discount;
    }

    // додати товар у замовлення (і перерахувати total)
    void add_item(OrderItem item) {
        items.push_back(item);
        total += item.get_cost();
        updated_at = time(nullptr);
    }

    string to_string() {
        string order = std::to_string(order_id) + "\t"
                     + std::to_string(user_id)  + "\t"
                     + user_name + "\t"
                     + phone + "\t"
                     + adress + "\t"
                     + order_status + "\t"
                     + std::to_string(total) + "\t"
                     + std::to_string(discount) + "\t"
                     + std::to_string(created_at) + "\t"
                     + std::to_string(updated_at);
        return order;
    }
};