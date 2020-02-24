#include <string>
#include <iostream>
#include "Furniture.h"
#include "Bed.h"

using namespace std;

Bed::Bed(string b_name, string b_size):Furniture(b_name) {
    if ((b_size.compare("Twin") == 0) || (b_size.compare("Full") == 0)
    || (b_size.compare("Queen") == 0) || (b_size.compare("King") == 0))
        bed_size = b_size;
    else {
        cerr << "Enter a valid bed size (Twin, Full, Queen, King)";
    }
}

void Bed::Print() {
    Furniture::Print();
    cout << "Bed size: " << bed_size;
}