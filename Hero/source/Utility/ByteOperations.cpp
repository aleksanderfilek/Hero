#include "ByteOperations.h"
#include <cstring>

void ByteOperations::WriteUint8(uint8_t* Bytes, int* CurrentPos, uint8_t Value)
{
	Bytes[(*CurrentPos)++] = Value;
}

uint8_t ByteOperations::ReadUint8(const uint8_t* Bytes, int* CurrentPos)
{
	return Bytes[(*CurrentPos)++];
}

void ByteOperations::WriteUint16(uint8_t* Bytes, int* CurrentPos, uint16_t Value)
{
	Bytes[(*CurrentPos)++] = (0x0000ff00 & Value) >> 8;
	Bytes[(*CurrentPos)++] = (0x000000ff & Value);
}

uint16_t ByteOperations::ReadUint16(const uint8_t* Bytes, int* CurrentPos)
{
	unsigned int a = Bytes[(*CurrentPos)++];
	unsigned int b = Bytes[(*CurrentPos)++];
	return a << 8 | b;
}

void ByteOperations::WriteUint32(uint8_t* Bytes, int* CurrentPos, uint32_t Value)
{
	Bytes[(*CurrentPos)++] = (0xff000000 & Value) >> 24;
	Bytes[(*CurrentPos)++] = (0x00ff0000 & Value) >> 16;
	Bytes[(*CurrentPos)++] = (0x0000ff00 & Value) >> 8;
	Bytes[(*CurrentPos)++] = (0x000000ff & Value);
}

uint32_t ByteOperations::ReadUint32(const uint8_t* Bytes, int* CurrentPos)
{
	unsigned int a = Bytes[(*CurrentPos)++];
	unsigned int b = Bytes[(*CurrentPos)++];
	unsigned int c = Bytes[(*CurrentPos)++];
	unsigned int d = Bytes[(*CurrentPos)++];
	return a << 24 | b << 16 | c << 8 | d;
}

void ByteOperations::WriteInt(uint8_t* Bytes, int* CurrentPos, int Value)
{
	Bytes[(*CurrentPos)++] = (0xff000000 & Value) >> 24;
	Bytes[(*CurrentPos)++] = (0x00ff0000 & Value) >> 16;
	Bytes[(*CurrentPos)++] = (0x0000ff00 & Value) >> 8;
	Bytes[(*CurrentPos)++] = (0x000000ff & Value);
}

int ByteOperations::ReadInt(const uint8_t* Bytes, int* CurrentPos)
{
	int a = Bytes[(*CurrentPos)++];
	int b = Bytes[(*CurrentPos)++];
	int c = Bytes[(*CurrentPos)++];
	int d = Bytes[(*CurrentPos)++];
	return a << 24 | b << 16 | c << 8 | d;
}

void ByteOperations::WritePtr(uint8_t* Bytes, int* CurrentPos, uint8_t* Value, uint32_t Size)
{
	std::memcpy(Bytes + *CurrentPos, Value, Size);
	*CurrentPos += Size;
}

void ByteOperations::ReadPtr(const uint8_t* Bytes, int* CurrentPos, uint8_t* Dest, uint32_t Size)
{
	std::memcpy(Dest, Bytes + *CurrentPos, Size);
	*CurrentPos += Size;
}