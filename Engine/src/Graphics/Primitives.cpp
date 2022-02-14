#include"Primitives.hpp"
#include"Mesh.hpp"

namespace Hero
{
namespace Primitives
{

Mesh* cube(float size)
{
    MeshBuffer<float> positions;
    std::vector<MeshBuffer<float>> buffers;
    buffers.push_back(positions);
    MeshBuffer<int> indicies;
    Mesh* mesh = new Mesh("cube", buffers, indicies);
    return mesh;
}

}
}