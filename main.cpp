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
|       to a name and will not be spell checked.                           |
|     Two different dictionaries are used to examine run time, one created |
|       with set, the other with unordered set.                            |
\**************************************************************************/

#include "spellchecker.h"

// argv[1] == name of text file to spellcheck
// argv[2] == name of dictionary text file
int main(int argc, char *argv[])
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
    unordered_set<string> unorderedSetDictionary;

    set<string> setDictionary;

    string word;
    while (dictionaryFile >> word)
    {
        unorderedSetDictionary.insert(word);
        setDictionary.insert(word);
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
                word.erase(word.begin() + i);
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
                        word.erase(word.begin() + i);
                    }

                    firstWord = firstWord + word[j];
                }
                text.push_back(firstWord);

                // second word
                for (int j = i + 1; j < word.length() - 1; j++)
                {
                    // rest of word must be checked for symbols
                    if (word[j] == ',' ||
                        word[j] == '!' ||
                        word[j] == '?' ||
                        word[j] == '.')
                    {
                        word.erase(word.begin() + i);
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

    // detect if word is misspelled (not in dictionary)
    // place misspelled word into vector
    vector<string> misspelledWords;
    vector<string>::iterator misspelledWords_it;

    cout << "Scanning for misspelled words..." << endl;
    // Loop through text
    for (auto text_it = text.begin(); text_it != text.end(); text_it++)
    {
        // Word not in dictionary detected
        if (unorderedSetDictionary.find(*text_it) == unorderedSetDictionary.end())
        {
            // Scan word
            for (int j = 0; j < text_it[0].length(); j++)
            {
                // Apostrophe detected in word, ignore
                if (text_it[0][j] == '\'')
                {
                    goto SkipWord;
                }
            }

            // place into vector of misspelled words
            misspelledWords.push_back(*text_it);

        SkipWord:;
        }
    }

    // Suggest Corrections for misspelled words
    multimap<string, string> corrections;

    string firstHalf, secondHalf, testWord;
    char letter;
    int wordIndex = 0;

    // 4 ERROR CASES
    // RUN EACH ERROR CASE AND KEEP TRACK OF RUN TIME FOR EACH TYPE OF DICTIONARY

    // cout << fixed << setprecision(16) << time_taken;

    double uOSRunTime;
    double sRunTime;

    // CASE 1 - CHECK FOR SINGLE MISSING LETTER

    auto start = chrono::high_resolution_clock::now();
    missingLetter(misspelledWords, unorderedSetDictionary, corrections); // run with unordered_set dictionary
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = end - start;

    uOSRunTime += duration.count();

    start = chrono::high_resolution_clock::now();
    missingLetter(misspelledWords, setDictionary, corrections, true); // run with set dictionary
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    sRunTime += duration.count();

    // CASE 2 - CHECK FOR EXTRA LETTER
    start = chrono::high_resolution_clock::now();
    extraLetter(misspelledWords, unorderedSetDictionary, corrections);
    end = chrono::high_resolution_clock::now();
    duration = end - start;

    uOSRunTime += duration.count();

    start = chrono::high_resolution_clock::now();
    extraLetter(misspelledWords, setDictionary, corrections, true);
    end = chrono::high_resolution_clock::now();
    duration = end - start;

    sRunTime += duration.count();

    // CASE 3 - REPLACE SINGLE LETTER
    start = chrono::high_resolution_clock::now();
    replaceLetter(misspelledWords, unorderedSetDictionary, corrections);
    end = chrono::high_resolution_clock::now();
    duration = end - start;

    uOSRunTime += duration.count();

    start = chrono::high_resolution_clock::now();
    replaceLetter(misspelledWords, setDictionary, corrections, true);
    end = chrono::high_resolution_clock::now();
    duration = end - start;

    sRunTime += duration.count();

    // CASE 4 - SWAP TWO NEIGHBORING LETTERS
    start = chrono::high_resolution_clock::now();
    swapLetters(misspelledWords, unorderedSetDictionary, corrections);
    end = chrono::high_resolution_clock::now();
    duration = end - start;

    uOSRunTime += duration.count();

    start = chrono::high_resolution_clock::now();
    swapLetters(misspelledWords, setDictionary, corrections, true);
    end = chrono::high_resolution_clock::now();
    duration = end - start;

    sRunTime += duration.count();

    // Output misspelled words with suggestions in text file
    ofstream outputFile("spell_check_results.txt");

    outputFile << "Misspelled Words \t Corrections\n";
    outputFile << "---------------- \t -----------\n";

    string previousKey;
    for (const auto &i : corrections)
    {
        outputFile << i.first << "\t\t\t" << i.second << '\t' << '\n';
    }

    cout << "Complete. Misspelled words and suggested corrections have been placed "
         << " in \"spell_check_results.txt\" " << endl;

    cout << "Set Dictionary RunTime: " << sRunTime * 1000.0 << "ms" << endl;
    cout << "Unordered Set Dictionary RunTime: " << uOSRunTime * 1000.0 << "ms" << endl;

    outputFile.close();
}
