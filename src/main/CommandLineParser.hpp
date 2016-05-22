#ifndef COMMANDLINEPARSER_HPP
#define COMMANDLINEPARSER_HPP

#include <string>
#include <vector>

using namespace std;

class CommandLineParser
{
public:
    CommandLineParser(int argc, char* argv[]);
    bool keyExists(string key) const;
    string getValue(string key) const;
    string getName() const;

private:
    vector<string> mElements;
    int index(string key) const;
};

#endif
