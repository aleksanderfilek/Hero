#ifndef HERO_MESH_H_
#define HERO_MESH_H_

typedef void* H_Mesh;

typedef enum
{
    HERO_BUFFERTYPE_SINGLE = 1,
    HERO_BUFFERTYPE_VEC2 = 2,
    HERO_BUFFERTYPE_VEC3 = 3
} HeroBufferType;

typedef struct
{
    HeroBufferType type;
    float* array;
    uint32_t length;
} HeroMeshBufferF;

typedef struct
{
    HeroBufferType type;
    uint32_t* array;
    uint32_t length;
} HeroMeshBufferI;

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif