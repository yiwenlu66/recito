#ifndef COMMANDLINEPARSER_HPP
#define COMMANDLINEPARSER_HPP

#include <string>
#include <vector>

using namespace std;

class CommandLineParser
{
public:
    CommandLineParser(int argc, char* argv[]);
    bool keyExists(string key);
    string getValue(string key);

private:
    vector<string> mSplit;  // call split() from common.hpp
};

#endif
