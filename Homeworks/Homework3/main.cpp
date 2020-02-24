#include <iostream>
#include <String>
#include "Bed.h"
#include "Furniture.h"
#include "Table.h"

int main() {
    string table_name;
    string table_wood;
    string bed_name;
    string bed_size;


    cout << "Creating table ..." << endl;
    cout << "Enter name: ";
    cin >> table_name;
    cout << "Enter wood type (Pine, Oak): ";
    cin >> table_wood;
    Table t1 = Table(table_name, table_wood);
    t1.ReadDimensions();

    cout << "Creating bed ..." << endl;
    cout << "Etner name: ";
    cin >> bed_name;
    cout << "Enter size (Twin, Full, Queen, King): ";
    cin >> bed_size;
    Bed b1 = Bed(bed_name, bed_size);
    b1.ReadDimensions();

    cout << "Printing objects ... " << endl << endl;
    t1.Print();
    b1.Print();
}