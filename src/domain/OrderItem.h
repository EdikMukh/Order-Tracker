#include <string>
#include "Product.h"
using namespace std;

class OrderItem{
    int product_id;
    string name;
    int quantity; // кількість одиниць в замовленні 
    int price; // Ціну зберігаємо в копійках
    int cost;

    
    public:
    //конструктор 
    OrderItem(Product product, int quantity){
        this -> product_id = product.product_id;
        this -> name = product.get_name();
        this -> quantity = quantity;
        this -> price = product.get_price();
        this -> cost = quantity * price;
    };
    //публічні методи класу
    int get_cost(){
        return cost;
    }
    string to_string(){
    string orderItem = std::to_string(product_id) + "\t" + name + "\t"
                     + std::to_string(quantity) + "\t"
                     + std::to_string(price) + "\t"
                     + std::to_string(cost);
    return orderItem;   // <-- добавь это
}
};