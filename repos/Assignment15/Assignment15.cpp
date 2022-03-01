#include <iostream>
#include <map>
using namespace std;

int main() {

    map<char, int> numberMap;

    bool isLucky = false;

    int num;

    string theNumbers;

    cout << "Enter a number: ";
    cin >> num;

    theNumbers = to_string(num);
    char num_char[theNumbers.length() + sizeof(char)];
    sprintf(num_char, "\%d", num);

    for (int i = 0; i < theNumbers.length(); ++i) {

        cout << num_char[i] << endl;

        auto iter = numberMap.find(num_char[i]);

        if (iter == numberMap.end())
        {
            numberMap.insert({ num_char[i],1 });
        }
        else
        {
            iter->second++;
        }

    }
    for (auto a : numberMap) {
        cout << a.first << " : " << a.second << endl;

        if (a.second > 1)
        {
            isLucky = false;
        }
        else
        {
            isLucky = true;
        }
    }

    if (isLucky)
        cout << num << " is lucky!" << endl;
    else
        cout << num << " is not lucky" << endl;






    return 0;
}
