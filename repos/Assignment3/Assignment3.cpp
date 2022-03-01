#include <iostream>
using namespace std;

int main() {

    int value;
    cout << "Input value: " << endl;
    cin >> value;

    if (value % 2 == 0)
    {
        cout << "Value is even";
    }
    if (value % 2 != 0)
    {
        cout << "Value is not even";
    }
}
