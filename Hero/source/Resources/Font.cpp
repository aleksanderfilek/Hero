#include "Font.h"
#include "Texture.h"
#include "../ThirdParty/GL/Gl.h"
#include <cstring>
#define STB_TRUETYPE_IMPLEMENTATION
#include "../ThirdParty/Stb/stb_truetype.h"
#include <cmath>

Font::Font(struct stbtt_fontinfo* Info, uint8_t* Buffer)
    : info(Info), buffer(Buffer)
{

}

Font::~Font()
{
	delete[] buffer;
	delete info;
}

Texture* Font::CreateTexture(const String& Text, uint32_t Size)
{
	float fontScale = stbtt_ScaleForPixelHeight(info, (float)(Size));

	int ascent, descent, lineGap;
	stbtt_GetFontVMetrics(info, &ascent, &descent, &lineGap);

	ascent = roundf(ascent * fontScale);

	int width = 0, height = 0;
	int prevGlyph = 0;
	float dWidth = 0.0;
	for (int i = 0; i < Text.Length(); i++) 
	{
		float kern = 0;
		int glyph = 0;
		int advance, lsb;
		glyph = stbtt_FindGlyphIndex(info, Text[i]);
		if (prevGlyph && glyph) 
		{
			// If both the current and previous glyph are valid, get the kerning
			kern = stbtt_GetCodepointKernAdvance(info, prevGlyph, glyph);
		}
		else {
			kern = 0;
		}
		// Get the advance and bounding box for the current glyph
		stbtt_GetGlyphHMetrics(info, glyph, &advance, &lsb);
		// Add the advance, kerning, and horizontal offset to the width
		dWidth += (advance * fontScale + kern);
		// Move to the next character
		prevGlyph = glyph;
	}
	width = ceilf(dWidth);
	width += (width % 2 == 0) ? 0 : 1;
	height = Size;
	height += (height % 2 == 0) ? 0 : 1;
	int totalSize = width * height + 64;
	uint8_t* bitmap = new uint8_t[totalSize];
	memset(bitmap, 0, totalSize);

	int x = 0;
	int i;
	for (i = 0; i < Text.Length(); ++i)
	{
		int ax;
		int lsb;
		stbtt_GetCodepointHMetrics(info, Text[i], &ax, &lsb);

		int c_x1, c_y1, c_x2, c_y2;
		stbtt_GetCodepointBitmapBox(info, Text[i], fontScale, fontScale, &c_x1, &c_y1, &c_x2, &c_y2);

		int y = ascent + c_y1;

		int byteOffset = x + ceilf(lsb * fontScale) + (y * width);
		stbtt_MakeCodepointBitmap(info, bitmap + byteOffset, c_x2 - c_x1, c_y2 - c_y1, width, fontScale, fontScale, Text[i]);

		x += ceilf(ax * fontScale);

		int kern;
		kern = stbtt_GetCodepointKernAdvance(info, Text[i], Text[i + 1]);
		x += ceilf(kern * fontScale);
	}

	uint8_t* rgbaBitmap = new uint8_t[totalSize * 4];
	memset(rgbaBitmap, 0, totalSize * 4);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int index = i * width + j;
			rgbaBitmap[index * 4 + 0] = 255;
			rgbaBitmap[index * 4 + 1] = 255;
			rgbaBitmap[index * 4 + 2] = 255;
			rgbaBitmap[index * 4 + 3] = bitmap[index];
		}
	}
	

	GLuint glId = 0;
	glGenTextures(1, &glId);
	glBindTexture(GL_TEXTURE_2D, glId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgbaBitmap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	delete[] rgbaBitmap;
	delete[] bitmap;

	TextureConfiguration configuration;
	configuration.Size = Int2(width, height);
	configuration.Channels = ColorChannel::RGBA;
	configuration.ColorSpace = ColorSpace::LINEAR;
	configuration.FilterMethod = TextureFilterMethod::LINEAR;
	configuration.WrapMethod = TextureWrapMethod::CLAMP_TO_BORDER;
	configuration.GenerateMipmaps = false;
	configuration.AtlasSize = Int2(width, height);

	return new Texture(glId, configuration);
}