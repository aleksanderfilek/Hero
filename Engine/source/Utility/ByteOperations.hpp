#pragma once

#include<cstdint>

namespace Hero
{

HERO void WriteUint8(uint8_t *bytes, int *currentPtr, uint8_t value);
HERO uint8_t ReadUint8(const uint8_t *bytes, int *currentPtr);
HERO void WriteUint16(uint8_t *bytes, int *currentPtr, uint16_t value);
HERO uint16_t ReadUint16(const uint8_t *bytes, int *currentPtr);
HERO void WriteUint32(uint8_t *bytes, int *currentPtr, uint32_t value);
HERO uint32_t ReadUint32(const uint8_t *bytes, int *currentPtr);
HERO void WriteInt(uint8_t *bytes, int *currentPtr, int value);
HERO int ReadInt(const uint8_t *bytes, int *currentPtr);
HERO void WritePtr(uint8_t *bytes, int *currentPtr, void* data, uint32_t byteSize);
HERO void ReadPtr(const uint8_t *bytes, int *currentPtr, void* dest, uint32_t byteSize);

}