#include <iostream>
#include <string>

using namespace std;

int main() {


    std::string helo = "Hello";

    helo.length();


    cin >> helo;

    for (int i = helo.length(); i >= 0; --i) {
        cout << helo[i];
    }

    return 0;
}
