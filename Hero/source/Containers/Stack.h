#pragma once
#include "Array.h"

template<typename ElementType>
class Stack
{
private:
    Array<ElementType> data;

public:
    /**
     * @brief Default constructor, doesn't initialize memeory.
     * 
     */
    Stack(){}

    /**
     * @brief Copy constructor.
     * 
     * @param Other Stack to copy from.
     */
    Stack(const Stack& Other)
    {
        data = Other.data;
    }

    /**
     * @brief Parameterized constructor. Sets defaults for stack.
     * 
     * @param Capacity Default element count for which memeory is allocated.
     * @param OffsetSize Number of elements to enlarge stack when lenght equals capacity.
     */
    Stack(int Capacity, int OffsetSize = 1) : data(Capacity, OffsetSize){}

    /**
     * @brief Default desctructor.
     * 
     */
    ~Stack(){}

    /**
     * @brief Take from stack element and removes it.
     * 
     * @return ElementType Element on top of stack.
     */
    ElementType Pop()
    {
        int index = data.Length() - 1;
        ElementType value = data[index];
        data.RemoveAt(index);
        return value;
    }

    /**
     * @brief Puts element on top of stack.
     * 
     * @param Value Element to add on stack.
     */
    void Push(const ElementType& Value)
    {
        data.Add(Value);
    }

    /**
     * @brief Takes size of stack.
     * 
     * @return int Size of stack.
     */
    int Size() const
    {
        return data.Length();
    }

    ElementType* Top()
    {
        if(Size() == 0)
            return nullptr;
            
        return &data[Size() - 1];
    }

};