#include <iostream>
#include <string>

using namespace std;



void Permutations(string str, int i, int n)
{
    if (i==n-1)
    {
        cout << str << endl;
        return;
    }
    for (int j = i; j < n; j++) {
        swap(str[i],str[j]);

        Permutations(str,i+1,n);

        swap(str[i],str[j]);
    }

}


int main() {

    string abc = "ABC";

    Permutations(abc,0,abc.length());





    return 0;
}
