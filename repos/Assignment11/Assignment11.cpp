#include <iostream>

using namespace std;

void GetSummary(int* numbers, int arraySize, int& sum)
{
    for (int i = 0; i < arraySize; ++i) {
        sum += numbers[i];
    }
}
void GetSmallestNumber(int* numbers, int arraySize, int& num)
{
    num = numbers[4];
    for (int i = 0; i < arraySize; ++i) {
        if (numbers[i] < num)
        {
            num = numbers[i];
        }
    }
}
void GetHighest(int* numbers, int arraySize, int& num)
{
    num = numbers[0];
    for (int i = 0; i < arraySize; ++i) {
        if (numbers[i] > num)
        {
            num = numbers[i];
        }
    }
}
int main() {

    int sum = 0, arraySize = 0, num;
    float average;
    int numbers[]{ 11,41,62,81,16,23,46,12 };
    for (int value : numbers) {
        arraySize++;
    }
    GetSummary(numbers, arraySize, sum);
    cout << "The sum of all the values are: " << sum << endl;
    cout << "The average of all the values are: " << (float)sum / 8 << endl;
    GetSmallestNumber(numbers, arraySize, num);
    cout << "The smallest of all the values is: " << num << endl;
    GetHighest(numbers, arraySize, num);
    cout << "The smallest of all the values is: " << num << endl;
}
