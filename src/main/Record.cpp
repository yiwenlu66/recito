#include "Record.hpp"
#include <sstream>

template<class KeyType>
KeyType Record<KeyType>::getKey() const
{
    return mKey;
}

WordRecord::WordRecord(string str)
{
    vector<string> inputs = split(str, '\t');
    mKey = inputs[0];
    mExample = inputs[1];
    mExplanation = inputs[2];
    switch (inputs[3][0] - '0')
    {
    case 0:
        mGroup = Group::UNSEEN;
        break;
    case 1:
        mGroup = Group::LEARN;
        break;
    case 2:
        mGroup = Group::YOUNG;
        break;
    case 3:
        mGroup = Group::MATURE;
        break;
    case 4:
        mGroup = Group::RELEARN;
        break;
    case 5:
        mGroup = Group::SUSPENDED;
        break;
    default:
        break;
    }
    vector<string> ans = split(inputs[4], ';');
    for (unsigned long i = 0; i < ans.size(); i++)
    {
        mAnswers[i] = ans[i][0] - '0';
    }
    vector<string> Alg = split(inputs[5], ';');
    for (unsigned long i = 0; i < Alg.size(); i++)
    {
        mAlgorithmOutput[i] = atof(Alg[i].c_str());
    }
}

string WordRecord::toString() const
{
    stringstream ss;
    ss << mKey << '\t' << mExample << '\t' << mExplanation << '\t' << char(int(mGroup) + '0') << '\t';
    for (unsigned long i = 0; i < mAnswers.size(); ++i)
    {
        if (i > 0)
        {
            ss << ';';
        }
        ss << char(mAnswers[i] + '0');
    }
    ss << '\t';
    for (unsigned long i = 0; i < mAlgorithmOutput.size(); ++i)
    {
        if (i > 0)
        {
            ss << ';';
        }
        ss << mAlgorithmOutput[i];
    }
    return ss.str();
}

string WordRecord::getExample() const
{
    return mExample;
}

string WordRecord::getExplanation() const
{
    return mExplanation;
}

Group WordRecord::getGroup() const
{
    return mGroup;
}

const vector<int>& WordRecord::getAnswers() const
{
    return mAnswers;
}

const vector<double>& WordRecord::getAlgorithmOutput() const
{
    return mAlgorithmOutput;
}

void WordRecord::setExample(string exp)
{
    mExample = exp;
}

void WordRecord::setGroup(Group group)
{
    mGroup = group;
}

void WordRecord::setAlgorithmOutput(vector<double> al)
{
    mAlgorithmOutput = al;
}

void WordRecord::addAnswer(int m)
{
    mAnswers.push_back(m);
}

HistoryRecord::HistoryRecord(string str)
{
    mKey = str;
}

string HistoryRecord::toString() const
{
    return mKey;
}
