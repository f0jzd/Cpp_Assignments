#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {

    map<char, int> characterInWord;

    string word;


    cout << "Enter a word: ";
    getline(cin, word);



    for (int i = 0; i < size(word); ++i) {

        auto iter = characterInWord.find(word[i]);

        if (iter == characterInWord.end()) {
            if (word[i] != ' ') {
                characterInWord.insert({ word[i], 1 });
            }
        }
        else {
            iter->second++;
        }
    }


    for (auto a : characterInWord) {
        cout << a.first << " : " << a.second << endl;
    }



    //if (characterInWord.count())


    return 0;
}
