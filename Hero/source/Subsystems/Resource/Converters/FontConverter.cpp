#include "FontConverter.h"
#include "../../../Utility/ByteOperations.h"
#include <fstream>
#include <sstream>
#include <string>

void FontConverter::GetAcceptableExtensions(Array<String>& Extensions)
{
    Extensions.Add("ttf");
}

void FontConverter::Convert(const String& FilePath)
{
    long size;
    unsigned char* fontBuffer;

    std::ifstream file(*FilePath, std::ios_base::binary);
    file.seekg(0, std::ios::end);
    size = file.tellg();
    file.seekg(0, std::ios::beg);

    fontBuffer = new unsigned char[size]{0};
    file.read((char*)fontBuffer, size);
    file.close();

    uint32_t byteSize = 0;
    byteSize += sizeof(uint32_t);
    byteSize += size;

    int index = 0;
    uint8_t* Data = new uint8_t[byteSize];
    ByteOperations::WriteUint32(Data, &index, size);
    ByteOperations::WritePtr(Data, &index, (uint8_t*)fontBuffer, size);

	std::stringstream outputPath;
    std::string path = *FilePath;
	outputPath << path.substr(0, path.find(".") + 1);
	outputPath << "he";
	std::ofstream output(outputPath.str(), std::ios::binary);

    uint32_t resourceId = *GetName();
    output.write((char*)&resourceId, sizeof(uint32_t));
    output.write((char*)&byteSize, sizeof(uint32_t));
    output.write((char*)Data, byteSize * sizeof(uint8_t));

    output.close();

    delete[] Data;
    delete[] fontBuffer;
}