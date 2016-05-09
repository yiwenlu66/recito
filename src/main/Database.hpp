#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <map>

using namespace std;

template<class KeyType, class RecordType>
class Database
{
public:
    virtual void load(string fileName);     // check r/w permissions (raise exception on failure) and save the file name
    RecordType* get(KeyType key) const;     // return nullptr if the record does not exist
    virtual void add(KeyType key, const RecordType& record);    // add the entry to mKeyRecordMap (raise exception for duplicate key)
    virtual void update(KeyType key) = 0;   // stage changes for commit
    virtual void commit() = 0;              // save changes to the database file

protected:
    string mFileName;
    map<KeyType, RecordType*> mKeyRecordMap;
};

template<class KeyType, class RecordType>
class TextDatabase: public Database<KeyType, RecordType>
{
public:
    virtual void load(string fileName);     // use Database::load(), read data into mKeyTextMap, and parse data into mKeyRecordMap
    virtual void add(KeyType key, const RecordType& record);    // use Database::add() and sync to mKeyTextMap
    virtual void update(KeyType key);       // sync changes to the record to mKeyTextMap
    virtual void commit();                  // write mKeyTextMap to mFileName
private:
    map<KeyType, string> mKeyTextMap;
};

#endif
