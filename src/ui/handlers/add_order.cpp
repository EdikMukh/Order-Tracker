#include <string>
#include <iostream>
#include <fstream>
#include "../../utils/file_utils.h"
#include "./add_order.h"

using namespace std;

void add_order(){
    //id	user_name	phone	address	created_at	order_status	delivery_status	total_price	quantity	discount	comment
    cout << "Формування замовлення" << endl;
    string name, phone, address, product, qty, price, discount, comment;
    cout << "Ім'я: "; getline(cin, name);
    cout << "Телефон: "; getline(cin, phone);
    cout << "Адреса: "; getline(cin, address);
    cout << "Товар: "; getline(cin, product);
    cout << "Кількість: "; getline(cin, qty);
    cout << "Ціна: "; getline(cin, price);
    cout << "Знижка (%): "; getline(cin, discount);
    cout << "Коментар: "; getline(cin, comment);
    string data = name + "\t" + address + "\t" + product + "\t" + qty + "\t" + price +"\n" + discount +"\n" + comment +"\n";
    if (append_to_file("data/orders.txt", data))
        cout << "Замовлення додано." << endl;
    else
        cout << "Помилка запису." << endl;
}