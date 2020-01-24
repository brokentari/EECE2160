#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>

using namespace std;

int to_power_of(int n1, int n2) { 
    return pow(n1, n2);
}
bool check_max(int n1, int n2) {
    if (n1 > n2) {
        return n1;
    } else return n2;
}

void dec2Hex(int n) {
    string conv = "";
    int temp;
    char hex[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

    while(n > 0) {
        temp = n % 16;;
        conv = hex[temp] + conv;
        n = n / 16;
    }

    cout << conv << endl;
}

void convert(int n1) {
    cout << "Decimal: " << n1 << endl;
    dec2Hex(n1);
}

int main() {
    int number1, number2;

    cout << "Enter the first number: " << endl;
    cin >> number1;
    cout << "Enter the second number: " << endl;
    cin >> number2;
    cout << number1 << " ^ " << number2 << " = " << to_power_of(number1, number2) << endl;
    cout << "Maximum number: " << check_max(number1, number2) << endl;
    
    convert(number1);
}

