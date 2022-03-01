#include <iostream>

void SwapNumsPointer(int* n1, int* n2);
void SwapNumsReference(int& nr1, int& nr2);
int main() {
    int nr1, nr2;

    ///Swapping using std::swap
    //std::cout << "Input number A: ";
    //std::cin >> nr1;
    //std::cout << "Input number B: ";
    //std::cin >>nr2;
    //std::cout << "Swapping";
    //std::swap(nr1,nr2);
    //std::cout << nr1 <<" "<< nr2;

    ///Swapping With Reference
    std::cout << "Input number A: ";
    std::cin >> nr1;
    std::cout << "Input number B: ";
    std::cin >> nr2;
    std::cout << "Swapping: ";
    SwapNumsReference(nr1, nr2);
    std::cout << nr1 << " " << nr2;

    ///Swapping with Pointer
    std::cout << "Input number A: ";
    std::cin >> nr1;
    std::cout << "Input number B: ";
    std::cin >> nr2;
    std::cout << "Swapping: ";
    SwapNumsPointer(&nr1, &nr2);
    std::cout << nr1 << " " << nr2;


}
void SwapNumsPointer(int* n1, int* n2)
{
    int z = *n1;
    *n1 = *n2;
    *n2 = z;
}
void SwapNumsReference(int& nr1, int& nr2)
{
    int z = nr1;
    nr1 = nr2;
    nr2 = z;
}


