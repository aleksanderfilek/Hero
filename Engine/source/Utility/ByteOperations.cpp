#include"ByteOperations.hpp"
#include"cstring"

namespace Hero
{

HERO void WriteUint8(uint8_t *bytes, int *currentPtr, uint8_t value)
{
	bytes[(*currentPtr)++] = value;
}

HERO uint8_t ReadUint8(const uint8_t *bytes, int *currentPtr)
{
	return bytes[(*currentPtr)++];
}

HERO void WriteUint16(uint8_t *bytes, int *currentPtr, uint16_t value)
{
	bytes[(*currentPtr)++] = (0x0000ff00 & value) >> 8;
	bytes[(*currentPtr)++] = (0x000000ff & value);
}

HERO uint16_t ReadUint16(const uint8_t *bytes, int *currentPtr)
{
	unsigned int a = bytes[(*currentPtr)++];
	unsigned int b = bytes[(*currentPtr)++];
	return a << 8 | b;
}

HERO void WriteUint32(uint8_t *bytes, int *currentPtr, uint32_t value)
{
	bytes[(*currentPtr)++] = (0xff000000 & value) >> 24;
	bytes[(*currentPtr)++] = (0x00ff0000 & value) >> 16;
	bytes[(*currentPtr)++] = (0x0000ff00 & value) >> 8;
	bytes[(*currentPtr)++] = (0x000000ff & value);
}

HERO uint32_t ReadUint32(const uint8_t *bytes, int *currentPtr)
{
	unsigned int a = bytes[(*currentPtr)++];
	unsigned int b = bytes[(*currentPtr)++];
	unsigned int c = bytes[(*currentPtr)++];
	unsigned int d = bytes[(*currentPtr)++];
	return a << 24 | b << 16 | c << 8 | d;
}

HERO void WriteInt(uint8_t *bytes, int *currentPtr, int value)
{
	bytes[(*currentPtr)++] = (0xff000000 & value) >> 24;
	bytes[(*currentPtr)++] = (0x00ff0000 & value) >> 16;
	bytes[(*currentPtr)++] = (0x0000ff00 & value) >> 8;
	bytes[(*currentPtr)++] = (0x000000ff & value);
}

HERO int ReadInt(const uint8_t *bytes, int *currentPtr)
{
	int a = bytes[(*currentPtr)++];
	int b = bytes[(*currentPtr)++];
	int c = bytes[(*currentPtr)++];
	int d = bytes[(*currentPtr)++];
	return a << 24 | b << 16 | c << 8 | d;
}

HERO void WritePtr(uint8_t *bytes, int *currentPtr, uint8_t* data, uint32_t byteSize)
{
	std::memcpy(bytes + *currentPtr, data, byteSize);
	*currentPtr += byteSize;
}

HERO void ReadPtr(const uint8_t *bytes, int *currentPtr, uint8_t* dest, uint32_t byteSize)
{
	std::memcpy(dest, bytes + *currentPtr, byteSize);
	*currentPtr += byteSize;
}

}