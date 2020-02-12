#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Car {
    private:
        string make;
        string model;
        int year;
        string color;
    public:
        Car() {}
        void setFields(string mk, string md, int yr, string cl) {
            make = mk;
            model = md;
            year = yr;
            color = cl;
        }
        string getMake() { return make; }
        string getModel() { return model; }
        int getYear() { return year; }
        string getColor() { return color; }
        void printCar() {
            cout << "\tMake: " << make << endl;
            cout << "\tModel: " << model << endl;
            cout << "\tYear: " <<  year << endl;
            cout << "\tColor: " << color << endl << endl;
        }
};

class CarRecords {
    private:
        int arraySize;
        ifstream infile;
        Car *cars;
    public:
        CarRecords(int size) { 
            if (size > 10) {
                arraySize = 10;
            } else {
                arraySize = size;
            }
            infile.open("CarRecords.txt");
            cars = new Car[arraySize]; 
            Car c;
            string line;

            for (int i = 0; i < arraySize; i++) {
                getline(infile, line);
                string make = line.substr(0, line.find(",", 0));
                string rest = line.substr(line.find(",") + 2);
                string model = rest.substr(0, rest.find(","));
                rest = rest.substr(rest.find(",") + 2);
                int year = stoi(rest.substr(0, rest.find(",")));
                rest = rest.substr(rest.find(",")+2);
                string color = rest;
                c.setFields(make, model, year, color);
                cars[i] = c;
            }
        }
        ~CarRecords() {
            infile.close();
            delete this;
        } 
        void printCarRecords() {
            for (int i = 0; i < arraySize; i++) {
                cars[i].printCar();
            }
        }
        void sort_cars_by_make() {
            int i, j;
            Car min;

            for (i = 0; i < arraySize; i++ ) {
                for (j = i + 1; j < arraySize; j++) {
                    if (cars[i].getMake() < cars[j].getMake()) {
                        min = cars[i];
                        cars[i] = cars[j];
                        cars[j] = min;
                    }
                }
            }
        }
        void sort_cars_by_year() {
            int i, j;
            Car min;
            for (i = 0; i < arraySize; i++) {
                for (j = i + 1; j < arraySize; j++ ) {
                    if (cars[i].getYear() > cars[j].getYear()) {
                        min = cars[i];
                        cars[i] = cars[j];
                        cars[j] = min;
                    }
                }
            }
        }
        void print_duplicates() {
            for (int i = 0; i < arraySize; i++ ) {
                for (int j = 0; j < arraySize; j++) {
                    if (j != i) {
                        if ((cars[i].getColor() == cars[j].getColor())
                        && (cars[i].getMake() == cars[j].getMake())
                        && (cars[i].getYear() == cars[j].getYear())
                        && (cars[i].getModel() == cars[j].getModel())) {
                            cars[i].printCar();
                        }
                    }
                }
            }
        }
};

int main() {
    int numRecs;
    cout << "Number of Records to read? "; 
    cin >> numRecs;
    CarRecords *cr = new CarRecords(numRecs);

    //Print car records
    cr->printCarRecords();
    //Sort by year
    cout << "--------------------Sorted by year---------------------" << endl << endl;
    cr->sort_cars_by_year();
    cr->printCarRecords();
    cout << "--------------------Sorted by make---------------------" << endl << endl;
    cr->sort_cars_by_make();
    cr->printCarRecords();
    cout << "--------------------Duplicates--------------------" << endl << endl;
    cr->print_duplicates();
    delete cr;
}