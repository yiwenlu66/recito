#include "recito_algorithm.hpp"
#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;

vector<double> interval(double EF, int q, double I)
{
    if (EF == 0)
    {
        EF = 2.5;
    }
    EF = EF - 0.8 + 0.28 * q - 0.02 * q * q;
    if (EF < 1.3)
    {
        EF = 1.3;
    }

    if (q < 3 || I == 0)
    {
        I = 1;
    }
    else if (I == 1)
    {
        I = 6;
    }
    else
    {
        I *= EF;
    }
    return vector<double>({EF, I});
}

Group group(Group oldGroup, const vector<int>& answers, double EF, double I)
{
    if (oldGroup != Group::SUSPENDED && count(answers.begin(), answers.end(), 0) > 15)
    {
        return Group::SUSPENDED;
    }
    switch(oldGroup)
    {
    case Group::UNSEEN:
        return Group::LEARN;
    case Group::LEARN:
    case Group::RELEARN:
        if (answers[answers.size() - 1] > 0)
        {
            return Group::YOUNG;
        }
        return oldGroup;
    case Group::YOUNG:
    case Group::MATURE:
        if (answers[answers.size() - 1] == 0)
        {
            return Group::RELEARN;
        }
        if (I > 21)
        {
            return Group::MATURE;
        }
        return Group::YOUNG;
    case Group::SUSPENDED:
        if (answers[answers.size() - 1] && answers[answers.size() - 2] && answers[answers.size() - 3])
        {
            return Group::YOUNG;
        }
        return Group::SUSPENDED;
    }
}

WordIterator::WordIterator(map<string, WordWithEFI*> keyRecordMap)
    : mWordsToBeTested(keyRecordMap)
{
}

string WordIterator::next()
{
    if (mWordsToBeTested.empty())
    {
        return "";
    }
    using pairType = decltype(mWordsToBeTested)::value_type;
    auto maxCursor = max_element
                     (
                         mWordsToBeTested.begin(),
                         mWordsToBeTested.end(),
                         [] (const pairType& p1, const pairType& p2)
                            {
                                return p1.second->I > p2.second->I;
                            }
                     );
    mWordsToBeTested.erase(maxCursor->first);
    string word = maxCursor->second->word;
    delete maxCursor->second;
    return word;
}

void WordIterator::add(WordWithEFI* wordWithEFI)
{
    if (mWordsToBeTested.find(wordWithEFI->word) != mWordsToBeTested.end())
    {
        throw * (new runtime_error("Key exists!"));
    }
    mWordsToBeTested.insert(pair<string, WordWithEFI*>(wordWithEFI->word, wordWithEFI));
}

WordWithEFI::WordWithEFI(string word, double EF, double I)
    : word(word), EF(EF), I(I)
{
}
