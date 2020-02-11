#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>

using namespace std;

struct Car {
    string make;
    string model;
    int year;
    string color;
};

Car * insert_array(Car *c, string file_path) {
    typedef struct Car Car;
    string line;
    ifstream file;
    file.open(file_path);
    int i = 0;
    
    while(!file.eof()){ 
        getline(file, line);
        string make = line.substr(0, line.find(",", 0));
        string rest = line.substr(line.find(",") + 2);
        string model = rest.substr(0, rest.find(","));
        rest = rest.substr(rest.find(",") + 2);
        int year;
        istringstream(rest.substr(0, rest.find(","))) >> year;
        rest = rest.substr(rest.find(",")+2);
        string color = rest;
        Car curr_car = {make, model, year, color};
        c[i] = curr_car;
        i++;
    }

    file.close();
    return c;
}

void print_car(Car c) {
    cout << "\t Make: " << c.make << endl;
    cout << "\t Model: " << c.model << endl;
    cout << "\t Year: " << c.year << endl;
    cout << "\t Color: " << c.color << endl;
}

void print_cars_array(Car* c, int length) {
    for (int i = 0; i < length; i++) {
        cout << "Car " << (i + 1) << ": " << endl;
        print_car(c[i]);
    }
}

Car * sort_cars_by_make(Car* c, int length) {
    Car* temp = new Car[length]();

    int i, min_i;
	string min_str;

	for (i = 0; i < length-1; i++) {
		min_i = i;
		min_str = c[i].make;
		for (int j = i+1; j < length; j++) {
			if (c[j].make < min_str) {
				min_str = c[j].make;
				min_i = j;
			}
		}
		c[min_i] = c[i];
		c[i].make = min_str;
	}

    return c;
}


void print_duplicates(Car* c, int length) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            if (j != i) {
                if((c[i].make == c[j].make) && (c[i].model == c[j].model) 
        && (c[i].year == c[j].year) && (c[i].color == c[j].color)) {
                    print_car(c[i]);
                    cout << endl;
                }
            }
        }
    }
}

void save_cars_in_file(Car* c, int length) {
    ofstream file ("CarRecords.txt");

    if(file.is_open()) {
        for(int i = 0; i < length; i++) {
            string line = "";
            if (i == (length - 1)) {
                line = c[i].make + ", " + c[i].model + ", " + 
                to_string(c[i].year) + ", " + c[i].color;
            }else {
                line = c[i].make + ", " + c[i].model + ", " + 
                to_string(c[i].year) + ", " + c[i].color + "\n";
            }
            file << line;
        }
    }

    file.close();
}

int main() {
    int total_lines = 0;
    string line;
    ifstream file;
    file.open("CarRecords.txt");

    while(!file.eof()) {
        getline(file, line);
        total_lines++;
    }

    Car* cars = new Car[total_lines]();
    int input;

    while (true) {
        cout << "MENU - Select an option: " << endl;
        cout << "1. Insert car records into an array" << endl;
        cout << "2. Print the cars array" << endl;
        cout << "3. Sort cars by make" << endl;
        cout << "4. Print duplicates" << endl;
        cout << "5. Save car records into a file" << endl;
        cout << "6. Exit" << endl;
        cin >> input;
        switch(input) {
            case 1:
                cars = insert_array(cars, "CarRecords.txt");
                break;
            case 2:
                print_cars_array(cars, total_lines);
                break;
            case 3:
                sort_cars_by_make(cars, total_lines);
                break;
            case 4:
                print_duplicates(cars, total_lines);
                break;
            case 5:
                save_cars_in_file(cars, total_lines);
                break;
            case 6:
                return 0;
            default:
                cout << "Not an available option" << endl;
        }
    }
}