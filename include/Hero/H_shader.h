#ifndef HERO_SHADER_H_
#define HERO_SHADER_H_

typedef void* HeroShader;

#ifdef __cplusplus
extern "C" {
#endif

extern HeroShader* heroShaderLoad(const char* vertexShader, const char* fragmentShader);
extern void heroShaderUnload(void* shader);
extern void heroShaderBind(const HeroShader* shader);
extern uint32_t heroShaderGetUniformLocation(const HeroShader* shader, const char* name);

#ifdef __cplusplus
}
#endif

#endif