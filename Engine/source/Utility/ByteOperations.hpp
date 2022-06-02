#pragma once

#include<cstdint>

namespace Hero
{

HERO void WriteUint32(uint8_t *bytes, int *currentPtr, uint32_t value);
HERO uint32_t ReadUint32(const uint8_t *bytes, int *currentPtr);
HERO void WritePtr(uint8_t *bytes, int *currentPtr, void* data, uint32_t byteSize);
HERO void ReadPtr(const uint8_t *bytes, int *currentPtr, void* dest, uint32_t byteSize);

}