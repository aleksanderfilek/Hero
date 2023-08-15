// #include "Font.h"
// #include "../Utilities/ByteOperations.h"
// #include "Texture.h"
// #include "../ThirdParty/GL/Gl.h"
// #include <cstring>
// #define STB_TRUETYPE_IMPLEMENTATION
// #include "../ThirdParty/Stb/stb_truetype.h"
// #define STB_IMAGE_WRITE_IMPLEMENTATION
// #include "../ThirdParty/Stb/stb_image_writer.h"

// ResourceHandle* Font::load(const uint8_t* Data, ResourceSubsystem* subsystem)
// {
// 	int index = 0;
// 	uint32_t size = readUint32(Data, &index);

// 	uint8_t* buffer = new uint8_t[size];
// 	readPtr(Data, &index, buffer, size);

// 	Font* font = new Font();
// 	font->mFontInfo = new stbtt_fontinfo();
// 	stbtt_InitFont(font->mFontInfo, buffer, 0);
// 	font->buffer = buffer;
// 	return font;
// }

// void Font::unload(ResourceHandle* resource)
// {
// 	Font* font = (Font*)resource;
// 	delete[] font->buffer;
// 	delete font->mFontInfo;
// 	delete font;
// }

// Texture* Font::createTexture(const char* text, uint32_t size)
// {
// 	float fontScale = stbtt_ScaleForPixelHeight(mFontInfo, (float)(size));

// 	int ascent, descent, lineGap;
// 	stbtt_GetFontVMetrics(mFontInfo, &ascent, &descent, &lineGap);

// 	ascent = roundf(ascent * fontScale);

// 	int width = 0, height = 0;
// 	int prevGlyph = 0;
// 	float dWidth = 0.0;
// 	for (int i = 0; i < strlen(text); i++) 
// 	{
// 		float kern = 0;
// 		int glyph = 0;
// 		int advance, lsb;
// 		glyph = stbtt_FindGlyphIndex(mFontInfo, text[i]);
// 		if (prevGlyph && glyph) 
// 		{
// 			// If both the current and previous glyph are valid, get the kerning
// 			kern = stbtt_GetCodepointKernAdvance(mFontInfo, prevGlyph, glyph);
// 		}
// 		else {
// 			kern = 0;
// 		}
// 		// Get the advance and bounding box for the current glyph
// 		stbtt_GetGlyphHMetrics(mFontInfo, glyph, &advance, &lsb);
// 		// Add the advance, kerning, and horizontal offset to the width
// 		dWidth += (advance * fontScale + kern);
// 		// Move to the next character
// 		prevGlyph = glyph;
// 	}
// 	width = ceilf(dWidth);
// 	width += (width % 2 == 0) ? 0 : 1;
// 	height = size;
// 	height += (height % 2 == 0) ? 0 : 1;
// 	int totalSize = width * height + 64;
// 	uint8_t* bitmap = new uint8_t[totalSize];
// 	memset(bitmap, 0, totalSize);

// 	int x = 0;
// 	int i;
// 	for (i = 0; i < strlen(text); ++i)
// 	{
// 		int ax;
// 		int lsb;
// 		stbtt_GetCodepointHMetrics(mFontInfo, text[i], &ax, &lsb);

// 		int c_x1, c_y1, c_x2, c_y2;
// 		stbtt_GetCodepointBitmapBox(mFontInfo, text[i], fontScale, fontScale, &c_x1, &c_y1, &c_x2, &c_y2);

// 		int y = ascent + c_y1;

// 		int byteOffset = x + ceilf(lsb * fontScale) + (y * width);
// 		stbtt_MakeCodepointBitmap(mFontInfo, bitmap + byteOffset, c_x2 - c_x1, c_y2 - c_y1, width, fontScale, fontScale, text[i]);

// 		x += ceilf(ax * fontScale);

// 		int kern;
// 		kern = stbtt_GetCodepointKernAdvance(mFontInfo, text[i], text[i + 1]);
// 		x += ceilf(kern * fontScale);
// 	}

// 	uint8_t* rgbaBitmap = new uint8_t[totalSize * 4];
// 	memset(rgbaBitmap, 0, totalSize * 4);
// 	for (int i = 0; i < height; i++)
// 	{
// 		for (int j = 0; j < width; j++)
// 		{
// 			int index = i * width + j;
// 			rgbaBitmap[index * 4 + 0] = 255;
// 			rgbaBitmap[index * 4 + 1] = 255;
// 			rgbaBitmap[index * 4 + 2] = 255;
// 			rgbaBitmap[index * 4 + 3] = bitmap[index];
// 		}
// 	}
	

// 	GLuint textureId = 0;
// 	glGenTextures(1, &textureId);
// 	glBindTexture(GL_TEXTURE_2D, textureId);
// 	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgbaBitmap);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// 	glBindTexture(GL_TEXTURE_2D, 0);

// 	delete[] rgbaBitmap;
// 	delete[] bitmap;

// 	Texture* texture = 
// 		new Texture(textureId, Int2(width, height), (uint8_t)TextureFlag::LINEAR, ColorChannel::RGBA, ColorSpace::LINEAR);

// 	return texture;
// }