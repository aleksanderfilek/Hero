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

Texture* Font::CreateTexture(const String& Text, uint32_t Height)
{
	int width = GetTextWidth(Text, Height);

	/* create a bitmap for the phrase */
	unsigned char* bitmap = new unsigned char[width * Height] {0};

	/* calculate font scaling */
	float scale = stbtt_ScaleForPixelHeight(info, Height);

	int x = 0;

	int ascent, descent, lineGap;
	stbtt_GetFontVMetrics(info, &ascent, &descent, &lineGap);

	ascent = roundf(ascent * scale);
	descent = roundf(descent * scale);

	int i;
	for (i = 0; i < Text.Length(); ++i)
	{
		/* how wide is this character */
		int ax;
		int lsb;
		stbtt_GetCodepointHMetrics(info, Text[i], &ax, &lsb);
		/* (Note that each Codepoint call has an alternative Glyph version which caches the work required to lookup the character word[i].) */

		/* get bounding box for character (may be offset to account for chars that dip above or below the line) */
		int c_x1, c_y1, c_x2, c_y2;
		stbtt_GetCodepointBitmapBox(info, Text[i], scale, scale, &c_x1, &c_y1, &c_x2, &c_y2);

		/* compute y (different characters have different heights) */
		int y = ascent + c_y1;

		/* render character (stride and offset is important here) */
		int byteOffset = x + roundf(lsb * scale) + (y * width);
		stbtt_MakeCodepointBitmap(info, bitmap + byteOffset, c_x2 - c_x1, c_y2 - c_y1, width, scale, scale, Text[i]);

		/* advance x */
		x += roundf(ax * scale);

		/* add kerning */
		int kern;
		kern = stbtt_GetCodepointKernAdvance(info, Text[i], Text[i + 1]);
		x += roundf(kern * scale);
	}

	uint8_t* rgbaBitmap = new uint8_t[width * Height * 4];
	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int index = i * width + j;
			rgbaBitmap[index * 4 + 0] = (uint8_t)255;
			rgbaBitmap[index * 4 + 1] = (uint8_t)255;
			rgbaBitmap[index * 4 + 2] = (uint8_t)255;
			rgbaBitmap[index * 4 + 3] = (uint8_t)bitmap[index];
		}
	}

	GLuint glId = 0;
	glGenTextures(1, &glId);
	glBindTexture(GL_TEXTURE_2D, glId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgbaBitmap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	TextureConfiguration configuration;
	configuration.Size = Int2(width, Height);
	configuration.Channels = ColorChannel::RED;
	configuration.ColorSpace = ColorSpace::LINEAR;
	configuration.FilterMethod = TextureFilterMethod::LINEAR;
	configuration.WrapMethod = TextureWrapMethod::CLAMP_TO_BORDER;
	configuration.GenerateMipmaps = false;
	configuration.AtlasSize = Int2(width, Height);

	delete[] bitmap;
	delete[] rgbaBitmap;

	return new Texture(glId, configuration);
}

int Font::GetTextWidth(const String& Text, uint32_t Height) const
{
	float scale = stbtt_ScaleForPixelHeight(info, (float)(Height));
	int width = 0;

	for (int i = 0; i < Text.Length(); i++)
	{
		char c = Text[i];
		int glyphIndex = stbtt_FindGlyphIndex(info, c);
		int lsb, rsb;
		stbtt_GetGlyphHMetrics(info, glyphIndex, &lsb, &rsb);
		int advanceWidth = ceilf(lsb * scale) + ceilf(rsb * scale);

		// Apply kerning if available
		if (Text[i+1] != '\0') // Check if there is a next character
		{
			int nextGlyphIndex = stbtt_FindGlyphIndex(info, Text[i + 1]);
			int kerning = stbtt_GetGlyphKernAdvance(info, glyphIndex, nextGlyphIndex);
			advanceWidth += ceilf(kerning * scale);
		}

		width += advanceWidth;
	}
	return width;
}