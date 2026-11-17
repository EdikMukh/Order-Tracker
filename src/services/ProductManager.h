#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include "Product.h" 
#include "../utils/file_utils.h"

using namespace std;

class ProductManager {
public:
    vector<Product> products;

    ProductManager() {
        read_from_file();
    }

    void read_from_file() {
        vector<string> lines = read_file("data/products.txt");//читаємо з файлу

        for (int i = 0; i < lines.size(); i++) {
            string line = lines[i];
            if (line.empty()) continue;

            // Змінні для зчитування з файлу
            string s_product_id, name, description;
            string s_price, s_quantity;

            istringstream iss(line);
            getline(iss, s_product_id, '\t');
            getline(iss, name, '\t');
            getline(iss, description, '\t');
            getline(iss, s_price, '\t');
            getline(iss, s_quantity, '\t');

            try {
                // Перетворюємо рядки у числа (ціна - int, бо в Product.h вона int)
                int product_id = stoi(s_product_id);
                int price      = stoi(s_price);
                int quantity   = stoi(s_quantity);

                // Викликаємо КОНСТРУКТОР 2 (для читання з файлу)
                // Зверніть увагу на останній аргумент: true (це bool from_file)
                Product product(
                    product_id, 
                    name, 
                    description, 
                    price, 
                    quantity, 
                    true   // <--- Обов'язково передаємо true!
                );

                products.push_back(product);
            } 
            catch (const exception& e) {
                cout << "Невалідні дані у рядку " << (i + 1) 
                     << ": неможливо додати продукт. Пропущено." << endl;
            }
        }
    }

    Product* find_by_id(int id) {
        for (int i = 0; i < products.size(); i++) {
            if (products[i].product_id == id) {
                return &products[i];
            }
        }
        return nullptr;
    }
};