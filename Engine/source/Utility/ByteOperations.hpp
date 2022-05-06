#pragma once

#include<cstdint>

namespace Hero
{

void WriteUint32(uint8_t *bytes, int *currentPtr, uint32_t value);
uint32_t ReadUint32(const uint8_t *bytes, int *currentPtr);

}