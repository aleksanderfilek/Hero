#include "TextureConverter.h"
#include "../../../Resources/Texture.h"
#include "../../../GenericTypes/StringId.h"
#include "../../../Utility/QOI.h"
#include "../../../Utility/ByteOperations.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../../../ThirdParty/Stb/stb_image.h"
#include <fstream>
#include <sstream>
#include <string>

void TextureConverter::GetAcceptableExtensions(Array<String>& Extensions)
{
    Extensions.SetOffsetSize(5);
    Extensions.Add("png");
    Extensions.Add("jpeg");
    Extensions.Add("jpg");
    Extensions.Add("bmp");
    Extensions.Add("tga");
}

void TextureConverter::Convert(const String& FilePath)
{
    int width, height, nrChannels;
	uint32_t dataLength = 0;
	uint8_t* data = stbi_load(*FilePath, &width, &height, &nrChannels, 0);
	uint8_t* encoded = QOI::Encode(data, (uint32_t)width, (uint32_t)height, (uint8_t)nrChannels, dataLength);

	stbi_image_free(data);

	uint8_t channels = (uint8_t)nrChannels;
	uint8_t colorSpace = (uint8_t)ColorSpace::LINEAR;
	uint8_t filter = (uint8_t)TextureFilterMethod::NEAREST;
    uint8_t wrap = (uint8_t)TextureWrapMethod::CLAMP_TO_BORDER;
    uint8_t generateMipmap = false;

	uint32_t byteSize = 0;
	byteSize += sizeof(uint32_t);
	byteSize += sizeof(uint32_t);
	byteSize += sizeof(uint8_t);
	byteSize += sizeof(uint8_t);
	byteSize += sizeof(uint8_t);
	byteSize += sizeof(uint8_t);
	byteSize += sizeof(uint8_t);
	byteSize += sizeof(uint32_t);
	byteSize += sizeof(uint32_t);
	byteSize += sizeof(uint32_t);
	byteSize += dataLength * sizeof(uint8_t);

	uint8_t* Data = new uint8_t[byteSize];
	int index = 0;
	ByteOperations::WriteUint32(Data, &index, (uint32_t)width);
	ByteOperations::WriteUint32(Data, &index, (uint32_t)height);
	ByteOperations::WriteUint8(Data, &index, channels);
	ByteOperations::WriteUint8(Data, &index, colorSpace);
	ByteOperations::WriteUint8(Data, &index, filter);
    ByteOperations::WriteUint8(Data, &index, wrap);
	ByteOperations::WriteUint8(Data, &index, generateMipmap);
	ByteOperations::WriteUint32(Data, &index, (uint32_t)width);
	ByteOperations::WriteUint32(Data, &index, (uint32_t)height);
	ByteOperations::WriteUint32(Data, &index, dataLength);
	ByteOperations::WritePtr(Data, &index, encoded, dataLength * sizeof(uint8_t));

	delete[] encoded;

	std::stringstream outputPath;
    std::string path = *FilePath;
	outputPath << path.substr(0, path.find(".") + 1);
	outputPath << "he";
	std::ofstream output(outputPath.str(), std::ios::binary);

	uint32_t ResourceId = *GetName();
	output.write((char*)&ResourceId, sizeof(uint32_t));
	output.write((char*)&byteSize, sizeof(uint32_t));
	output.write((char*)Data, byteSize * sizeof(uint8_t));

	output.close();

	delete[] Data;
}