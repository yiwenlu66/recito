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

WordIterator::WordIterator(vector<WordWithEFI*> words)
    : mWordsToBeTested(words)
{
    sortWords();
}

void WordIterator::sortWords()
{
    sort(mWordsToBeTested.begin(), mWordsToBeTested.end(), [](const WordWithEFI * p1, const WordWithEFI * p2)
    {
        return p1->I > p2->I;
    });
}

string WordIterator::next()
{
    if (mWordsToBeTested.empty())
    {
        return "";
    }
    WordWithEFI* minIntervalPointer = mWordsToBeTested.back();
    mWordsToBeTested.pop_back();
    string word = minIntervalPointer->word;
    delete minIntervalPointer;
    return word;
}

void WordIterator::add(WordWithEFI* wordWithEFI)
{
    for (auto ptr : mWordsToBeTested)
    {
        if (ptr->word == wordWithEFI->word)
        {
            throw * (new runtime_error("Key exists!"));
        }
    }
    if (mWordsToBeTested.size() >= static_cast<unsigned long>(10))
    {
        mWordsToBeTested.insert(mWordsToBeTested.end() - 10, wordWithEFI);
    }
    else
    {
        mWordsToBeTested.insert(mWordsToBeTested.begin(), wordWithEFI);
    }
}

WordIterator::~WordIterator()
{
    for (auto ptr : mWordsToBeTested)
    {
        delete ptr;
    }
}

WordWithEFI::WordWithEFI(string word, double EF, double I)
    : word(word), EF(EF), I(I)
{
}
