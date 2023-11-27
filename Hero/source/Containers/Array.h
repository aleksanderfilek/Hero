#pragma once

#include <cstring>
#include <iterator>
#include <algorithm>
#include <cstdlib>

template<typename ElementType> struct ArrayIterator
{
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = ElementType;
    using pointer = ElementType*;
    using reference = ElementType&;

private:
    pointer data;
    int length = 0;
    int index = 0;

public:

    ArrayIterator(ElementType* Data, int Length, int Index) 
        : data(Data), length(Length), index(Index) {}

    reference operator*() const { return data[index]; }
    pointer operator->() { return &data[index]; }

    // Prefix increment.
    ArrayIterator& operator++() 
    { 
        index++;
        return *this;
    }  

    // Postfix increment.
    ArrayIterator operator++(int) 
    { 
        ArrayIterator tmp(data, length, index); 
        index++;
        return tmp; 
    }

    friend bool operator== (const ArrayIterator& a, const ArrayIterator& b) { return a.index == b.index; }
    friend bool operator!= (const ArrayIterator& a, const ArrayIterator& b) { return a.index != b.index; }

    ArrayIterator operator-(int Value)
    {
        ArrayIterator tmp = *this;
        tmp.index - 1;
        return tmp;
    }

};

template<typename ElementType>
class Array
{
private:
    int capacity = 0;
    int length = 0;
    int offsetSize = 1;

    ElementType* data = nullptr;

public:
    /**
     * @brief Default constructor with not initialized memory.
     */
    Array(){}

    /**
     * @brief Parameterized constructor.
     * 
     * @param Capacity The number of the array elements.
     * @param OffsetSize The number of elements to be added when length equals capacity.
     */
    Array(int Capacity, int OffsetSize = 1) : capacity(Capacity), offsetSize(OffsetSize)
    {
        data = (ElementType*)calloc(Capacity, sizeof(ElementType));
    }

    /**
     * @brief Constructor copying one array to another.
     * 
     * @param Other The array to copy from.
     */
    Array(const Array& Other)
    {
        if(data)
        {
            free(data);
        }

        length = Other.length;
        capacity = Other.length;

        data = (ElementType*)malloc(capacity * sizeof(ElementType));
        std::memcpy(data, Other.data, capacity * sizeof(ElementType));
    }

    /**
     * @brief Constructor copying simple array elements.
     * 
     * @param Data The array to copy from.
     * @param Length The lengh of the array.
     */
    Array(ElementType* Data, int Length)
    {
        if(data)
        {
            free(data);
        }

        length = Length;
        capacity = Length;

        data = (ElementType*)malloc(capacity * sizeof(ElementType));
        std::memcpy(data, Data, length * sizeof(ElementType));
    }

    /**
     * @brief Destructor
     * 
     */
    ~Array()
    {
        free(data);
    }

    ArrayIterator<ElementType> begin() const { return ArrayIterator<ElementType>(data, length, 0); }
    ArrayIterator<ElementType> end() const { return ArrayIterator<ElementType>(data, length, length); }

    /**
     * @brief Function adding new elment to array. If lenght equals capacity, allocated array is enlarged by offset size.
     * 
     * @param Value Element to be added to array.
     * @return int Index of added element;
     */
    int Add(const ElementType& Value)
    {
        if(length == capacity)
        {
            ElementType* oldData = data;
            capacity += offsetSize;
            data = (ElementType*)malloc(capacity * sizeof(ElementType));

            if (oldData)
            {
                std::memcpy(data, oldData, length * sizeof(ElementType));
                free(oldData);
            }
        }

        int index = length;
        data[index] = Value;
        length++;
        return index;
    }

    /**
     * @brief The function tries to delete an element from array by iterating through all elements. The array capacity is not changed.
     * 
     * @param Value The element to be removed.
     * @return true The element was found and removed.
     * @return false The elmeent wasn't find.
     */
    bool Remove(const ElementType& Value)
    {
        for(int i = 0; i < length; i++)
        {
            if(data[i] != Value)
            {
                continue;
            }

            int elementsNumberToMove = length - i - 1;
            std::memcpy(data + i, data + i + 1, elementsNumberToMove * sizeof(ElementType));
            length--;
            return true;
        }

        return false;
    }

    /**
     * @brief The function tries to delete an element from array on index. The array capacity is not changed.
     * 
     * @param Index The index of element to be deleted.
     * @return true The element was removed.
     * @return false The element wasn't removed, index exceeds range <0, length).
     */
    bool RemoveAt(int Index)
    {
        if(Index < 0 || Index >= length)
        {
            return false;
        }

        int elementsNumberToMove = length - Index - 1;
        std::memcpy(data + Index, data + Index + 1, elementsNumberToMove * sizeof(ElementType));
        length--;
        return true;
    }

    /**
     * @brief Checks if element is in array.
     * 
     * @param Value Element to look for.
     * @param Index Pointer to index with index of found element.
     * @return true Array contains element.
     * @return false Array doesn't contain element.
     */
    bool Contains(const ElementType& Value, int* Index = nullptr)
    {
        for(int i = 0; i < length; i++)
        {
            if(data[i] != Value)
            {
                continue;
            }

            if(Index)
                *Index = i;

            return true;
        }

        return false;
    }

    /**
     * @brief Sets array memory and lenght to 0. 
     * 
     */
    void Clear()
    {
        if(length == 0)
            return;

        std::memset(data, 0, length * sizeof(ElementType));
        length = 0;
    }

    void Reset()
    {
        free(data);
        length = 0;
        capacity = 0;
    }

    /**
     * @brief Gets array length.
     * 
     * @return int Array lenght.
     */
    int Length() const
    {
        return length;
    }

    /**
     * @brief Gets capacity.
     * 
     * @return int Array capacity.
     */
    int Capacity() const
    {
        return capacity;
    }

    /**
     * @brief Set the Offset Size
     * 
     * @param OffsetSize Number of elements to enlarge array memory when length equals capacity.
     */
    void SetOffsetSize(int OffsetSize)
    {
        offsetSize = OffsetSize;
    }

    /**
     * @brief Gets offset size.
     * 
     * @return int Offset size.
     */
    int OffsetSize() const
    {
        return offsetSize;
    }

    /**
     * @brief Get reference to array element.
     * 
     * @param Index Index of element to get.
     * @return ElementType& Reference to element.
     */
    ElementType& operator[](int Index) const
    {
        return data[Index];
    }

    ElementType* Data() const { return data; }
};