#pragma once
#include <string>

using namespace std;

//цей клас описує окремо одного замовника(кожного тільки дані різні)
class Customer
{
public:
    int user_id;
    string user_name;          // ПІБ: "Іванов Іван Іванович"
    vector<string> phones;              // формат: "+380501234567" або "0501234567"
    string address;            // "Нова пошта, Київ, №123"
    // ===== КОНСТРУКТОР 1: звичайний (створення вручну) =====
    Customer(string customer_name,
             vector<string> customer_phones,
             string customer_address)
    {
        user_id          = 0;   // <-- додав, щоб поле не було сміттям
        user_name        = customer_name;
        phones            = customer_phones;
        address          = customer_address;
    }

    // ===== КОНСТРУКТОР 2: для читання з файлу customers.txt =====
    // Приймає всі поля як аргументи і записує їх у відповідні поля класу
    Customer(int user_id,
             string user_name,
             vector<string> phones,
             string address
             )
    {
        this->user_id          = user_id;
        this->user_name        = user_name;
        this->phones            = phones;
        this->address          = address;
    }
};