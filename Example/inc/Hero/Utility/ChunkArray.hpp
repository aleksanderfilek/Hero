#pragma once

#include<cstdint>
#include<vector>
#include<utility>
#include <iterator>
#include <cstddef>

namespace Hero
{

struct ChunkArrayIndex
{
    uint32_t chunk;
    uint32_t index;
};

template<typename T>
class ChunkArray
{
private:
    struct Chunk
    {
        std::pair<bool, T>* array;
        uint32_t size = 0;
        uint32_t firstAvailable = 0;
    };

    uint32_t firstAvailable = 0;
    uint32_t chunkSize = 0;
    std::vector<Chunk> data;

    void addChunk();
public:
    ChunkArray(uint32_t _chunkSize);
    ~ChunkArray();

    ChunkArrayIndex add(const T& value);
    void remove(const ChunkArrayIndex& index);
    void clear();

    T& operator[] (const ChunkArrayIndex& index) { return data[index.chunk].array[index.index].second; }

    inline uint32_t getChunkSize() const { return chunkSize; }
    inline uint32_t getChunkCount() const { return data.size(); }

    struct Iterator 
    {
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = T*;
        using reference         = T&;

        Iterator(std::vector<Chunk>& _data, uint32_t _chunkSize, uint32_t _i, uint32_t _j) 
            : data(_data), chunkSize(_chunkSize), i(_i), j(_j) {}

        reference operator*() const { return data[i].array[j].second; }
        pointer operator->() { return &data[i].array[j].second; }

        // Prefix increment
        Iterator& operator++() 
        { 
            do{
                if(j < chunkSize)
                {
                    j++;
                }
                else
                {
                    j = 0;
                    i++;
                }
            }while(data[i].array[j].first == false && i == data.size());

            return *this;
        }  

        // Postfix increment
        Iterator operator++(int) 
        { 
            Iterator tmp(data, chunkSize, i, j); 
            
            do{
                if(j < chunkSize)
                {
                    j++;
                }
                else
                {
                    j = 0;
                    i++;
                }
            }while(data[i].array[j].first == false && i == data.size());
            
            return tmp; 
        }

        friend bool operator== (const Iterator& a, const Iterator& b) { return a.i == b.i && a.j == b.j; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.i != b.i || a.j != b.j; }; 

        private:
            std::vector<Chunk>& data;
            uint32_t chunkSize;
            uint32_t i = 0;
            uint32_t j = 0;
    };

    Iterator begin() { return Iterator(data, chunkSize, 0, 0); }
    Iterator end()   { return Iterator(data, chunkSize, data.size(), 0); }
};

template<typename T>
void ChunkArray<T>::addChunk()
{
    Chunk chunk;
    chunk.array = new std::pair<bool, T>[chunkSize];
    for(int i = 0; i < chunkSize; i++)
        chunk.array[i].first = false;

    data.push_back(chunk);
}

template<typename T>
ChunkArray<T>::ChunkArray(uint32_t _chunkSize)
:chunkSize(_chunkSize)
{
    addChunk();
}

template<typename T>
ChunkArray<T>::~ChunkArray()
{
    clear();
}

template<typename T>
ChunkArrayIndex ChunkArray<T>::add(const T& value)
{
    if(firstAvailable >= data.size())
    {
        addChunk();
    }

    Chunk& chunk = data[firstAvailable];
    chunk.array[chunk.firstAvailable] = { true, value };
    ChunkArrayIndex result = { firstAvailable, chunk.firstAvailable };

    while(chunk.array[chunk.firstAvailable++].first == true 
        && chunk.firstAvailable < chunkSize){}
    
    if(chunk.firstAvailable == chunkSize)
    {
        for(int i = firstAvailable; i < data.size(); i++)
        {
            if(data[i].firstAvailable == chunkSize)
                continue;

            firstAvailable = i;
            return result;
        }

        firstAvailable++;
    }

    return result;
}

template<typename T>
void ChunkArray<T>::clear()
{
    data.clear();
}

template<typename T>
void ChunkArray<T>::remove(const ChunkArrayIndex& index)
{
    data[index.chunk].array[index.index].first = false;
    if(index.chunk < firstAvailable)
        firstAvailable = index.chunk;
    
    if(index.index < data[index.chunk].firstAvailable)
        data[index.chunk].firstAvailable = index.index;
}

}