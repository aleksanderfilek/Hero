#pragma once

#include<cstdint>

namespace Hero
{

class Shader
{   
private:
    const char* name;
    uint32_t glId;
    bool isBinded = false;
public:
    Shader(const char* _name);
    ~Shader();

    void bind();
    uint32_t getUniformLocation(const char* _name);

};

}