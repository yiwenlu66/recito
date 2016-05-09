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
    SUSPENDED
};

vector<string> split(string s, string delimiter);

#endif