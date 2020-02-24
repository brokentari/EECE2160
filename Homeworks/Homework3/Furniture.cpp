#include <string>
#include <iostream>
#include "Furniture.h"

using namespace std;


Furniture::Furniture(string f_name) {
    name = f_name;
}

void Furniture::ReadDimensions() {
    cout << "Width: ";
    cin >> width;
    cout << "Height: ";
    cin >> height;
    cout << "Depth: ";
    cin >> depth;

    if ((width == 0) || (height == 0) || (depth == 0)) {
        cerr << "Make sure all values are above 0" << endl;
    }
}

void Furniture::Print() {
    cout << "Furniture Name" << name << endl;
    cout << "Width: " << width << endl;
    cout << "Height: " << height << endl;
    cout << "Depth: " << depth << endl;
}