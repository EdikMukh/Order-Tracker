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
    Product(int id, string name, int price, int quantity, string description = "")
    {
        this->product_id  = id;
        this->name        = name;
        this->description = description;
        this->price       = price;
        this->quantity    = quantity;
    };

    // ===== КОНСТРУКТОР 2: для читання з файлу products.txt =====
    // Приймає всі поля і записує у відповідні поля класу.
    // Останній bool from_file — щоб відрізнити від конструктора 1.
    Product(int product_id,
            string name,
            string description,
            int price,
            int quantity,
            bool from_file)
    {
        this->product_id  = product_id;
        this->name        = name;
        this->description = description;
        this->price       = price;
        this->quantity    = quantity;
    }

    string get_name(){
        return name;
    };

    int get_price(){
        return price;
    };
};