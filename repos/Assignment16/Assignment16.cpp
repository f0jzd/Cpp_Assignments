#include <iostream>

using namespace std;



bool ContainsWord(string sentence, int sentenceSize, string substr, int substrSize)
{
    int temp = 0;

    cout << sentenceSize;

    for (int i = 0; i < sentenceSize; ++i) {

        cout << sentence[i] << " : " << substr[temp] << endl;

        if (sentence[i] == substr[temp])
        {
            temp++;
        }
        else
        {
            temp = 0;
        }
        if (temp == substrSize)
        {
            return true;
        }
    }
    return false;
}


int main() {

    string sentence, substr = "name";

    int sentenceSize, substrSize;


    bool doesContain = false;


    cout << "Input a sentence: " << endl;
    getline(cin, sentence);

    cout << size(sentence) << endl;

    sentenceSize = size(sentence);
    substrSize = size(substr);


    doesContain = ContainsWord(sentence, sentenceSize, substr, substrSize);

    if (doesContain)
        cout << "The word ''" << sentence << "'' does contain the substring ''" << substr << "''" << endl;
    if (!doesContain)
        cout << "The word ''" << sentence << "'' does NOT contain the substring ''" << substr << "''" << endl;

}
