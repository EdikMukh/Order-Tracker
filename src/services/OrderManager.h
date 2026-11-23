#pragma once
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include "../domain/Order.h"
#include "../utils/file_utils.h"

using namespace std;

class OrderManager {
public:
    vector<Order> orders;

    OrderManager() {
        read_from_file();
    }

    void read_from_file() {
        vector<string> lines = read_file("data/orders.txt"); // читаємо з файлу

        for (int i = 0; i < lines.size(); i++) {
            string line = lines[i];
            if (line.empty()) continue;

            // Змінні для зчитування з файлу
            string s_order_id, s_product_id, s_quantity;
            string s_total_price, customer, status;

            istringstream iss(line);
            getline(iss, s_order_id,    '\t');
            getline(iss, s_product_id,  '\t');
            getline(iss, s_quantity,    '\t');
            getline(iss, s_total_price, '\t');
            getline(iss, customer,      '\t');
            getline(iss, status,        '\t');

            try {
                // Перетворюємо рядки у числа (усі гроші/кількості - int)
                int order_id    = stoi(s_order_id);
                int product_id  = stoi(s_product_id);
                int quantity    = stoi(s_quantity);
                int total_price = stoi(s_total_price);

                // Викликаємо КОНСТРУКТОР 2 (для читання з файлу)
                // Порядок і типи аргументів повністю збігаються з конструктором:
                // (int, int, int, int, string, string, bool)
                Order order(
                    order_id,     // int
                    product_id,   // int
                    quantity,     // int
                    total_price,  // int
                    customer,     // string
                    status,       // string
                    true          // bool — маркер "з файлу"
                );

                orders.push_back(order);
            }
            catch (const exception& e) {
                cout << "Невалідні дані у рядку " << (i + 1)
                     << ": неможливо додати замовлення. Пропущено." << endl;
            }
        }
    }

    Order* find_by_id(int id) {
        for (int i = 0; i < orders.size(); i++) {
            if (orders[i].order_id == id) {
                return &orders[i];
            }
        }
        return nullptr;
    }

    // Метод для збереження замовлень у файл
    void save_to_file() {
        ofstream file("data/orders.txt");
        if (!file.is_open()) {
            cout << "Не вдалося відкрити файл для запису!" << endl;
            return;
        }

        for (int i = 0; i < orders.size(); i++) {
            // Записуємо поля через табуляцію '\t', як і при читанні
            file << orders[i].order_id    << '\t'
                 << orders[i].product_id  << '\t'
                 << orders[i].quantity    << '\t'
                 << orders[i].total_price << '\t'
                 << orders[i].customer    << '\t'
                 << orders[i].status      << '\n';
        }
        file.close();
    }
};