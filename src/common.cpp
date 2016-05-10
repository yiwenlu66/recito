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
