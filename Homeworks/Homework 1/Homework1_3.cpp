#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Car {
    string make;
    string model;
    int year;
    string color;
};

struct car_node {
    Car current_car;
    car_node *next_car;
};

car_node * insert_linkedList(car_node* cn, string file_path) {
    string line;
    ifstream file;
    file.open(file_path);

    while(!file.eof()) {
        car_node *temp = new car_node;
        getline(file, line);

        string make = line.substr(0, line.find(",", 0));
        string rest = line.substr(line.find(",") + 2);
        string model = rest.substr(0, rest.find(","));
        rest = rest.substr(rest.find(",") + 2);
        int year = stoi(rest.substr(0, rest.find(",")));
        rest = rest.substr(rest.find(",")+2);
        string color = rest;
        Car curr_car = {make, model, year, color};

        temp->current_car = curr_car;
        temp->next_car = cn;
        cn = temp;
    }

    file.close();
    return cn;

}

void print_cars_list(car_node* cn) {
    if (cn->next_car == NULL) {

    }
    else {
        cout << "\tMake: " << cn->current_car.make << endl;
        cout << "\tModel: " << cn->current_car.model << endl;
        cout << "\tYear: " << cn->current_car.year << endl;
        cout << "\tColor: " << cn->current_car.color << endl << endl;;
        print_cars_list(cn->next_car); 
    }
}

int main() {
    typedef struct Car Car;
    car_node *ptr = new car_node;
    ptr->next_car = NULL;
    int input;

    while(true) {
        cout << "MENU - Select an option: " << endl;
        cout << "1. Insert Linked List" << endl;
        cout << "2. Print Cars List" << endl;
        cout << "3. Exit" << endl;
        cin >> input;
        switch(input) {
            case 1:
                ptr = insert_linkedList(ptr, "CarRecords.txt");
                cout << "Records have been inserted into a linked list" << endl;
                break;
            case 2:
                print_cars_list(ptr);
                break;
            case 3:
                return 0;
                break;
        }
    }

    delete ptr;
}