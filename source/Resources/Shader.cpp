#include "Shader.h"
#include "../ThirdParty/GL/Gl.h"
#include "Texture.h"

Shader::Shader(uint32_t GlId, const Map<StringId, uint32_t>& Uniforms,
        const Map<StringId, uint32_t>& Textures)
    : glId(GlId), uniforms(Uniforms), textures(Textures)
{}

Shader::~Shader()
{
    glDeleteProgram(glId);
}

void Shader::Bind()
{
    glUseProgram(glId);
    GlCheckError();
}

int Shader::GetUniformLocation(StringId Name)
{
    return (uniforms.Contains(Name)) ? -1 : uniforms[Name];
}

void Shader::SetInt(StringId Name, int Value)
{
    glUniform1i(GetUniformLocation(Name), Value);
}

void Shader::SetFloat(StringId Name, float Value)
{
    glUniform1f(GetUniformLocation(Name), Value);
}

void Shader::SetFloat3(StringId Name, const Float3& Value)
{
    glUniform3fv(GetUniformLocation(Name), 1, &Value.X);
}

void Shader::SetFloat4(StringId Name, const Float4& Value)
{
    glUniform4fv(GetUniformLocation(Name), 1, &Value.X);
}

void Shader::SetMatrix3f(StringId Name, const Matrix3x3& Value)
{
    glUniformMatrix3fv(GetUniformLocation(Name), 1, GL_FALSE, &Value.Column[0].X);
}

void Shader::SetMatrix4f(StringId Name, const Matrix4x4& Value)
{
    glUniformMatrix4fv(GetUniformLocation(Name), 1, GL_FALSE, &Value.Column[0].X);
}

void Shader::SetTexture(StringId Name, Texture* Value)
{
    Value->Bind(textures[Name]);
}