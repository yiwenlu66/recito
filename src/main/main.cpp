#include "CommandLineParser.hpp"
#include "MainLoop.hpp"
#include <iostream>
#include <string>

using namespace std;

const string DEFAULT_MAIN_DATABASE_FILE_NAME = "res/dict.txt";
const string DEFAULT_HISTORY_FILE_NAME = "history.txt";
const string DEFAULT_ALGORITHM_LIB_FILE_NAME = "algorithm.so";

void printUsage(const CommandLineParser&);

int main(int argc, char* argv[])
{
    CommandLineParser commandLineParser(argc, argv);
    if (commandLineParser.keyExists("--help"))
    {
        printUsage(commandLineParser);
        return 0;
    }
    string mainDatabaseFileName = commandLineParser.keyExists("-d") ?
                                  commandLineParser.getValue("-d") : DEFAULT_MAIN_DATABASE_FILE_NAME;
    string historyFileName = commandLineParser.keyExists("-h") ?
                             commandLineParser.getValue("-h") : DEFAULT_HISTORY_FILE_NAME;

    MainLoop mainLoop(mainDatabaseFileName, historyFileName);
    mainLoop.run();

    return 0;
}

void printUsage(const CommandLineParser& commandLineParser)
{
    cout << "Usage: " << commandLineParser.getName() << " "
         << "[--help] "
         << "[-d <main database file name>] "
         << "[-h <history file name>] "
         << "[-a <algorithm library file name>] "
         << endl << endl
         << "Arguments: " << endl
         << "--help" << "\t" << "show this message" << endl
         << "-d" << "\t" << "main database file name" << "\t\t" << "default: res/dict.txt" << endl
         << "-h" << "\t" << "history file name" << "\t\t" << "default: history.txt" << endl
         << "-a" << "\t" << "algorithm library file name" << "\t" << "default: algorithm[.dll/.so/.dylib]" << endl
         ;
}
