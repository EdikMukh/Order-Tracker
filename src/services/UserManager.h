#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include "Customer.h" 
#include "../utils/file_utils.h"

using namespace std;

class UserManager {
public:
    vector<Customer> customers;   // Список всіх замовників

    UserManager() {
        read_from_file();         // Конструктор автоматично читає дані при створенні
    }

    void read_from_file() {
        // Читаємо файл із замовниками
        vector<string> lines = read_file("data/customers.txt");

        for (int i = 0; i < lines.size(); i++) {
            string line = lines[i];
            if (line.empty()) continue;    // Пропускаємо порожні рядки

            // Оголошуємо змінні для всіх 8 полів згідно з Конструктором 2 у Customer.h
            string s_user_id, user_name, phone, address;
            string city, street, house, apartment;

            // Розбираємо рядок файлу по табуляції
            istringstream iss(line);
            getline(iss, s_user_id, '\t');
            getline(iss, user_name, '\t');
            getline(iss, phone, '\t');
            getline(iss, address, '\t');
            getline(iss, city, '\t');
            getline(iss, street, '\t');
            getline(iss, house, '\t');
            getline(iss, apartment, '\t');

            try {
                // Перетворюємо рядковий ID у число
                int user_id = stoi(s_user_id);

                // Викликаємо Конструктор 2 (для читання з файлу)
                Customer customer(
                    user_id, 
                    user_name, 
                    phone, 
                    address,
                    city, 
                    street, 
                    house, 
                    apartment
                );

                customers.push_back(customer); // Додаємо у колекцію
            } 
            catch (const exception& e) {
                // Якщо ID невалідний (наприклад, літери замість цифр) — ловимо помилку
                cout << "Невалідні дані у рядку " << (i + 1) 
                     << ": неможливо додати замовника. Пропущено." << endl;
            }
        }
    }

    // Метод для пошуку замовника за його ID
    Customer* find_by_id(int id) {
        for (int i = 0; i < customers.size(); i++) {
            // Перевіряємо поле user_id
            if (customers[i].user_id == id) { 
                return &customers[i];   // Повертаємо адресу знайденого замовника
            }
        }
        return nullptr;                 // Якщо такого немає — повертаємо nullptr
    }
};