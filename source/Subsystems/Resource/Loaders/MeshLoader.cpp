#include "MeshLoader.h"
#include "../../../Resources/Mesh.h"
#include "../../../Utility/ByteOperations.h"
#include "../../../Containers/Array.h"

ResourceHandle* MeshLoader::Load(const uint8_t* Data, class ResourceSubsystem* Subsystem)
{
    int index = 0;
    Array<MeshBuffer<float>> buffers;
    MeshBuffer<int> indices;
    uint32_t indicesCount = ByteOperations::ReadUint32(Data, &index);

    int* indicesArr = new int[indicesCount];
    ByteOperations::ReadPtr(Data, &index, (uint8_t*)indicesArr, indicesCount * sizeof(int));
    indices.Length = indicesCount;
    indices.Array = indicesArr;

    uint32_t bufferCount = ByteOperations::ReadUint32(Data, &index);

    for (int i = 0; i < bufferCount; i++)
    {
        uint8_t bufferType = ByteOperations::ReadUint8(Data, &index);
        uint32_t bufferLength = ByteOperations::ReadUint32(Data, &index);
        float* bufferArr = new float[bufferLength / sizeof(float)];
        ByteOperations::ReadPtr(Data, &index, (uint8_t*)bufferArr, bufferLength);

        MeshBuffer<float> buffer = { (BufferType)bufferType, bufferArr, bufferLength / (uint32_t)sizeof(float) };
        buffers.Add(buffer);
    }

    Mesh* mesh = new Mesh(buffers, indices);

    return mesh;
}

void MeshLoader::Unload(ResourceHandle* Resource)
{
    delete Resource;
}
