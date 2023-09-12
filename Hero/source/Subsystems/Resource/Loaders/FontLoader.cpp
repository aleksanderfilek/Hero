#include "FontLoader.h"
#include "../../../Resources/Font.h"
#include "../../../Utility/ByteOperations.h"
#include "../../../ThirdParty/Stb/stb_truetype.h"

ResourceHandle* FontLoader::Load(const uint8_t* Data, class ResourceSubsystem* Subsystem)
{
    int index = 0;
	uint32_t size = ByteOperations::ReadUint32(Data, &index);

	uint8_t* buffer = new uint8_t[size];
	ByteOperations::ReadPtr(Data, &index, buffer, size);

    stbtt_fontinfo* info = new stbtt_fontinfo();
    stbtt_InitFont(info, buffer, 0);

	Font* font = new Font(info, buffer);
    return font;
}

void FontLoader::Unload(ResourceHandle* Resource)
{
	delete Resource;
}