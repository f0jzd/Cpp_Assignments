#include <iostream>

using namespace std;


template<class T>
T compareValues(T x, T y)
{
    return(x > y);
}



int main() {

    int a, b;

    cout << "Enter two values: ";
    cin >> a >> b;



    cout << "Is " << a << " larger than " << b << "? that is ";
    cout << boolalpha << compareValues<bool>(a, b);


    return 0;
}
