# Simple Spell Checker
 Simple Spell Checker Assignment done in C++ for Software Analysis and Design 3 course (CSCI 335) at Hunter College.
 
 # Assignment Description
 
The purpose of the assignment was build a spell checker and compare the runtimes between C++'s "unordered_set" and "set" data types. C++'s "unordered_set" data type is implemented using a hash table, which is optimal for a dictionary as the average look up time for a word would be O(1). C++'s "set" implementations vary but are typically implemented as red-black trees which have a look up time of O(log n). With this in mind, the runtimes for the "underordered_set" dictionary were expected to be significantly shorter than the "set" dictionary's runtime and the results confirmed this.
 
# To Run Spell Checker
 - Navigate to the same directory as "spellchecker" in your terminal
 - Command template is as follows:
   - ./spellchecker <check_it.txt> <dictionary.txt>
 
 
 
 "check_it.txt" may be changed to any text document you would like to be spellchecked.
 
 "dictionary.txt" is a default dictionary provided with the program. You may modify the words in the dictionary or provide your own "dictionary.txt."
 - If modifying or providing your own "dictionary.txt", be sure to keep the formatting the same, one word per line.
 
 
 
When spell checking is complete, misspelled words along with their suggested corrections are placed in "spell_check_result.txt" and the runtimes for each dictionary type will be displayed in the console.
 
 
 
 # Notes:
  - If a word contains an apostrophe, the apostrophe is assumed to belong to a name and will not be spell checked.
  - Two different dictionaries are created at runtime to examine look up time differences between a set and unordered set.
  - Spell checker will correct the following errors:
    - Missing Letter ("moter" -> "mother")
    - Extra Letter ("cadse" -> "case")
    - Replace Letter ("moter" -> "meter", "motor")
    - Neighboring Letters Swapped ("nto" -> "not")
    
    
    
    
 
 # Sample Text
 <img src="/textPreview.jpg">
 
 
 
 
 
 
 # Sample Correction Suggestions
 <img src="/correctionPreview.jpg">
