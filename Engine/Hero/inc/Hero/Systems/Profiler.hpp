#pragma once

#include"../Core/ISystem.hpp"
#include"../Core/SID.hpp"

#include<unordered_map>
#include<cstdint>
#include<string>

namespace Hero
{
namespace System
{

class Profiler : public ISystem
{
private:
    static Profiler* instance;

    uint32_t frame = 0;
    uint32_t bufferNumber = 0;
    uint32_t bufferIndex = 0;


    HERO void SaveBuffer();
    HERO void SaveLog();

    int BufferSize;

    std::unordered_map<Sid, double*, SidHashFunction> buffers;

    HERO void TryAddBuffer(const Sid& sid);

public:
    HERO Profiler(const Sid& sid, int _BufferSize = 1024);
    HERO ~Profiler();

    HERO void init();
    HERO void update();
    HERO void close();

    HERO static uint64_t GetTime();
    HERO static void Register(const Sid& sid, double time);
};
  
}
}