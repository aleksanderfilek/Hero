// #include "Shader.h"

// #include "../Utilities/ByteOperations.h"
// #include "../ThirdParty/GL/Gl.h"
// #include "../Core/Debug.h"
// #include "Texture.h"

// #include<iostream>
// #include<cstdlib>

// #include <vector>
// #include <string>

// Shader::Shader()
// {}

// ResourceHandle* Shader::load(const uint8_t* Data, ResourceSubsystem* subsystem)
// {
//     int index = 0;
//     uint32_t program = glCreateProgram();

//     uint32_t uniformNumber = 0;
//     uint32_t textureUniformNumber = 0;

//     uint16_t flags = 0;
//     uint32_t size = 0;
//     char* content = 0;
//     uint32_t typeArr[5] = { GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER,
//         GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER, GL_FRAGMENT_SHADER };
//     uint32_t shaders[5];

//     std::vector<std::string> uniformVec;
//     uniformNumber = readUint32(Data, &index);
//     for (int i = 0; i < uniformNumber; i++)
//     {
//         size = readUint32(Data, &index);

//         content = new char[size + 1];
//         content[size] = '\0';
//         readPtr(Data, &index, (uint8_t*)content, size);

//         std::string uniform(content);
//         uniformVec.push_back(uniform);

//         delete[] content;
//     }

//     std::vector<std::string> textureUniformVec;
//     textureUniformNumber = readUint32(Data, &index);
//     for (int i = 0; i < textureUniformNumber; i++)
//     {
//         size = readUint32(Data, &index);

//         content = new char[size + 1];
//         content[size] = '\0';
//         readPtr(Data, &index, (uint8_t*)content, size);

//         std::string uniform(content);
//         textureUniformVec.push_back(uniform);

//         delete[] content;
//     }

//     flags = readUint16(Data, &index);
//     for (int i = 0; i < 5; i++)
//     {
//         if (!(flags & 1 << i))
//         {
//             continue;
//         }

//         size = readUint32(Data, &index);
//         content = new char[size + 1];
//         content[size] = '\0';
//         readPtr(Data, &index, (uint8_t*)content, size);

//         shaders[i] = glCreateShader(typeArr[i]);
//         glShaderSource(shaders[i], 1, (const char**)&content, nullptr);
//         glCompileShader(shaders[i]);
//         glShaderCheckError(shaders[i], GL_COMPILE_STATUS);

//         glAttachShader(program, shaders[i]);
//         glProgramCheckError(program, GL_ATTACHED_SHADERS);


//         delete[] content;
//         content = nullptr;
//     }

//     glLinkProgram(program);
//     int  success;
//     glGetProgramiv(program, GL_LINK_STATUS, &success);
//     glProgramCheckError(program, GL_LINK_STATUS);
//     if (success == GL_FALSE)
//     {
//         exit(-1);
//     }

//     glValidateProgram(program);
//     glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
//     if (success == GL_FALSE)
//     {
//         std::cout << "Program is not valid!\n" << std::endl;
//         exit(-1);
//     }

//     for (int i = 0; i < 5; i++)
//     {
//         if (!(flags & 1 << i))
//         {
//             continue;
//         }

//         glDeleteShader(shaders[i]);
//         glShaderCheckError(shaders[i], GL_DELETE_STATUS);
//     }

//     glUseProgram(program);
//     std::map<StringId, uint32_t> uniforms;
//     for (auto uniform : uniformVec)
//     {
//         uint32_t loc = glGetUniformLocation(program, uniform.c_str());
//         uniforms.insert(std::pair<StringId, uint32_t>(sid(uniform.c_str()), loc));
//     }

//     Shader* shader = new Shader();
//     shader->mGlId = program;
//     shader->mUniforms = uniforms;

//     uint32_t textureCounter = 0;
//     for (auto uniform : textureUniformVec)
//     {
//         shader->mTextures.insert(std::pair<StringId, uint32_t>(sid(uniform.c_str()), textureCounter));
//         textureCounter++;
//     }

//     return shader;
// }

// Shader::~Shader()
// {
//     glDeleteProgram(mGlId);
// }

// void Shader::unload(ResourceHandle* resource)
// {
//     delete resource;
// }

// void Shader::bind()
// {
//     glUseProgram(mGlId);
//     glCheckError();
//     isBinded = true;
// }

// int Shader::getUniformLocation(StringId name)
// {
//     return (mUniforms.find(name) == mUniforms.end()) ? -1 : mUniforms[name];
// }

// void Shader::setInt(StringId name, int value)
// {
//     glUniform1i(getUniformLocation(name), value);
// }

// void Shader::setFloat(StringId name, float value)
// {
//     glUniform1f(getUniformLocation(name), value);
// }

// void Shader::setFloat3(StringId name, const Float3& value)
// {
//     glUniform3fv(getUniformLocation(name), 1, &value.x);
// }

// void Shader::setFloat4(StringId name, const Float4& value)
// {
//     glUniform4fv(getUniformLocation(name), 1, &value.x);
// }

// void Shader::setMatrix3f(StringId name, const Matrix3x3& value)
// {
//     glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, &value.col[0].x);
// }

// void Shader::setMatrix4f(StringId name, const Matrix4x4& value)
// {
//     glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &value.col[0].x);
// }

// void Shader::setTexture(StringId name, Texture* value)
// {
//     value->bind(mTextures[name]);
// }