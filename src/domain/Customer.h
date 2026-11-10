#include <string>

using namespace std;

//цей клас описує окремо одного замовника(кожного тільки дані різні)
class Customer
{
public:
    int user_id;
    string user_name;          // ПІБ: "Іванов Іван Іванович"
    string phone;              // формат: "+380501234567" або "0501234567"
    string address;            // "Нова пошта, Київ, №123"
    string delivery_address[4]; // {Місто, вулиця, будинок, квартира}

    // ===== КОНСТРУКТОР 1: звичайний (створення вручну) =====
    Customer(string customer_name,
             string customer_phone,
             string customer_address,
             string city = "",
             string street = "",
             string house = "",
             string apartment = "")
    {
        user_id          = 0;   // <-- додав, щоб поле не було сміттям
        user_name        = customer_name;
        phone            = customer_phone;
        address          = customer_address;

        delivery_address[0] = city;
        delivery_address[1] = street;
        delivery_address[2] = house;
        delivery_address[3] = apartment;
    }

    // ===== КОНСТРУКТОР 2: для читання з файлу customers.txt =====
    // Приймає всі поля як аргументи і записує їх у відповідні поля класу
    Customer(int user_id,
             string user_name,
             string phone,
             string address,
             string city,
             string street,
             string house,
             string apartment)
    {
        this->user_id          = user_id;
        this->user_name        = user_name;
        this->phone            = phone;
        this->address          = address;

        this->delivery_address[0] = city;
        this->delivery_address[1] = street;
        this->delivery_address[2] = house;
        this->delivery_address[3] = apartment;
    }
};