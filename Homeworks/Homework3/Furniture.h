#ifndef FURNITURE_H
#define FURNITURE_H
#include<string>

using namespace std;

class Furniture {
    private:
        float width;
        float height;
        float depth;
        string name;
    
    public:
        Furniture(string name);
        void ReadDimensions();
        virtual void Print();
};

#endif