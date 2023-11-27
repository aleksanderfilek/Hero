#include"Profiler.hpp"
#include"../Core/Time.hpp"
#include"../ThirdParty/SDL2/SDL.h"

#include<sstream>
#include<cstring>
#include<fstream>
#include<iostream>

namespace Hero
{
namespace System
{

Profiler* Profiler::instance = nullptr;

HERO Profiler::Profiler(const Sid& sid, int _BufferSize) 
    : ISystem(sid), BufferSize(_BufferSize)
{
    Profiler::instance = this;
}

HERO Profiler::~Profiler()
{

}

HERO void Profiler::init()
{
    ISystem::init();

    TryAddBuffer(SID("FPS"));
}

HERO void Profiler::update()
{
    buffers[SID("FPS")][bufferIndex] = 1.0/Hero::Time::getDeltaTime();

    frame++;
    bufferIndex++;

    if(bufferIndex == BufferSize)
    {
        SaveBuffer();
    }
}

HERO void Profiler::close()
{
    ISystem::close();

    SaveLog();

    for(auto buffer: buffers)
    {
        delete[] buffer.second;
    }
}

HERO void Profiler::SaveBuffer()
{

    std::string name = std::to_string(bufferNumber) + "profiler.temp";

    std::ofstream file;
    file.open(name, std::ios::binary);
    if(!file.is_open())
    {
        printMessage("Could not create buffer file: "+name);
        return;
    }


    uint32_t size = buffers.size();
    file.write((char*)&size, sizeof(uint32_t));


    for(auto buffer: buffers)
    {
        std::stringstream name;
        name<<buffer.first;
        

        uint32_t length = name.str().length();

        file.write((char*)&length, sizeof(uint32_t));

        file.write((char*)name.str().c_str(), length * sizeof(char));

        file.write((char*)buffer.second, BufferSize * sizeof(double));


        std::memset(buffer.second, 0, BufferSize * sizeof(double));

    }


    file.close();


    bufferNumber++;
    bufferIndex = 0;
}

HERO void Profiler::SaveLog(){
    std::ofstream file;
    file.open("profiler.csv");

    if(file.fail())
    {
        printMessage("Could not create profiler file");
        return;
    }

    file<<"Frame,";
    for(auto buffer: buffers)
    {
        file<<buffer.first;
        file<<",";
    }
    file<<std::endl;

    std::unordered_map<Sid, double*, SidHashFunction> tempBuffers;

    for(auto buffer: buffers)
    {
        double* buff = new double[BufferSize]{0.0};
        tempBuffers.insert({buffer.first, buff});
    }

    int frameCounter = 0;

    for(int i = 0; i < bufferNumber; i++)
    {
        std::string name = std::to_string(i) + "profiler.temp";
        std::ifstream tempFile;
        tempFile.open(name, std::ios::in | std::ios::binary);

        uint32_t count = 0; 
        tempFile.read((char*)&count, sizeof(uint32_t));

        for(int i = 0; i < count; i++)
        {
            uint32_t nameLength;
            tempFile.read((char*)&nameLength, sizeof(uint32_t));

            char* name = new char[nameLength+1];
            tempFile.read((char*)name, nameLength * sizeof(char));
            name[nameLength] = '\0';

            Sid sid = SID(name);

            tempFile.read((char*)tempBuffers[sid], BufferSize * sizeof(double));

            delete[] name;
        }

        tempFile.close();

        for(int i = 0; i < BufferSize; i++)
        {
            file<<frameCounter++<<",";
            for(auto buffer: buffers)
            {
                file<<tempBuffers[buffer.first][i]<<",";
            }
            file<<std::endl;
        }
    }

    for(int i = 0; i < bufferIndex; i++)
    {
        file<<frameCounter++<<",";
        for(auto buffer: buffers)
        {
            file<<buffer.second[i]<<",";
        }
        file<<std::endl;
    }

    file.close();
    
    for(auto buffer: tempBuffers)
    {
        delete[] buffer.second;
    }
}

HERO void Profiler::TryAddBuffer(const Sid& sid)
{
    auto search = buffers.find(sid);

    if(search != buffers.end())
        return;

    double* buffer = new double[BufferSize]{0.0};
    buffers.insert({sid, buffer});
}

HERO uint64_t Profiler::GetTime()
{
    return SDL_GetPerformanceCounter();
}

HERO void Profiler::Register(const Sid& sid, double elasedTime)
{
    instance->TryAddBuffer(sid);
    
    instance->buffers[sid][instance->bufferIndex] += 
        elasedTime / (double)SDL_GetPerformanceFrequency();
}

}
}