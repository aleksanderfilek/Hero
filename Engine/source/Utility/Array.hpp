#pragma once

#include<cstdint>
#include<cstring>

namespace Hero
{

template<typename T>
class Array
{
private:
    uint32_t capacity = 0;
    uint32_t size = 0;
    uint32_t chunk = 0;

    T* data = nullptr;

public:
    Array(uint32_t _startSize = 1, uint32_t _chunkSize = 1);
    ~Array();

    void add(const T& value);
    void remove(uint32_t index);
    void clear();
    void resize(uint32_t newSize);

    T& operator[] (uint32_t index) { return data[index]; }

    inline uint32_t getSize() const { return size; }
    inline uint32_t getCapacity() const { return capacity; }
};

template<typename T>
Array<T>::Array(uint32_t _startSize, uint32_t _chunkSize)
    :chunkSize(_chunkSize)
{
    if(_startSize < 1) 
        _startSize = 1;
    data = new T[_startSIze];
    capacity = _startSize;
}

template<typename T>
Array<T>::~Array()
{
    clear();
}

template<typename T>
void Array<T>::add(const T& value)
{
    data[size] = value;

    size++;
    if(size >= capacity)
    {
        T* old = data;
        capcity += chunk;
        data = new T[capacity];
        std::memcpy(data, old, (size-1)*sizeof(T));
        delete[] old;
    }
}

template<typename T>
void Array<T>::remove(uint32_t index)
{
    if(index >= size) 
        return;

    std::memmove(data+index, data+index+1, (size - index)*sizeof(T));
}

template<typename T>
void Array<T>::clear()
{
    delete[] data;
    data = nullptr;
    capacity = 0;
    size = 0;
}

template<typename T>
void Array<T>::resize(uint32_t newSize)
{

}

}
