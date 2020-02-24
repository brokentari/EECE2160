#include<string>
#include<iostream>
#include "Table.h"
#include "Furniture.h"

using namespace std;

Table::Table(string t_name, string w_type):Furniture(t_name) {
    if ((w_type.compare("Pine") == 0) || 
        (w_type.compare("Oak") == 0)) {
            wood_type = w_type;
        }
    else {
        cerr << "Enter a valid wood type [Oak or Pine]";
    }
}

void Table::Print() {
    Furniture::Print();
    cout << "Wood Type: " << wood_type << endl;
}