#ifndef RECITO_ALGORITHM_HPP
#define RECITO_ALGORITHM_HPP

#include "../common.hpp"
#include "../main/Record.hpp"
#include <vector>
#include <map>

using namespace std;

vector<double> interval(double EF, int q, double I);  // implement SM2 algorithm: https://www.supermemo.com/english/ol/sm2.htm, return new EF and new I; pass in 0 for EF and I for an unseen word.

Group group(Group oldGroup, const vector<int>& answers, double EF, double I);   // find new group by Anki standard: https://www.supermemo.com/english/ol/sm2.htm

class WordIterator
{
public:
    WordIterator(map<string, WordRecord*>);
    string next();  // return a word and pop it; return empty string if all words have been traversed through
    void add(WordRecord&);

private:
    map<string, WordRecord*> mWordsToBeTested;
};

#endif
