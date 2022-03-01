#include <iostream>
#include <bitset>

using namespace std;



void PerformBitswap(int& slotA, int& slotB)
{

    slotA = slotA ^ slotB;
    slotB = slotA ^ slotB;
    slotA = slotA ^ slotB;

    cout << "Swap complete" << endl;

}

int main() {



    int a = 255, b = 129;

    cout << "a: " << a << ", b: " << b << endl;
    PerformBitswap(a, b);
    cout << "a: " << a << ", b: " << b << endl;



    return 0;
}
