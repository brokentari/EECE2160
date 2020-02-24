#ifndef BED_H
#define BED_H
#include <string>
#include "Furniture.h"

using namespace std;

class Bed : public Furniture {
    private:
        string bed_size;
    public:
        Bed(string b_name, string b_size);

        void Print();
};

#endif