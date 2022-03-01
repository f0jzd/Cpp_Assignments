#include <iostream>

using namespace std;

int AbsoluteFunction(int a);

int main() {
    int number1, number2;


    cout << "Enter 2 values: ";
    cin >> number1 >> number2;
    cout << "The absolute value is: " << AbsoluteFunction(number1 + number2);

    return 0;
}


int AbsoluteFunction(int nr1) {
    if (nr1 < 0) {
        nr1 *= -1;
    }
    return nr1;
}

