#include <iostream>

using namespace std;

int fibonacciRecursive(int n, int a, int b)
{
    if (n > 0)
    {
        int result = a + b;
        cout << result << ", ";
        a = b;
        n--;
        fibonacciRecursive(n, a, result);
    }
}

void fibonacciIterative(int n)
{
    int nextVal{ 0 };
    int t1{ 0 };
    int t2{ 1 };

    for (int i = 0; i < n; ++i) {

        nextVal = t1 + t2;
        t1 = t2;
        t2 = nextVal;

        cout << nextVal << ", ";
    }
}


int main() {

    int n, a = 0, b = 1;

    cout << "Enter the number: ";
    cin >> n;

    cout << "Iterative: ";
    fibonacciIterative(n);

    cout << "\n";

    cout << "Recursive: ";
    fibonacciRecursive(n, a, b);


}


