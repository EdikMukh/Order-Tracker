#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "../services/OrderManager.h"
#include "../services/ProductManager.h"
#include "../services/UserManager.h"

using namespace std;

class OrderController {
private:
    OrderManager order_mgr;
    UserManager user_mgr;
    ProductManager prod_mgr;

public:
    // 1. Створити замовлення (перевіряє юзера і товар)
    void create_order() {
        int u_id, p_id;
        cout << "ID клієнта: "; cin >> u_id;
        // !-це оператор логічного заперечення
        if (!user_mgr.find_by_id(u_id)) { 
            cout << "Клієнта не знайдено!\n"; return; 
        }

        cout << "ID товару: "; cin >> p_id;
        Product* p = prod_mgr.find_by_id(p_id);
        // || - це оператор логічного "АБО"
        if (!p || p->quantity <= 0) { 
            cout << "Товару немає!\n"; return; 
        }

        // Створюємо замовлення (спрощено, без кошика)
        Order new_o(0, u_id, user_mgr.find_by_id(u_id)->user_name, 
                    user_mgr.find_by_id(u_id)->phones[0],
                    user_mgr.find_by_id(u_id)->address, 
                    {}, "Нове", p->price, "", 0, "", time(0), time(0), 0);

        order_mgr.add_order(new_o); // Зберігає у файл
        p->quantity--;              // Зменшуємо запас
        prod_mgr.save_to_file();    // Зберігаємо зміни товару
        
        cout << "Успішно створено!\n";
    }
// | - це побітовий оператор "АБО"
    // 2. Показати всі замовлення
    void show_orders() {
        vector<Order> list = order_mgr.get_all_orders();
        for (auto& o : list) {
            cout << "ID: " << o.order_id << " | " << o.user_name 
                 << " | Сума: " << o.total << " | " << o.order_status << "\n";
        }
    }

    // 3. Пошук за ID
    void find_order() {
        int id; cout << "ID замовлення: "; cin >> id;
        Order* o = order_mgr.find_by_id(id);
        if (o) cout << "Знайдено: " << o->user_name << " (" << o->order_status << ")\n";//вказівник o вказує на реальний об'єкт у пам'яті.
        else cout << "Не знайдено.\n";
    }

    // 4. Змінити статус
    void edit_status() {
        int id; cout << "ID замовлення: "; cin >> id;// cin - зчитування даних з клавіатури
        Order* o = order_mgr.find_by_id(id);
        if (o) {
            cout << "Новий статус: "; cin >> o->order_status;
            order_mgr.save_to_file();
            cout << "Змінено.\n";
        } else cout << "Не знайдено.\n";
    }
};