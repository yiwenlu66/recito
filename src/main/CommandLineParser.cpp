#include "CommandLineParser.hpp"

CommandLineParser::CommandLineParser(int argc, char* argv[])
{
    for (int i = 0; i < argc; ++i)
    {
        mElements.push_back(argv[i]);
    }
}

bool CommandLineParser::keyExists(string key)
{
    return index(key) != -1;
}

int CommandLineParser::index(string key)
{
    for (int i = 0; i < static_cast<int>(mElements.size()); ++i)
    {
        if (mElements[i] == key)
        {
            return i;
        }
    }
    return -1;
}

string CommandLineParser::getValue(string key)
{
    int i = index(key);
    if (i == -1 || i == static_cast<int>(mElements.size()) - 1)
    {
        return "";
    }
    return mElements[i + 1];
}

string CommandLineParser::getName()
{
    return mElements[0];
}
