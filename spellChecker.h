#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <map>
#include <set>
#include <chrono>
#include <iomanip>
#include <thread>
#include <type_traits>

using namespace std;

// We use template classes in order to call 2 different types dictionaries.
// One unordered_set, the other set

template <class T>
void missingLetter(const vector<string> &misspelledWords, const T &dictionary, multimap<string, string> &corrections, bool doNotOutput = false)
{
    map<string, string> temp;
    // Loop through misspelled words
    string modifiedWord;
    string letterToBeAdded;
    for (auto mispelledWord : misspelledWords)
    {
        // Loop through word
        for (int i = 0; i < mispelledWord.length(); i++)
        {
            // Add letters to word and check if in dictionary. Lowercase ASCII letters range from 97-122
            for (int j = 97; j <= 122; j++)
            {
                // reset modifiedWord to original word
                modifiedWord = mispelledWord;
                letterToBeAdded = j;

                // Add to end of word
                if (i == mispelledWord.length())
                {
                    modifiedWord = modifiedWord + letterToBeAdded;
                }
                else // add to middle of word
                {
                    modifiedWord = modifiedWord.substr(0, i) + letterToBeAdded + modifiedWord.substr(i);
                }

                // Check if in dictionary, add if so
                if (dictionary.find(modifiedWord) != dictionary.end())
                {
                    if (doNotOutput) // Do not add to corrections, done when called with unordered set dictionary
                        continue;
                    corrections.insert(make_pair(mispelledWord, modifiedWord));
                }
            }
        }
    }
}

template <class T>
void extraLetter(const vector<string> &misspelledWords, const T &dictionary, multimap<string, string> &corrections, bool doNotOutput = false)
{
    // loop through list of misspelled words
    string modifiedWord = "";
    string letterToBeAdded = "";
    for (auto mispelledWord : misspelledWords)
    {
        // Loop through word
        for (int i = 0; i < mispelledWord.length(); i++)
        {
            // reset modified word after each loop
            modifiedWord = mispelledWord;

            // delete letter at index
            modifiedWord = modifiedWord.erase(i, 1);

            // check if in dictionary, add if so
            if (dictionary.find(modifiedWord) != dictionary.end())
            {
                if (doNotOutput) // Do not add to corrections, done when called with unordered set dictionary
                    continue;
                corrections.insert(make_pair(mispelledWord, modifiedWord));
            }
        }
    }
}

template <class T>
void replaceLetter(const vector<string> &misspelledWords, const T &dictionary, multimap<string, string> &corrections, bool doNotOutput = false)
{
    // Loop through list of missplled words
    string modifiedWord = "";
    string letterToBeAdded = "";
    for (auto mispelledWord : misspelledWords)
    {
        // Loop through word
        for (int i = 0; i < mispelledWord.length(); i++)
        {
            // Add letters to word and check if in dictionary. Lowercase ASCII letters range from 97-122
            for (int j = 97; j <= 122; j++)
            {
                // reset modified word after each loop
                modifiedWord = mispelledWord;
                letterToBeAdded = j;

                // replace letter at index
                modifiedWord = modifiedWord.replace(i, 1, letterToBeAdded);

                // check if in dictionary, add if so
                if (dictionary.find(modifiedWord) != dictionary.end())
                {
                    if (doNotOutput) // Do not add to corrections, done when called with unordered set dictionary
                        continue;
                    corrections.insert(make_pair(mispelledWord, modifiedWord));
                }
            }
        }
    }
}

template <class T>
void swapLetters(const vector<string> &misspelledWords, const T &dictionary, multimap<string, string> &corrections, bool doNotOutput = false)
{
    // Loop through list of missplled words
    string modifiedWord = "";
    string letterToBeAdded = "";
    for (auto mispelledWord : misspelledWords)
    {
        // Loop through word, stop one index before end
        for (int i = 0; i < mispelledWord.length() - 1; i++)
        {
            // reset modified word after each loop
            modifiedWord = mispelledWord;

            // Beginning of word + 2 letters swapped + end of word
            modifiedWord = modifiedWord.substr(0, i) + modifiedWord[i + 1] + modifiedWord[i] + modifiedWord.substr(i + 2);

            // check if in dictionary, add if so
            if (dictionary.find(modifiedWord) != dictionary.end())
            {
                if (doNotOutput) // Do not add to corrections, done when called with unordered set dictionary
                    continue;
                corrections.insert(make_pair(mispelledWord, modifiedWord));
            }
        }
    }
}