#pragma once

#include "Array.h"

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

    /**
     * @brief Get number of elements in set.
     * 
     * @return int Elements number in set.
     */
    int Length() const
    {
        return data.Length();
    }
};