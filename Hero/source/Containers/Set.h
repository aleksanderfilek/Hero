#pragma once

#include "Array.h"

template<typename ElementType>
struct SetIterator
{
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = ElementType;
    using pointer = ElementType*;
    using reference = ElementType&;

    SetIterator(ElementType* Data, int Length, int Index)
        : data(Data), length(Length), index(Index) {}

    reference operator*() const { return data[index]; }
    pointer operator->() { return &data[index]; }

    // Prefix increment.
    SetIterator& operator++()
    {
        index++;
        return *this;
    }

    // Postfix increment.
    SetIterator operator++(int)
    {
        ArrayIterator tmp(data, length, index);
        index++;
        return tmp;
    }

    friend bool operator== (const SetIterator& a, const SetIterator& b) { return a.index == b.index; };
    friend bool operator!= (const SetIterator& a, const SetIterator& b) { return a.index != b.index; };

    SetIterator operator-(int Value)
    {
        ArrayIterator tmp = *this;
        tmp.index - 1;
        return tmp;
    }

private:
    ElementType* data = nullptr;
    int length = 0;
    int index = 0;
};


template<typename ElementType>
class Set
{
private:
    Array<ElementType> data;

public:
    /**
     * @brief Default desctructor.
     * 
     */
    Set(){}
    
    /**
     * @brief Copy constructor.
     * 
     * @param Other Set to copy from.
     */
    Set(const Set& Other)
    {
        data = Other.data;
    }

    /**
     * @brief Parameterized constructor. Sets defaults for set.
     * 
     * @param Capacity Default element count for which memeory is allocated.
     * @param OffsetSize Number of elements to enlarge set when lenght equals capacity.
     */
    Set(int Capacity, int OffsetSize = 1) : data(Capacity, OffsetSize){}

    /**
     * @brief Default destructor.
     * 
     */
    ~Set(){}

    /**
     * @brief Add unique element to set.
     * 
     * @param Value Element to add to.
     * @return true Element was added.
     * @return false Element wasn't added, bacause set conatains element with same value.
     */
    bool Add(const ElementType& Value)
    {
        if(data.Contains(Value))
            return false;

        data.Add(Value);
        return true;
    }

    /**
     * @brief Remove element from set.
     * 
     * @param Value Element to remove.
     */
    void Remove(const ElementType& Value)
    {
        data.Remove(Value);
    }

    bool Contains(const ElementType& Value)
    {
        return data.Contains(Value);
    }

    /**
     * @brief Get number of elements in set.
     * 
     * @return int Elements number in set.
     */
    int Length() const
    {
        return data.Length();
    }

    SetIterator<ElementType> begin() const { return SetIterator<ElementType>(data.Data(), data.Length(), 0); }
    SetIterator<ElementType> end() const { return SetIterator<ElementType>(data.Data(), data.Length(), data.Length()); }
};