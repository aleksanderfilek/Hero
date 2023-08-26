#include "UniformBlock.h"
#include "../ThirdParty/GL/Gl.h"

void UniformBlock::Apply(uint32_t Id)
{
	id = Id;

	glGenBuffers(1, &ubo);
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferRange(GL_UNIFORM_BUFFER, id, ubo, 0, size);
}

void UniformBlock::BindValue(uint32_t Offset, uint32_t Size, void* ValuePtr)
{
    glBindBuffer(GL_UNIFORM_BUFFER, ubo);
    glBufferSubData(GL_UNIFORM_BUFFER, Offset, Size, ValuePtr);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}