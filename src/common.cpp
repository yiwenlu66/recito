#include "common.hpp"
#include <sstream>

vector<string> split(string s, char delimiter)
{
    vector<string> elems;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delimiter))
    {
        elems.push_back(item);
    }
    return elems;
}

string escape(string str, char toEscape, char substitute)
{
    string newString;
    for (char c: str)
    {
        if (c != toEscape)
        {
            newString += c;
        }
        else if (substitute)
        {
            newString += substitute;
        }
    }
    return newString;
}
