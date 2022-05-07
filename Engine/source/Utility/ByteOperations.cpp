#include"ByteOperations.hpp"

namespace Hero
{

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

}