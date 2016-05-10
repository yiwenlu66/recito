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
    string getName();

private:
    vector<string> mElements;
    int index(string key);
};

#endif
