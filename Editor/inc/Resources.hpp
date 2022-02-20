#pragma once

#include"Core/ISystem.hpp"
#include"Core/Sid.hpp"

#include<unordered_map>

struct SidHashFunction
{
    size_t operator()(const Hero::Sid& sid) const
    {
        return sid.id;
    }
};

class Resources : public Hero::ISystem
{
private:
    std::unordered_map<Hero::Sid, void*, SidHashFunction> bank;

public:
    Resources(const Hero::Sid& sid);
    ~Resources();

    void init();
    void update();
    void close();

    bool exists(const Hero::Sid& sid) const 
        { return (bank.find(sid) != bank.end()); }

    template<class T>
    T* get(const Hero::Sid& sid) const 
        { return (T*)bank.at(sid); }

    void add(const Hero::Sid& sid, void* resource)
        { bank.insert({sid, resource}); }
};