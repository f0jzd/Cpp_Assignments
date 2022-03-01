#include <iostream>

using namespace std;

class A {
public:
    A() {
        cout << "Constructor A called" << endl;
    }
    ~A() {
        cout << "Destructor A Called" << endl;
    }
};
class B : A {
public:
    B() {
        cout << "Constructor B Called" << endl;
    }
    ~B() {
        cout << "Destructor B Called" << endl;
    }
};
class C : B {
public:
    C() {
        cout << "Constructor C Called" << endl;
    }
    ~C() {
        cout << "Destructor C Called" << endl;
    }
};

int main() {

    C c;



}

