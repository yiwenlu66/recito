#ifndef RECORD_HPP
#define RECORD_HPP

#include <string>
#include <vector>
#include "../common.hpp"

using namespace std;

template <class KeyType>
class Record
{
public:
    Record() = default;
    virtual string toString() const = 0;
    KeyType getKey() const;
    virtual ~Record() = default;

protected:
    KeyType mKey;
};

class WordRecord: public Record<string>
{
public:
    WordRecord(const string&);
    virtual string toString() const;
    string getExplanation() const;
    string getExample() const;
    Group getGroup() const;
    const vector<int>& getAnswers() const;
    const vector<double>& getAlgorithmOutput() const;
    void setExample(string);
    void setGroup(Group);
    void addAnswer(int);
    void setAlgorithmOutput(vector<double>);

private:
    string mExplanation;
    string mExample;
    Group mGroup;
    vector<int> mAnswers;
    vector<double> mAlgorithmOutput;
};

class HistoryRecord: public Record<string>
{
public:
    // newRecord = true:    the string as the word, use the current timestamp
    // newRecord = false:   both the word and the timestamp will be parsed from the string
    HistoryRecord(string, bool newRecord = false);
    long long getTimeStamp() const;
    void setTimeStamp(long long);
    virtual string toString() const;

private:
    long long mTimestamp;
};

#endif
