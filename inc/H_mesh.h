#ifndef HERO_MESH_H_
#define HERO_MESH_H_

typedef void* H_Mesh;

typedef enum
{
    HEROBUFFERTYPE_SINGLE = 1,
    HEROBUFFERTYPE_VEC2 = 2,
    HEROBUFFERTYPE_VEC3 = 3
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