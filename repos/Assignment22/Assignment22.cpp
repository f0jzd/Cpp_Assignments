#include <iostream>


template<typename T>

T SwapFunc(T& a, T& b)
{

    a += b;
    b = a - b;
    a -= b;

}

int main() {

    float a{ 5.2 };
    float b{ 20.1 };


    std::cout << a << " : " << b << std::endl;

    SwapFunc<float>(a, b);

    std::cout << a << " : " << b << std::endl;




    return 0;
}
