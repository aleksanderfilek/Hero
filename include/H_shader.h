#ifndef HERO_SHADER_H_
#define HERO_SHADER_H_

typedef void* HeroShader;

#ifdef __cplusplus
extern "C" {
#endif

extern HeroShader* heroShaderLoad(const char* vertexShader, const char* fragmentShader);
extern void heroShaderUnload(HeroShader* shader);
extern void heroShaderBind(const HeroShader* shader);

#ifdef __cplusplus
}
#endif

#endif