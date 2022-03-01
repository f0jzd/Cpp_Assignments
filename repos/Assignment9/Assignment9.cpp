#include <iostream>


using namespace std;
void LinearSearch(int array[8], int numToFind, int arraySize, int& count);


int main() {


    int nr, arrSize;
    int count{ 0 };
    int arr[8]{ 3,4,6,12,3,2,4,51 };

    cout << "enter nr to find: ";
    cin >> nr;

    arrSize = sizeof(arr) / sizeof(int);


    LinearSearch(arr, nr, arrSize, count);


    return 0;
}
void LinearSearch(int array[8], int numToFind, int arraySize, int& count)
{

    for (int i = 0; i < arraySize; ++i) {

        if (array[i] == numToFind)
        {
            cout << "Number was found!" << endl;
            count += 1;
        }
    }

    cout << "Number was found " << count << " times!" << endl;

}
