#include <iostream>
#include <stack>

using namespace std;
int main() {
    int input;
    stack<int >numbers;


    cout << "Enter input: \n";
    cin >> input;


    while (input > 0)
    {

        int digit = input % 10; //Modulo 10 gets the last numbers
        input /= 10;//Shortens the numbers by 1 digit, basically removing the last one.
        numbers.push(digit);

    }
    while (!numbers.empty())
    {
        int digit = numbers.top();
        numbers.pop();

        cout << digit << endl;
    }

    //cout << "The last digit is: " << input % 10;



    return 0;
}
