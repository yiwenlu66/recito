#ifndef COMMON_HPP
#define COMMON_HPP

#include <vector>
#include <string>

using namespace std;

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

vector<string> split(string s, char delimiter);

string escape(string str, char toEscape, char substitute = '\0');

vector<string> splitWord(string text);

const int HISTORY_PER_PAGE = 4;
const int MAX_MEMORY_WORD = 100;

#endif
