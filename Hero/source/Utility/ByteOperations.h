#pragma once

#include "../Definitions.h"
#include<cstdint>

class HERO_API ByteOperations
{
public:
    static void WriteUint8(uint8_t* Bytes, int* CurrentPos, uint8_t Value);
    static uint8_t ReadUint8(const uint8_t* Bytes, int* CurrentPos);
    static void WriteUint16(uint8_t* Bytes, int* CurrentPos, uint16_t Value);
    static uint16_t ReadUint16(const uint8_t* Bytes, int* CurrentPos);
    static void WriteUint32(uint8_t* Bytes, int* CurrentPos, uint32_t Value);
    static uint32_t ReadUint32(const uint8_t* Bytes, int* CurrentPos);
    static void WriteInt(uint8_t* Bytes, int* CurrentPos, int Value);
    static int ReadInt(const uint8_t* Bytes, int* CurrentPos);
    static void WritePtr(uint8_t* Bytes, int* CurrentPos, uint8_t* Value, uint32_t Size);
    static void ReadPtr(const uint8_t* Bytes, int* CurrentPos, uint8_t* Dest, uint32_t Size);
};