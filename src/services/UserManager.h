#pragma once
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include "../domain/Customer.h" 
#include "../utils/file_utils.h"

using namespace std;
struct Result{
    int success;
    int failure;
};

class UserManager {
public:
    vector<Customer> customers;   // Список всіх замовників

    UserManager() {
        cout <<"Завантажуємо дані замовників..."<<endl;
        read_from_file();// Конструктор автоматично читає дані при створенні
        //cout<<"Кількість успішних завантаженнь:"<<result.success<<endl;
        //cout<<"Кількість не успішних завантаженнь:"<<result.failure<<endl;
        cout<<"qweqwe"<<endl;
    }

    void read_from_file() {
        
        int success = 0;
        int failure = 0;

        // Читаємо файл із замовниками
        vector<string> lines = read_file("data/customers.txt");

        for (int i = 0; i < lines.size(); i++) {
            string line = lines[i];
            if (line.empty()) continue;    // Пропускаємо порожні рядки

            // Оголошуємо змінні для всіх 8 полів згідно з Конструктором 2 у Customer.h
            string s_user_id, user_name, s_phones, address;
            vector<string>phones;

            // Розбираємо рядок файлу по табуляції
            istringstream iss(line);
            getline(iss, s_user_id, '\t');
            getline(iss, user_name, '\t');
            getline(iss, s_phones, '\t');
            getline(iss, address, '\t');
            istringstream ppss(s_phones);
            bool is_next_phone = true;
            while(is_next_phone){
                string phone;
                getline(ppss, phone, '|');
                if(phone.size()){
                    phones.push_back(phone);
                }else{
                    is_next_phone = false;

                }
            }




            try {
                // Перетворюємо рядковий ID у число
                int user_id = stoi(s_user_id);

                // Викликаємо Конструктор 2 (для читання з файлу)
                Customer customer(
                    user_id, 
                    user_name, 
                    phones, 
                    address
                );

                customers.push_back(customer); // Додаємо у колекцію
                success = success + 1;
                
            } 
            catch (const exception& e) {// це блок, який ловить винятки (помилки), що виникли в блоці try перед ним.
                // Якщо ID невалідний (наприклад, літери замість цифр) — ловимо помилку
                cout << "Невалідні дані у рядку " << (i + 1) 
                     << ": неможливо додати замовника. Пропущено." << endl;
                failure++;
            }
        }
        cout<<success<<failure<<endl;
        //return result;
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