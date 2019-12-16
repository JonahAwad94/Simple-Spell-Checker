# Simple Spell Checker
 Simple Spell Checker Assignment done in C++ for Software Analysis and Design 3 course (CSCI 335) at Hunter College
 
# To Run Spell Checker
 - Navigate to the same directory as "spellchecker"
 
 
 - Command template is as follows:
 
 
 ./spellchecker <check_it.txt> <dictionary.txt>
 
 
 
 "check_it.txt" may be changed to any text document you would like to be spellchecked.
 
 "dictionary.txt" is a default dictionary provided with the program. You may modify the words in the dictionary or provide your own dictionary.txt
 
 
 
 When spell checking is complete, misspelled words along with their corrections are placed in "spell_check_result.txt"
 
 
 
 # Notes:
  - If a word contains an apostrophe, the apostrophe is assumed to belong to a name and will not be spell checked.
  - Two different dictionaries are created at runtime to examine look up time differences between a set and unordered set.
  - Spell checker will correct the following errors:
    - Missing Letter ("moter" -> "mother")
    - Extra Letter ("cadse" -> "case")
    - Replace Letter ("moter" -> "meter", "motor")
    - Neighboring Letters Swapped ("nto" -> "not")
    
 
 # Example Text
 <img src="/textPreview.jpg">
 
 
 
 # Example Correction
 <img src="/correctionPreview.jpg">
