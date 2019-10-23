/**************************************************************************\
|   Jonah Alexander-Awad                                                   |
|   Simple Spell checker for CSCI 335                                      |
|                                                                          |
|   Requirements:                                                          |
|     Command line argument 1 must be the text file to be spellchecked     |
|     Command line argument 2 must be a dictionary text file which         |
|       the program will use as its dictionary                             |
|                                                                          |
|   NOTES:                                                                 |
|     If a word has an apostrophe, the apostrophe is assumed to belong     |
|       to a name and will not be spellchecked.                            |
\**************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

// argv[1] == name of text file to spellcheck
// argv[2] == name of dictionary text file
int main(int argc, char* argv[])
{
    // open dictionary file
    ifstream dictionaryFile(argv[2]);
    cout << "Opening \"" << argv[2] << ".\"" << endl;

    // error check
    if (dictionaryFile.fail())
    {
        cerr << "Dictionary File Not Found" << endl;
        exit(1);
    }
    cout << "Opening \"" << argv[2] << "\" successful, loading contents." << endl;

    // place words in dictionary into container (unordered_set)
    unordered_set<string> dictionary;
    unordered_set<string>::iterator dictionary_it;

    string word;
    while (dictionaryFile >> word)
    {
        dictionary.insert(word);
    }

    // close dictionary file
    dictionaryFile.close();
    cout << "Complete. Closing. " << endl;


    // open text file requiring spellcheck
    ifstream textFile(argv[1]);
    cout << "Opening \"" << argv[1] << ".\"" << endl;

    // error check
    if (textFile.fail())
    {
        cerr << "Text File Not Found" << endl;
        exit(1);
    }
   cout << "Opening \"" << argv[1] << "\" successful, loading contents." << endl;

    // place words needing to be spell checked into vector
    vector<string> text;
    vector<string>::iterator text_it;
    string firstWord, secondWord;

    while (textFile >> word)
    {
        // if first letter is capital, convert to lowercase
        word[0] = tolower(word[0]);

        // Punctuation detected in word, remove it
        for (int i = 0; i < word.length(); i++)
        {
            if (word[i] == ',' ||
                word[i] == '!' ||
                word[i] == '?' ||
                word[i] == '.')
            {
                word.erase(word.begin()+i);
            }
            // in case of hyphen, split it into 2 words
            else if (word[i] == '-')
            {
                // first word
                for (int j = 0; j < i; j++)
                {
                    // rest of word must be checked for symbols
                    if (word[j] == ',' ||
                        word[j] == '!' ||
                        word[j] == '?' ||
                        word[j] == '.')
                    {
                        word.erase(word.begin()+i);
                    }

                    firstWord = firstWord + word[j];
                }
                text.push_back(firstWord);
    
                // second word
                for (int j = i+1; j < word.length()-1; j++)
                {
                    // rest of word must be checked for symbols
                    if (word[j] == ',' ||
                        word[j] == '!' ||
                        word[j] == '?' ||
                        word[j] == '.')
                    {
                        word.erase(word.begin()+i);
                    }
                    secondWord = secondWord + word[j];
                }
                text.push_back(secondWord);

                goto SkipAdding;
            }
        }

        text.push_back(word);
        SkipAdding:;
    }

    // close text file
    textFile.close();
    cout << "Complete. Closing. " << endl;
    

    // detect if word is mispelled (not in dictionary)
    // place mispelled word into vector
    vector<string> mispelledWords;
    vector<string>::iterator mispelledWords_it;

    cout << "Scanning for mispelled words..." << endl;
    // Loop through text
    for (text_it = text.begin(); text_it != text.end(); text_it++)
    {
        // Word not in dictionary detected
        if (dictionary.find(*text_it) == dictionary.end())
        {
            // Scan word
            for (int j = 0; j < text_it[0].length(); j++)
            {
                // Apostrophe detected in word, ignore 
                if (text_it[0][j] == '\'' )
                {
                    goto SkipWord;
                }
            }

            // place into vector of mispelled words
            mispelledWords.push_back(*text_it);

            SkipWord:;
        }
    }

    cout << "Complete. Mispelled words and suggested corrections have been placed "
         << " in \"spell_check_results.txt\" " << endl;

    // Output mispelled words with suggestions in text file
    ofstream outputFile("spell_check_results.txt");

    for (mispelledWords_it = mispelledWords.begin(); mispelledWords_it != mispelledWords.end(); mispelledWords_it++)
    {
        outputFile << *mispelledWords_it << endl;
    }

    outputFile.close();
}