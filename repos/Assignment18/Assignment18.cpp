#include <iostream>

using namespace std;


int main() {

    int n, a, temp;
    string number;

    cout << "Enter a value:";
    cin >> n;

    cout << '\n' << "Enter a value you want to find: ";
    cin >> a;

    while (n != 0)
    {
        temp = n % 10;
        n = n / 10;
        if (temp == a)
        {
            cout << "gusta" << endl;
            break;
        }
    }

    return 0;
}
