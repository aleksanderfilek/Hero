#include"QOI.h"
#include"ByteOperations.h"

#include<iostream>

/*
Encoder and decoder code was copies from https://github.com/phoboslab/qoi/blob/master/qoi.h repository.
*/

#include<cstring>

#define QOI_OP_INDEX  0x00 /* 00xxxxxx */
#define QOI_OP_DIFF   0x40 /* 01xxxxxx */
#define QOI_OP_LUMA   0x80 /* 10xxxxxx */
#define QOI_OP_RUN    0xc0 /* 11xxxxxx */
#define QOI_OP_RGB    0xfe /* 11111110 */
#define QOI_OP_RGBA   0xff /* 11111111 */

#define QOI_MASK_2    0xc0 /* 11000000 */

#define QOI_COLOR_HASH(C) (C.rgba.r*3 + C.rgba.g*5 + C.rgba.b*7 + C.rgba.a*11)
#define QOI_MAGIC \
	(((unsigned int)'q') << 24 | ((unsigned int)'o') << 16 | \
	 ((unsigned int)'i') <<  8 | ((unsigned int)'f'))
#define QOI_HEADER_SIZE 4 // Only QOI_MAGIC

		/* 2GB is the max file size that this implementation can safely handle. We guard
		against anything larger than that, assuming the worst case with 5 bytes per
		pixel, rounded down to a nice clean value. 400 million pixels ought to be
		enough for anybody. */
#define QOI_PIXELS_MAX ((unsigned int)400000000)

typedef union {
	struct { uint8_t r, g, b, a; } rgba;
	unsigned int v;
} qoi_rgba_t;

static const unsigned char qoi_padding[8] = { 0,0,0,0,0,0,0,1 };

uint8_t* QOI::Encode(uint8_t* Data, uint32_t Width, uint32_t Height, uint8_t Channels, uint32_t& ByteLength)
{
    int i, max_size, p, run;
    int px_len, px_end, px_pos, channels;
    uint8_t* bytes;
    const uint8_t* pixels;
    qoi_rgba_t index[64];
    qoi_rgba_t px, px_prev;

    if (Data == nullptr ||
        Width == 0 || Height == 0 ||
        Height >= QOI_PIXELS_MAX / Width)
    {
        return nullptr;
    }

    max_size =
        Width * Height * ((uint8_t)Channels + 1) +
        QOI_HEADER_SIZE + sizeof(qoi_padding);

    p = 0;
    bytes = new uint8_t[max_size];
    if (!bytes) {
        return NULL;
    }

    ByteOperations::WriteUint32(bytes, &p, QOI_MAGIC);

    pixels = (const uint8_t*)Data;

    std::memset(index, 0, sizeof(index));

    run = 0;
    px_prev.rgba.r = 0;
    px_prev.rgba.g = 0;
    px_prev.rgba.b = 0;
    px_prev.rgba.a = 255;
    px = px_prev;

    px_len = Width * Height * (uint8_t)Channels;
    px_end = px_len - (uint8_t)Channels;
    channels = (uint8_t)Channels;

    for (px_pos = 0; px_pos < px_len; px_pos += channels) {
        px.rgba.r = pixels[px_pos + 0];
        px.rgba.g = pixels[px_pos + 1];
        px.rgba.b = pixels[px_pos + 2];

        if (channels == 4) {
            px.rgba.a = pixels[px_pos + 3];
        }

        if (px.v == px_prev.v) {
            run++;
            if (run == 62 || px_pos == px_end) {
                bytes[p++] = QOI_OP_RUN | (run - 1);
                run = 0;
            }
        }
        else {
            int index_pos;

            if (run > 0) {
                bytes[p++] = QOI_OP_RUN | (run - 1);
                run = 0;
            }

            index_pos = QOI_COLOR_HASH(px) % 64;

            if (index[index_pos].v == px.v) {
                bytes[p++] = QOI_OP_INDEX | index_pos;
            }
            else {
                index[index_pos] = px;

                if (px.rgba.a == px_prev.rgba.a) {
                    signed char vr = px.rgba.r - px_prev.rgba.r;
                    signed char vg = px.rgba.g - px_prev.rgba.g;
                    signed char vb = px.rgba.b - px_prev.rgba.b;

                    signed char vg_r = vr - vg;
                    signed char vg_b = vb - vg;

                    if (
                        vr > -3 && vr < 2 &&
                        vg > -3 && vg < 2 &&
                        vb > -3 && vb < 2
                        ) {
                        bytes[p++] = QOI_OP_DIFF | (vr + 2) << 4 | (vg + 2) << 2 | (vb + 2);
                    }
                    else if (
                        vg_r > -9 && vg_r <  8 &&
                        vg   > -33 && vg   < 32 &&
                        vg_b >  -9 && vg_b < 8
                        ) {
                        bytes[p++] = QOI_OP_LUMA | (vg + 32);
                        bytes[p++] = (vg_r + 8) << 4 | (vg_b + 8);
                    }
                    else {
                        bytes[p++] = QOI_OP_RGB;
                        bytes[p++] = px.rgba.r;
                        bytes[p++] = px.rgba.g;
                        bytes[p++] = px.rgba.b;
                    }
                }
                else {
                    bytes[p++] = QOI_OP_RGBA;
                    bytes[p++] = px.rgba.r;
                    bytes[p++] = px.rgba.g;
                    bytes[p++] = px.rgba.b;
                    bytes[p++] = px.rgba.a;
                }
            }
        }
        px_prev = px;
    }

    for (i = 0; i < (int)sizeof(qoi_padding); i++) {
        bytes[p++] = qoi_padding[i];
    }

    ByteLength = p;
    return bytes;
}

