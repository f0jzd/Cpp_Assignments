#include <iostream>
#include <bitset>

using namespace std;


void GetBit(int& bitToGet, int& num);
void SetBit(int& bitToSet, int& num);

int main() {

    int numberToGet, numberToSet, bitVal, number;

    cout << "Enter the number you want to check the bit of: ";
    cin >> number;

    cout << bitset<16>(number) << endl;


    cout << "Enter the nth bit from the number you want: ";
    cin >> numberToGet;


    GetBit(numberToGet, number);

    cout << "Enter the number of the bit you want to set: ";
    cin >> numberToSet;

    SetBit(numberToSet, number);

    cout << number << endl;

}

void GetBit(int& bitToGet, int& num)
{
    cout << bitset<8>(num) << endl;
    int bit = (num >> bitToGet) & 1;
    cout << bitset<8>(num) << endl;
    cout << bit << endl;

}
void SetBit(int& bitToSet, int& num)
{
    cout << bitset<8>(num) << endl;
    num ^= 1UL << bitToSet;
    cout << bitset<8>(num) << endl;



}
