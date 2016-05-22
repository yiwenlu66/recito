#ifndef COMMON_HPP
#define COMMON_HPP

#include <vector>
#include <string>

using namespace std;

// constants
const int HISTORY_PER_PAGE = 10;
const int MAX_MEMORY_WORD = 100;
const int EXAM_NUM_OPTIONS = 4;


// enum classes

enum class Group
{
    UNSEEN,
    LEARN,
    YOUNG,
    MATURE,
    RELEARN,
    SUSPENDED,
    ALL     // intended for category chooser only
};

enum class ViewClass
{
    MAIN_MENU,
    CHOOSE_CATEGORY,
    REVIEW_QUESTION,
    REVIEW_ANSWER,
    REVIEW_COMPLETE,
    DICT_MENU,
    DICT_INPUT,
    DICT_HISTORY,
    DICT_HISTORY_EMPTY,
    DICT_WORD,
    DICT_WORD_NOT_EXIST,
    EXAM_CHOOSE_NUMBER,
    EXAM_QUESTION,
    EXAM_ANSWER,
    EXAM_COMPLETE,
    TEXT_CHOOSE_FILE,
    TEXT_NOT_FIND_FILE,
    TEXT_WORD,
    EDIT
};

enum class ControlClass
{
    MAIN_MENU,
    MEMORY,
    DICT,
    EXAM,
    TEXT,
    QUIT
};

// auxiliary functions
vector<string> split(string s, char delimiter);
string escape(string str, char toEscape, char substitute = '\0');
vector<string> splitWord(string text);
long long getCurrentTimeStamp();

#endif
