#pragma once

#include <unordered_map>

/**
 * @brief Map is temporarly implemented on top of unorderedmap.
 */
template<typename KeyType, typename ValueType>
class Map
{
private:
    std::unordered_map<KeyType, ValueType> data;

public:
    Map(){}
    Map(const Map& Other)
    {
        data = Other.data;
    }

    void Add(KeyType Key, ValueType Value)
    {
        data.insert({Key, Value});
    }

    void Remove(KeyType Key)
    {
        auto search = data.find(Key);
        if(search == data.end())
        {
            return;
        }

        data.erase(Key);
    }

    void Clear()
    {
        data.clear();
    }

    bool Contains(KeyType Key) const
    {
        return data.find(Key) != data.end();
    }

    int Size() const { return data.size(); }

    ValueType& operator [](const KeyType& Key)
    {
        return data[Key];
    }

    typename std::unordered_map<KeyType, ValueType>::iterator begin(){ return data.begin(); }
    typename std::unordered_map<KeyType, ValueType>::iterator end(){ return data.end(); }
};
