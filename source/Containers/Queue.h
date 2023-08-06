#pragma once

template<typename ElementType>
class Queue
{
private:
    ElementType* data = nullptr;
    int length = 0;
    int capacity = 0;
    int offsetSize = 1;

    int headIndex = -1;
    int tailIndex = -1;

public:
    Queue(){}

    Queue(const Queue& Other)
    {
        if(data)
        {
            delete[] data;
        }

        length = Other.length;
        capacity = Other.length;

        data = new ElementType[capacity];
        std::memcpy(data, Other.data, length * sizeof(ElementType));
        headIndex = Other.headIndex;
        tailIndex = Other.tailIndex;
    }

    Queue(int Capacity, int OffsetSize = 1) : capacity(Capacity), offsetSize(OffsetSize)
    {
        data = new ElementType[Capacity];
        std::memset(data, 0, capacity * sizeof(ElementType));
    }

    ~Queue()
    {
        delete[] data;
    }

    void Enqueue(const ElementType& Value)
    {
        if(headIndex == 0 && tailIndex == capacity - 1 || capacity == 0)
        {
            int oldCapacity = capacity;
            ElementType* oldData = data;
            capacity += offsetSize;
            data = new ElementType[capacity];
            std::memcpy(data, oldData, oldCapacity * sizeof(ElementType));
            delete[] oldData;
        }

        if(headIndex == -1)
            headIndex = 0;

        tailIndex++;
        length++;
        data[tailIndex] = Value;
    }

    bool Dequeue(ElementType& Element)
    {
        if(length == 0)
        {
            return false;
        }

        Element = data[headIndex];
        length--;
        if(headIndex >= tailIndex)
        {
            headIndex = -1;
            tailIndex = -1;
        }
        else
        {
            headIndex++;
        }

        return true;
    }

    int Length() const
    {
        return length;
    }

};