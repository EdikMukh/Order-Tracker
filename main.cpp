 #include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <vector>
#include <direct.h>

 using namespace std;
 bool append_to_file(string path, string text);

 void add_order(){
    //id	user_name	phone	address	created_at	order_status	delivery_status	total_price	quantity	discount	comment
    cout << "Формування замовлення" << endl;
    string name, address, product, qty, price;
    cout << "Ім'я: "; getline(cin, name);
    cout << "Адреса: "; getline(cin, address);
    cout << "Товар: "; getline(cin, product);
    cout << "Кількість: "; getline(cin, qty);
    cout << "Ціна: "; getline(cin, price);
    string data = name + "\t" + address + "\t" + product + "\t" + qty + "\t" + price +"\n";
    if (append_to_file("data/orders.txt", data))
        cout << "Замовлення додано." << endl;
    else
        cout << "Помилка запису." << endl;
}
 void seeOrder(){cout << "see order;" << "\n";}
 void seeOneOrder(){cout << "see one order;" << "\n";}
 void updateOrder(){cout << "update order;" << "\n";}
 void deleteOrder(){cout << "delete order;" << "\n";}
 void createOrder(){cout << "create order;" << "\n";}
 void exit(){cout << "exit;" << "\n";}

void main_menu(){
    int choice;
    bool is_choice_made = false;
    while(!is_choice_made){
        cout <<"--------------------"<< endl;
        cout <<"========MENU========" << endl;
        cout <<"1. Додати замовлення;"<< endl;
        cout <<"2. Переглянути усі замовлення;"<< endl;
        cout <<"3. Переглянути одне замовлення;"<< endl;
        cout <<"4. Редагувати замовлення;"<< endl;
        cout <<"5. Видалити замовлення;"<< endl;
        cout <<"6. Сформувати звіт;"<< endl;
        cout <<"0. Вихід."<< endl;
        cout <<"--------------------"<< endl;
        cout <<"Зробіть свій вибір: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                add_order();
                is_choice_made = true;
                break;
            case 2:
                seeOrder();
                is_choice_made = true;
                break;
            case 3:
                seeOneOrder();
                is_choice_made = true;
                break;
            case 4:
                updateOrder();
                is_choice_made = true;
                break;
            case 5:
                deleteOrder();
                is_choice_made = true;
                break;
            case 6:
                createOrder();
                is_choice_made = true;
                break;
            case 0:
                is_choice_made = false;   
                cout << "exit;\n";
                break;
            default:
                cout << "Неправильний вибір. Спробуйте ще раз.\n";
                cout << "Натисніть Enter, щоб продовжити.\n";
                is_choice_made = true;
                break;            
        }

    }}  
// ------------file ultilites------------
vector<string> read_file(string patch){
    ifstream file(patch);
    vector<string> lines;
    if (file.is_open()){
        string line;
        while (getline(file, line))
            lines.push_back(line);
    };
    return lines;
}


bool append_to_file(string path, string text) {
    ofstream file(path, ios::app);
    if (file.is_open()) {
        file << text << endl; 
        file.close();
        return true; 
    }
    return false;
}



bool overwrite_file(string path, string text) {
    ofstream file(path); 
    if (file.is_open()) {
        file << text; 
        file.close();
        return true;
    }
    return false;
}

  int main(){
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
        _mkdir("data");
    main_menu();
    vector<string> lines = read_file("data/orders.txt");
    for (const string &item : lines)
            cout << item << endl;
    

    return 0;
  }