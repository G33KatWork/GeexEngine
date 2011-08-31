#ifndef _GX_DATASTRUCTURES_DICTIONARY_H_
#define _GX_DATASTRUCTURES_DICTIONARY_H_

#include <DataStructures/Hashtable.h>
#include <Utils/CRC32.h>

//TODO: iterators

//KeyValuePair as a container for the dictionary
template <typename DictionaryKeyType, typename DictionaryValueType>
class KeyValuePair
{
    template<typename DictionaryKeyType, typename DictionaryValueType, typename Allocator>
    friend class Dictionary;

public:
    DictionaryKeyType   key;
    DictionaryValueType value;

    KeyValuePair(DictionaryKeyType key, DictionaryValueType value)
        : key(key),
        value(value)
    {}

private:
    struct HashTableDefinition
    {
        typedef DictionaryKeyType   KeyType;
        typedef KeyValuePair        ValueType;

        size_t HashKey(const KeyType key) const { return (size_t)CRC32((char*)&key, sizeof(KeyType)); }
        size_t Hash(ValueType* value) const { return HashKey(value->key); }
        bool Compare(KeyType key, ValueType* value) const { return value->key == key; }
        ValueType*& GetLink(ValueType* value) const { return value->next; }
    };

    KeyValuePair<DictionaryKeyType, DictionaryValueType>* next;
};

//The dictionary implemented with a HashTable and some wrapperfunctions for allocating and deallocating the KeyValuePairs
//TODO: Let user choose KeyValuePair allocator with template stuff
template <typename KeyType, typename ValueType, typename Allocator = MallocAllocator>
class Dictionary
{
protected:
    BHashTable<struct KeyValuePair<KeyType, ValueType>::HashTableDefinition, true, false, Allocator> hashTable;

public:
    size_t GetItemCount() const { return hashTable.GetItemCount(); }
    ValueType& Lookup(const KeyType& key) const { return hashTable.Lookup(key)->value; }
    
    void Clear()
    {
        KeyValuePair<KeyType, ValueType>* itemList = hashTable.Clear(true);
        while(itemList)
        {
            KeyValuePair<KeyType, ValueType>* next = itemList->next;
            delete itemList;
            itemList = next;
        }
    }

    bool Insert(const KeyType& key, ValueType value)
    { 
        KeyValuePair<KeyType, ValueType> *kv = new KeyValuePair<KeyType, ValueType>(key, value);
        return hashTable.Insert(kv);
    }

    bool Remove(const KeyType& key)
    {
        KeyValuePair<KeyType, ValueType>* toRemove = hashTable.Lookup(key);
        if(toRemove)
        {
            bool ret = hashTable.Remove(toRemove);
            delete toRemove;
            return ret;
        }
        else
            return false;
    }

    ValueType& operator[] (const KeyType& key) const { return this->Lookup(key); }
};

#endif