uint8_t* QOI::Decode(uint8_t* Data, uint32_t Size, int Width, int Height, uint8_t Channels)
{
    const uint8_t* bytes;
    uint32_t header_magic;
    uint8_t* pixels;
    qoi_rgba_t index[64];
    qoi_rgba_t px;
    int px_len, chunks_len, px_pos;
    int p = 0, run = 0;

    if (Data == nullptr)
    {
        return nullptr;
    }

    if (Size < QOI_HEADER_SIZE + (int)sizeof(qoi_padding))
    {
        return nullptr;
    }

    bytes = (const uint8_t*)Data;

    header_magic = ByteOperations::ReadUint32(bytes, &p);

    if (header_magic != QOI_MAGIC ||
        (uint32_t)Height >= QOI_PIXELS_MAX / (uint32_t)Width
        ) {
        return nullptr;
    }

    px_len = Width * Height * (uint8_t)Channels;
    pixels = new uint8_t[px_len];
    if (!pixels) {
        return nullptr;
    }

    std::memset(index, 0, sizeof(index));
    px.rgba.r = 0;
    px.rgba.g = 0;
    px.rgba.b = 0;
    px.rgba.a = 255;

    chunks_len = Size - (int)sizeof(qoi_padding);
    for (px_pos = 0; px_pos < px_len; px_pos += (uint8_t)Channels) {
        if (run > 0) {
            run--;
        }
        else if (p < chunks_len) {
            int b1 = bytes[p++];

            if (b1 == QOI_OP_RGB) {
                px.rgba.r = bytes[p++];
                px.rgba.g = bytes[p++];
                px.rgba.b = bytes[p++];
            }
            else if (b1 == QOI_OP_RGBA) {
                px.rgba.r = bytes[p++];
                px.rgba.g = bytes[p++];
                px.rgba.b = bytes[p++];
                px.rgba.a = bytes[p++];
            }
            else if ((b1 & QOI_MASK_2) == QOI_OP_INDEX) {
                px = index[b1];
            }
            else if ((b1 & QOI_MASK_2) == QOI_OP_DIFF) {
                px.rgba.r += ((b1 >> 4) & 0x03) - 2;
                px.rgba.g += ((b1 >> 2) & 0x03) - 2;
                px.rgba.b += (b1 & 0x03) - 2;
            }
            else if ((b1 & QOI_MASK_2) == QOI_OP_LUMA) {
                int b2 = bytes[p++];
                int vg = (b1 & 0x3f) - 32;
                px.rgba.r += vg - 8 + ((b2 >> 4) & 0x0f);
                px.rgba.g += vg;
                px.rgba.b += vg - 8 + (b2 & 0x0f);
            }
            else if ((b1 & QOI_MASK_2) == QOI_OP_RUN) {
                run = (b1 & 0x3f);
            }

            index[QOI_COLOR_HASH(px) % 64] = px;
        }

        pixels[px_pos + 0] = px.rgba.r;
        pixels[px_pos + 1] = px.rgba.g;
        pixels[px_pos + 2] = px.rgba.b;

        if (Channels == 4) {
            pixels[px_pos + 3] = px.rgba.a;
        }
    }

    return pixels;
}
