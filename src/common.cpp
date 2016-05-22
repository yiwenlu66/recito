#include "common.hpp"
#include <sstream>
#include <cctype>
#include <chrono>

using namespace std;
using namespace std::chrono;

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
    for (char c : str)
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

vector<string>* splitWord(string text)
{
    vector<string>* words = new vector<string>(1, "");
    int j = 0;
    bool isInWord = false;
    for (size_t i = 0; i < text.size(); i++)
    {
        if (isalpha(text[i]))
        {
            (*words)[j].push_back(text[i]);
            isInWord = true;
        }
        else
        {
            if (isInWord)
            {
                isInWord = false;
                words->push_back(string(""));
                j++;
            }
        }
    }
    return words;
}

long long getCurrentTimeStamp()
{
    long long result = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    return result;
}
