#include "Database.hpp"
#include "Record.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <stdexcept>

using namespace std;

template<class KeyType, class RecordType>
void Database<KeyType, RecordType>::load(string fileName)
{
    ofstream fout;
    fout.open(fileName, ios::app);
    if (fout.is_open())
    {
        mFileName = fileName;
        fout.close();
    }
    else
    {
        fout.close();
        throw * (new runtime_error("Failed to open file for writing!"));
    }

    ifstream fin;
    fin.open(fileName);
    if (fin.is_open())
    {
        mFileName = fileName;
        fin.close();
    }
    else
    {
        fin.close();
        throw * (new runtime_error("Failed to open file for reading!"));
    }
}

template<class KeyType, class RecordType>
RecordType* Database<KeyType, RecordType>::get(KeyType key)
{
    typename map<KeyType, RecordType*>::iterator iter;
    iter = mKeyRecordMap.find(key);
    if (iter == mKeyRecordMap.end())
    {
        return nullptr;
    }
    else
    {
        return iter->second;
    }
}

template<class KeyType, class RecordType>
void Database<KeyType, RecordType>::add(KeyType key, RecordType* record)
{
    if (get(key))
    {
        throw * (new runtime_error("Duplicate key!"));
    }
    else
    {
        mKeyRecordMap[key] = record;
    }
}

template<class KeyType, class RecordType>
const map<KeyType, RecordType*>& Database<KeyType, RecordType>::getKeyRecordMap() const
{
    return mKeyRecordMap;
}

template<class KeyType, class RecordType>
void TextDatabase<KeyType, RecordType>::load(string filename)
{
    Database<KeyType, RecordType>::load(filename);
    ifstream fin(this->mFileName);
    string line;
    KeyType key;
    int lineNumber = 1;
    while (getline(fin, line))
    {
        try
        {
            RecordType* record = new RecordType(line);
            key = record->getKey();
            add(key, record);
            ++lineNumber;
        }
        catch (const runtime_error& e)
        {
            throw * (new runtime_error("Broken record on line " + to_string(lineNumber) + "!"));
        }
    }
    fin.close();
}

template<class KeyType, class RecordType>
void TextDatabase<KeyType, RecordType>::add(KeyType key, RecordType* record)
{
    Database<KeyType, RecordType>::add(key, record);
    mKeyTextMap[key] = record->toString();
}

template<class KeyType, class RecordType>
void TextDatabase<KeyType, RecordType>::update(KeyType key)
{
    if (this->get(key))
    {
        this->mKeyTextMap[key] = this->mKeyRecordMap[key]->toString();
    }
    else
    {
        throw * (new runtime_error("Attempt to update a non-existing key!"));
    }
}

template<class KeyType, class RecordType>
void TextDatabase<KeyType, RecordType>::commit()
{
    ofstream fout(this->mFileName, ios::out);
    typename map<KeyType, string>::iterator iter;
    for (iter = this->mKeyTextMap.begin(); iter != this->mKeyTextMap.end(); ++iter)
    {
        if (iter != this->mKeyTextMap.begin())
        {
            fout << endl;
        }
        fout << iter->second;
    }
    fout.close();
}

template<class KeyType, class RecordType>
TextDatabase<KeyType, RecordType>::~TextDatabase()
{
    typename map<KeyType, RecordType*>::iterator it;
    for (auto item : this->mKeyRecordMap)
    {
        delete item.second;
    }
}

template class Database<string, WordRecord>;
template class Database<string, HistoryRecord>;
template class TextDatabase<string, WordRecord>;
template class TextDatabase<string, HistoryRecord>;
