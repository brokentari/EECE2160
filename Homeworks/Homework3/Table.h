#ifndef TABLE_H
#define TABLE_H
#include "Furniture.h"
#include<string>

using namespace std;

class Table : public Furniture {
    private:
        string wood_type;
    public:
        Table(string t_name, string w_type);
        void Print();
};

#endif