#include <iostream>
#include <string>
#include <map>

using namespace std;


void compressString(map<char, int>& charMap, string& word)
{

    for (int i = 0; i < word.length(); ++i) {

        auto iter = charMap.find(word[i]);

        if (iter == charMap.end())
        {
            if (word[i] != ' ')
                charMap.insert({ word[i],1 });
        }
        else
        {
            iter->second++;
        }
    }

    string compressedString;
    for (auto val : charMap)
    {
        compressedString += val.first + to_string(val.second);
    }

    cout << sizeof(word) << endl;

    word = compressedString;

    cout << sizeof(word) << endl;
}

void uncompressString(map<char, int>& charMap, string& word)
{
    string uncompressedWord;
    for (auto iter = charMap.begin(); iter != charMap.end(); iter++) {
        for (int i = 0; i < iter->second; ++i) {
            uncompressedWord += iter->first;
        }
    }
    word = uncompressedWord;
}




int main() {

    string word;
    map<char, int> compStrMap;

    cout << "Enter a word: ";
    getline(cin, word);
    compressString(compStrMap, word);
    cout << word << endl;
    uncompressString(compStrMap, word);
    cout << word << endl;



    /*for (auto val : compStrMap)
    {
        cout << val.first << val.second;
    }*/


    /*
    cout << endl;

    uncompressString(compStrMap);*/

    return 0;
}
