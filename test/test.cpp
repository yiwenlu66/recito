#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/algorithm/recito_algorithm.hpp"
#include "../src/common.hpp"
#include "../src/main/CommandLineParser.hpp"
#include <cmath>

using namespace std;

const double EPS = 1e-6;

TEST_CASE("test for common utilities", "[common]")
{
    SECTION("test for split")
    {
        REQUIRE(split("Lorem ipsum dolor sit amet", ' ') == vector<string>({"Lorem", "ipsum", "dolor", "sit", "amet"}));
        REQUIRE(split("Lorem\tipsum\tdolor\tsit\tamet", '\t') == vector<string>({"Lorem", "ipsum", "dolor", "sit", "amet"}));
    }
}

TEST_CASE("test for CommandLineParser", "[command]")
{
    SECTION("test for CommandLineParser")
    {
        char* argv[100];
        CommandLineParser commandLineParser(0, argv);
        argv[0] = const_cast<char *>("./recito");
        commandLineParser = CommandLineParser(1, argv);
        REQUIRE(!commandLineParser.keyExists("-h"));
        REQUIRE(commandLineParser.getValue("-h") == "");
        REQUIRE(commandLineParser.getName() == "./recito");

        argv[0] = const_cast<char *>("recito.exe");
        argv[1] = const_cast<char *>("--help");
        commandLineParser = CommandLineParser(2, argv);
        REQUIRE(commandLineParser.keyExists("--help"));
        REQUIRE(commandLineParser.getValue("--help") == "");
        REQUIRE(commandLineParser.getName() == "recito.exe");

        argv[0] = const_cast<char *>("recito");
        argv[1] = const_cast<char *>("-h");
        argv[2] = const_cast<char *>("history.txt");
        argv[3] = const_cast<char *>("-d");
        argv[4] = const_cast<char *>("dict.txt");
        argv[5] = const_cast<char *>("-a");
        argv[6] = const_cast<char *>("algorithm.so");
        argv[7] = const_cast<char *>("-x");
        commandLineParser = CommandLineParser(8, argv);
        REQUIRE(commandLineParser.getName() == "recito");
        REQUIRE(commandLineParser.keyExists("-h"));
        REQUIRE(commandLineParser.keyExists("-d"));
        REQUIRE(commandLineParser.keyExists("-a"));
        REQUIRE(commandLineParser.keyExists("-x"));
        REQUIRE(!commandLineParser.keyExists("--help"));
        REQUIRE(commandLineParser.getValue("-h") == "history.txt");
        REQUIRE(commandLineParser.getValue("-d") == "dict.txt");
        REQUIRE(commandLineParser.getValue("-a") == "algorithm.so");
        REQUIRE(commandLineParser.getValue("-x") == "");
    }
}

TEST_CASE("test for recito_algorithm", "[algorithm]")
{
    SECTION("test for interval")
    {
        vector<double> intervalCase1 = interval(0, 0, 0);
        vector<double> intervalCase2 = interval(0, 5, 0);
        vector<double> intervalCase3 = interval(1.5, 0, 20);
        vector<double> intervalCase4 = interval(2.2, 3, 1);
        vector<double> intervalCase5 = interval(2, 4, 6);

        REQUIRE(abs(intervalCase1[0] - 1.7) < EPS);
        REQUIRE(abs(intervalCase1[1] - 1) < EPS);
        REQUIRE(abs(intervalCase2[0] - 2.6) < EPS);
        REQUIRE(abs(intervalCase2[1] - 1) < EPS);
        REQUIRE(abs(intervalCase3[0] - 1.3) < EPS);
        REQUIRE(abs(intervalCase3[1] - 1) < EPS);
        REQUIRE(abs(intervalCase4[0] - 2.06) < EPS);
        REQUIRE(abs(intervalCase4[1] - 6) < EPS);
        REQUIRE(abs(intervalCase5[0] - 2) < EPS);
        REQUIRE(abs(intervalCase5[1] - 12) < EPS);
    }

    SECTION("test for group")
    {
        Group groupCase1 = group(Group::UNSEEN, vector<int>({0}), 2.5, 1);
        Group groupCase2 = group(Group::UNSEEN, vector<int>({3}), 2.5, 1);
        Group groupCase3 = group(Group::LEARN, vector<int>({2, 3}), 3, 10);
        Group groupCase4 = group(Group::LEARN, vector<int>({2, 3}), 5, 22);
        Group groupCase5 = group(Group::YOUNG, vector<int>({0, 2, 1, 3}), 4, 15);
        Group groupCase6 = group(Group::YOUNG, vector<int>({0, 2, 1, 3, 3}), 6, 25);
        Group groupCase7 = group(Group::MATURE, vector<int>({0, 2, 1, 3, 3}), 6, 25);
        Group groupCase8 = group(Group::MATURE, vector<int>({0, 2, 1, 3, 3, 0}), 4, 1);
        Group groupCase9 = group(Group::YOUNG, vector<int>({0, 2, 1, 0}), 3, 1);
        Group groupCase10 = group(Group::LEARN, vector<int>({0, 1, 1, 0}), 2, 1);
        Group groupCase11 = group(Group::RELEARN, vector<int>({0, 1, 2, 0, 0, 3, 0, 0, 2, 0, 2, 0, 2, 0, 0, 2, 0, 2, 2, 3, 0, 0, 0, 0, 1, 2, 1, 2, 3, 1, 0, 0, 0, 0}), 1.5, 1);
        Group groupCase12 = group(Group::SUSPENDED, vector<int>({0, 1, 2, 0, 0, 3, 0, 0, 2, 0, 2, 0, 2, 0, 0, 2, 0, 2, 2, 3, 0, 0, 0, 0, 1, 2, 1, 2, 3, 1, 0, 0, 0, 0, 1, 1, 1}), 1.5, 1);

        REQUIRE(groupCase1 == Group::LEARN);
        REQUIRE(groupCase2 == Group::LEARN);
        REQUIRE(groupCase3 == Group::YOUNG);
        REQUIRE(groupCase4 == Group::YOUNG);
        REQUIRE(groupCase5 == Group::YOUNG);
        REQUIRE(groupCase6 == Group::MATURE);
        REQUIRE(groupCase7 == Group::MATURE);
        REQUIRE(groupCase8 == Group::RELEARN);
        REQUIRE(groupCase9 == Group::RELEARN);
        REQUIRE(groupCase10 == Group::LEARN);
        REQUIRE(groupCase11 == Group::SUSPENDED);
        REQUIRE(groupCase12 == Group::YOUNG);
    }

    // TODO: add tests for WordIterator after WordRecord is completed
}
