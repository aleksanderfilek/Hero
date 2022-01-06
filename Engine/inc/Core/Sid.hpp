#pragma once

#include<iostream>
#include<string>
#include<cstdint>
#include<cstring>

namespace Hero
{

struct Sid
{
    uint32_t id = 0;
    #ifdef HERO_DEBUG
    const char* text = "None";
    #endif

    public:
        #ifdef HERO_DEBUG
        constexpr Sid() {}
        #else
        constexpr Sid():id(0) {}
        #endif

        inline std::string getName() const
        {
            #ifdef HERO_DEBUG
            return std::string(text);
            #else
            std::cout<<"[SID] - getName function can only be used in Hero Debug Mode!"<<std::endl;
            return std::to_string(id);
            #endif
        }

        inline bool operator== (const Sid &rhs) const
        {
            return id == rhs.id;
        }

        static constexpr Sid create(const char* text)
        {
            const size_t length = std::strlen(text) + 1;
            unsigned int hash = 2166136261u;
            const char* lText = text;
            for (size_t i=0; i<length; ++i)
            {
                hash ^= *lText++;
                hash *= 16777619u;
            }

            Sid sid;
            sid.id = hash;

            #ifdef HERO_DEBUG
            sid.text = text;
            #endif

            return sid;
        }
};

#define SID(name) Hero::Sid::create(name)

}