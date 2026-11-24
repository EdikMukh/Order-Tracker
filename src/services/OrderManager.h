#pragma once
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include "../domain/Order.h"
#include "../domain/OrderItem.h"
#include "../utils/file_utils.h"
using namespace std;

class OrderManager {
public:
    vector<Order> orders;

    OrderManager() { read_from_file(); }
    vector<OrderItem> parse_items(const string& s) {
        vector<OrderItem> res;
        if (s.empty()) return res;
        //size_t - беззнаковий цілий тип (не може бути від'ємним), який використовується для розмірів і індексів.
        size_t pos = 0;
        while (pos < s.size()) {// pos-position-індекс, з якого зараз починаємо читати рядок (початок поточного товару)
            size_t sep = s.find(" | ", pos);// sep-seperator-позиція, де знаходиться " | " — розділювач між товарами
            string chunk = (sep == string::npos) ? s.substr(pos) : s.substr(pos, sep - pos);
            pos = (sep == string::npos) ? s.size() : sep + 3;
            vector<string> p;//-порожній список рядків.
            size_t q = 0;//q-індекс, з якого починаємо читати одне поле всередині товару
            while (q <= chunk.size()) {//chunk	рядок, у якому шукаємо (один товар)
                size_t c = chunk.find(", ", q);//c-comma-позиція, де знаходиться ", " — розділювач між полями одного товару
                if (c == string::npos) { p.push_back(chunk.substr(q)); break; }
                //p-parts-Це масив рядків, у якому тимчасово зберігаються 5 частин одного товару, розбиті по ", ".
                p.push_back(chunk.substr(q, c - q));//substr — це метод класу string, який повертає частину рядка (підрядок).
                q = c + 2;
            }
            if (p.size() < 5) continue;

            try {
                // порядок у файлі: id, name, price, qty, cost
                res.push_back(OrderItem(
                    stoi(p[0]), p[1], stoi(p[2]), stoi(p[3]), stoi(p[4]),true));
            } catch (...) {}
        }
        return res;
    }

    //parse_items бере один рядок зі списком товарів (стовпець 7 файлу) і розбирає його на окремі об'єкти OrderItem.
    //serialize_items-Вона бере вектор товарів (vector<OrderItem>) і збирає його назад в один рядок того ж формату, що й у файлі.
    string serialize_items(const vector<OrderItem>& items) {
        string r;
        for (int i = 0; i < items.size(); i++) {
            if (i) r += " | ";
            r += to_string(items[i].product_id) + ", "
               + items[i].name + ", "
               + to_string(items[i].price) + ", "
               + to_string(items[i].quantity) + ", "
               + to_string(items[i].cost);
        }
        return r;
    }

    void read_from_file() {
        vector<string> lines = read_file("data/orders.txt");

        for (int i = 0; i < lines.size(); i++) {
            if (lines[i].empty()) continue;

            string s_oid, customer, s_cid, phone, addr, status, items_str;
            string s_disc, comment, ca, ua, s_tp;

            istringstream iss(lines[i]);
            getline(iss, s_oid,     '\t'); getline(iss, customer, '\t');
            getline(iss, s_cid,     '\t'); getline(iss, phone,    '\t');
            getline(iss, addr,      '\t'); getline(iss, status,   '\t');
            getline(iss, items_str, '\t'); getline(iss, s_disc,   '\t');
            getline(iss, comment,   '\t'); getline(iss, ca,       '\t');
            getline(iss, ua,        '\t'); getline(iss, s_tp,     '\t');

            try {
                Order order(
                    stoi(s_oid), customer, stoi(s_cid), phone, addr, status,
                    parse_items(items_str), stoi(s_disc), comment, static_cast<time_t>(stoll(ca)), static_cast<time_t>(stoll(ua)),
                    stoi(s_tp));
                orders.push_back(order);
            } catch (const exception&) {
                cout << "Невалідні дані у рядку " << (i + 1) << ". Пропущено." << endl;
            }
        }
    }

    Order* find_by_id(int id) {
        for (int i = 0; i < orders.size(); i++)
            if (orders[i].order_id == id) return &orders[i];
        return nullptr;
    }

    void save_to_file() {
        ofstream f("data/orders.txt");
        if (!f.is_open()) { cout << "Не вдалося відкрити файл!" << endl; return; }

        for (int i = 0; i < orders.size(); i++) {
            f << orders[i].order_id              << '\t'
              << orders[i].customer              << '\t'
              << orders[i].customer_id           << '\t'
              << orders[i].phone                 << '\t'
              << orders[i].delivery_address      << '\t'
              << orders[i].status                << '\t'
              << serialize_items(orders[i].items) << '\t'
              << orders[i].discount              << '\t'
              << orders[i].comment               << '\t'
              << orders[i].created_at            << '\t'
              << orders[i].updated_at            << '\t'
              << orders[i].total_price           << '\t';
        }
        f.close();
    }
};