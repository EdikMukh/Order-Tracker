#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include "Order.h" 
#include "../utils/file_utils.h"

using namespace std;

class OrderManager {
public:
    vector<Order> orders;

    OrderManager() {
        read_from_file();
    }

    void read_from_file() {
        vector<string> lines = read_file("data/orders.txt");

        for (int i = 0; i < lines.size(); i++) {
            string line = lines[i];
            if (line.empty()) continue;

            string s_order_id, s_user_id, user_name, phone, adress;
            string order_status, s_total, s_discount, s_created_at, s_updated_at;

            istringstream iss(line);
            getline(iss, s_order_id, '\t');
            getline(iss, s_user_id, '\t');
            getline(iss, user_name, '\t');
            getline(iss, phone, '\t');
            getline(iss, adress, '\t');
            getline(iss, order_status, '\t');
            getline(iss, s_total, '\t');
            getline(iss, s_discount, '\t');
            getline(iss, s_created_at, '\t');
            getline(iss, s_updated_at, '\t');

            if (s_order_id.empty() || s_user_id.empty() || user_name.empty()) {
                cout << "Невалідні дані у рядку " << (i + 1) << ": пропущено." << endl;
                continue;
            }

            try {
                int order_id     = stoi(s_order_id);
                int user_id      = stoi(s_user_id);
                int total        = stoi(s_total);
                int discount     = s_discount.empty() ? 0 : stoi(s_discount);
                time_t created_at = (time_t)stol(s_created_at);// time_t призначений для зберігання моменту часу (дати й часу).
                time_t updated_at = (time_t)stol(s_updated_at);

                vector<OrderItem> empty_items;
                
                Order order(
                    order_id, user_id, user_name, phone, adress,
                    empty_items, order_status, total, "", 0, "", 
                    created_at, updated_at, discount
                );

                orders.push_back(order);
            } 
            catch (const exception& e) { //catch Ключове слово: "зловити виняток". Спрацьовує, якщо в блоці try сталася помилка.
                cout << "Помилка парсингу рядка " << (i + 1) << ". Пропущено." << endl;
            }
        }
    }

    Order* find_by_id(int id) {
        for (int i = 0; i < orders.size(); i++) { //size() — метод (функція), що належить вектору.
            if (orders[i].order_id == id) {
                return &orders[i];//"Пройтися по всіх замовленнях, знайти потрібне за ID і віддати його адресу".
            }
        }
        return nullptr;
    }

    void add_order(const Order& order) {
        orders.push_back(order); 
        save_to_file();//додає нове замовлення у колекцію та одразу зберігає його на диск.         
    }

    vector<Order> get_all_orders() const {//const «це не можна змінювати».
        return orders;
    }

    bool edit_order(int id, const Order& updated) {
        Order* existing = find_by_id(id);
        if (existing == nullptr) {
            cout << "Замовлення з id=" << id << " не знайдено." << endl;
            return false;
        }
        *existing = updated; 
        save_to_file();
        return true;//Це метод редагування замовлення за його ID. Він знаходить замовлення, замінює його на нові дані та зберігає зміни у файл.
    }

    void save_to_file() {
        ofstream file("data/orders.txt"); 
        if (!file.is_open()) {
            cout << "Не вдалося відкрити файл для запису!" << endl;
            return;
        }
        for (int i = 0; i < orders.size(); i++) {
            file << orders[i].to_string() << '\n';
        }
        file.close(); 
//Це метод, який зберігає всі замовлення у файл (перезаписує його повністю).
    }
};
