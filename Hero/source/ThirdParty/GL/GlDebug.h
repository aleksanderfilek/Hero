#pragma once

#include "../../Definitions.h"
#include <cstdint>

class HERO_API GlDebbug
{
public:
    static uint32_t _InternalGlCheckError(const char* File, int Line);
    static int _InternalGlShaderCheckError(uint32_t Shader, uint32_t Pname, const char* File, int Line);
    static int _InternalGlProgramCheckError(uint32_t Program, uint32_t Pname, const char* File, int Line);
};

#define GlCheckError() GlDebbug::_InternalGlCheckError(__FILE__, __LINE__)
#define GlShaderCheckError(shader, type) GlDebbug::_InternalGlShaderCheckError(shader, type, __FILE__, __LINE__) 
#define GlProgramCheckError(program, type) GlDebbug::_InternalGlProgramCheckError(program, type, __FILE__, __LINE__) 
