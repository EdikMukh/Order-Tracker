#pragma once
#include <string>

using namespace std;


class Product
{
public:
    int product_id;
    string name;
    string description;
    int price;      // Ціну зберігаємо в копійках
    int quantity;   // кількість скільки залишилося на складі

public:
    // ===== КОНСТРУКТОР 1: звичайний (створення вручну) =====
    // Порядок параметрів узгоджено з Конструктором 2 та з полями файлу:
    // product_id, name, description, price, quantity
    Product(int product_id, string name, string description, int price, int quantity)
    {
        this->product_id  = product_id;
        this->name        = name;
        this->description = description;
        this->price       = price;
        this->quantity    = quantity;
    };

    // ===== КОНСТРУКТОР 2: для читання з файлу products.txt =====
    // Приймає всі поля і записує у відповідні поля класу.
    // Останній bool from_file — щоб відрізнити від конструктора 1.
    // Делегує всю роботу Конструктору 1, щоб не дублювати код.
    Product(int product_id,
            string name,
            string description,
            int price,
            int quantity,
            bool from_file)
        : Product(product_id, name, description, price, quantity)
    {
        // from_file навмисно не використовується —
        // він потрібен лише для розрізнення перевантаження.
    }

    string get_name(){
        return name;
    };

    int get_price(){
        return price;
    };
};