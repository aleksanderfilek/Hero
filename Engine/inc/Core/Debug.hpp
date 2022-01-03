#pragma once

#include"ThirdParty.hpp"

namespace Hero
{

extern GLenum glCheckError_(const char *file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__) 

extern GLint glShaderCheckError_(GLuint shader, GLenum pname ,const char *file, int line);
#define glShaderCheckError(shader, type) glShaderCheckError_(shader, type, __FILE__, __LINE__) 

extern GLint glProgramCheckError_(GLuint program, GLenum pname ,const char *file, int line);
#define glProgramCheckError(program, type) glProgramCheckError_(program, type, __FILE__, __LINE__) 

}