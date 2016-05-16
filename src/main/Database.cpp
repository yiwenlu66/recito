#include "Database.hpp"
#include "Record.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

template<class KeyType, class RecordType>
void Database<KeyType, RecordType>::load(string fileName)
{
    ifstream fin;
    fin.open(fileName);
    if (fin.is_open())
    {
        mFileName = fileName;
        fin.close();
    }
    else
    {
        cout << "fail in open files" << endl;
        fin.close();
        exit(1);
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
        cout << "duplicate key" << endl;
        exit(1);
    }
    else
    {
        mKeyRecordMap[key] = record;
    }
}

template<class KeyType, class RecordType>
void TextDatabase<KeyType, RecordType>::load(string filename)
{
    Database<KeyType, RecordType>::load(filename);
    ifstream fin(this->mFileName);
    string temp;
    KeyType key;
    while (getline(fin, temp))
    {
        RecordType rtemp(temp);
        key = rtemp.getKey();
        this->mKeyTextMap[key] = temp;
        this->mKeyRecordMap[key] = new RecordType(temp);
    }
    fin.close();
}

template<class KeyType, class RecordType>
void TextDatabase<KeyType, RecordType>::add(KeyType key, RecordType* record)
{
    Database<KeyType, RecordType>::add(key, record);
    this->mKeyTextMap[key] = record->toString();
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
        cout << "no such input" << endl;
    }
}

template<class KeyType, class RecordType>
void TextDatabase<KeyType, RecordType>::commit()
{
    ofstream fout(this->mFileName, ios::out);
    typename map<KeyType, string>::iterator iter;
    for (iter = this->mKeyTextMap.begin(); iter != this->mKeyTextMap.end(); ++iter)
    {
        if (iter != this->mKeyTextMap.begin()) {
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
    for (auto item: this->mKeyRecordMap)
    {
        // uncomment after Record::~Record() is implemented
        //delete item.second;
    }
}

template class TextDatabase<string, WordRecord>;
