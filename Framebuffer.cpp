/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>
*/

#include "Framebuffer.h"

void Framebuffer::init()
{
    this->clear();
    oled.init();
}

#ifndef SIMULATOR
void Framebuffer::drawBitmap(const uint8_t *progmem_bitmap, uint8_t height, uint8_t width, uint8_t pos_x, uint8_t pos_y) {
    uint8_t current_byte;
    uint8_t byte_width = (width + 7)/8;

    for (uint8_t current_y = 0; current_y < height; current_y++) {
        for (uint8_t current_x = 0; current_x < width; current_x++) {
            current_byte = pgm_read_byte(progmem_bitmap + current_y*byte_width + current_x/8);
            if (current_byte & (128 >> (current_x&7))) {
                this->drawPixel(current_x+pos_x,current_y+pos_y,1);
            } else {
                this->drawPixel(current_x+pos_x,current_y+pos_y,0);
            }
        }
    }
}


const uint8_t PROGMEM font6x8[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,// sp
  0x00, 0x00, 0x00, 0x2f, 0x00, 0x00,// !
  0x00, 0x00, 0x07, 0x00, 0x07, 0x00,// "
  0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14,// #
  0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12,// $
  0x00, 0x62, 0x64, 0x08, 0x13, 0x23,// %
  0x00, 0x36, 0x49, 0x55, 0x22, 0x50,// &
  0x00, 0x00, 0x05, 0x03, 0x00, 0x00,// '
  0x00, 0x00, 0x1c, 0x22, 0x41, 0x00,// (
  0x00, 0x00, 0x41, 0x22, 0x1c, 0x00,// )
  0x00, 0x14, 0x08, 0x3E, 0x08, 0x14,// *
  0x00, 0x08, 0x08, 0x3E, 0x08, 0x08,// +
  0x00, 0x00, 0x00, 0xA0, 0x60, 0x00,// ,
  0x00, 0x08, 0x08, 0x08, 0x08, 0x08,// -
  0x00, 0x00, 0x60, 0x60, 0x00, 0x00,// .
  0x00, 0x20, 0x10, 0x08, 0x04, 0x02,// /
  0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E,// 0
  0x00, 0x00, 0x42, 0x7F, 0x40, 0x00,// 1
  0x00, 0x42, 0x61, 0x51, 0x49, 0x46,// 2
  0x00, 0x21, 0x41, 0x45, 0x4B, 0x31,// 3
  0x00, 0x18, 0x14, 0x12, 0x7F, 0x10,// 4
  0x00, 0x27, 0x45, 0x45, 0x45, 0x39,// 5
  0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30,// 6
  0x00, 0x01, 0x71, 0x09, 0x05, 0x03,// 7
  0x00, 0x36, 0x49, 0x49, 0x49, 0x36,// 8
  0x00, 0x06, 0x49, 0x49, 0x29, 0x1E,// 9
  0x00, 0x00, 0x36, 0x36, 0x00, 0x00,// :
  0x00, 0x00, 0x56, 0x36, 0x00, 0x00,// ;
  0x00, 0x08, 0x14, 0x22, 0x41, 0x00,// <
  0x00, 0x14, 0x14, 0x14, 0x14, 0x14,// =
  0x00, 0x00, 0x41, 0x22, 0x14, 0x08,// >
  0x00, 0x02, 0x01, 0x51, 0x09, 0x06,// ?
  0x00, 0x32, 0x49, 0x59, 0x51, 0x3E,// @
  0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C,// A
  0x00, 0x7F, 0x49, 0x49, 0x49, 0x36,// B
  0x00, 0x3E, 0x41, 0x41, 0x41, 0x22,// C
  0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C,// D
  0x00, 0x7F, 0x49, 0x49, 0x49, 0x41,// E
  0x00, 0x7F, 0x09, 0x09, 0x09, 0x01,// F
  0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A,// G
  0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F,// H
  0x00, 0x00, 0x41, 0x7F, 0x41, 0x00,// I
  0x00, 0x20, 0x40, 0x41, 0x3F, 0x01,// J
  0x00, 0x7F, 0x08, 0x14, 0x22, 0x41,// K
  0x00, 0x7F, 0x40, 0x40, 0x40, 0x40,// L
  0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F,// M
  0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F,// N
  0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E,// O
  0x00, 0x7F, 0x09, 0x09, 0x09, 0x06,// P
  0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E,// Q
  0x00, 0x7F, 0x09, 0x19, 0x29, 0x46,// R
  0x00, 0x46, 0x49, 0x49, 0x49, 0x31,// S
  0x00, 0x01, 0x01, 0x7F, 0x01, 0x01,// T
  0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F,// U
  0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F,// V
  0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F,// W
  0x00, 0x63, 0x14, 0x08, 0x14, 0x63,// X
  0x00, 0x07, 0x08, 0x70, 0x08, 0x07,// Y
  0x00, 0x61, 0x51, 0x49, 0x45, 0x43,// Z
  0x00, 0x00, 0x7F, 0x41, 0x41, 0x00,// [
  0x00, 0x55, 0x2A, 0x55, 0x2A, 0x55,// 55
  0x00, 0x00, 0x41, 0x41, 0x7F, 0x00,// ]
  0x00, 0x04, 0x02, 0x01, 0x02, 0x04,// ^
  0x00, 0x40, 0x40, 0x40, 0x40, 0x40,// _
  0x00, 0x00, 0x01, 0x02, 0x04, 0x00,// '
  0x00, 0x20, 0x54, 0x54, 0x54, 0x78,// a
  0x00, 0x7F, 0x48, 0x44, 0x44, 0x38,// b
  0x00, 0x38, 0x44, 0x44, 0x44, 0x20,// c
  0x00, 0x38, 0x44, 0x44, 0x48, 0x7F,// d
  0x00, 0x38, 0x54, 0x54, 0x54, 0x18,// e
  0x00, 0x08, 0x7E, 0x09, 0x01, 0x02,// f
  0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C,// g
  0x00, 0x7F, 0x08, 0x04, 0x04, 0x78,// h
  0x00, 0x00, 0x44, 0x7D, 0x40, 0x00,// i
  0x00, 0x40, 0x80, 0x84, 0x7D, 0x00,// j
  0x00, 0x7F, 0x10, 0x28, 0x44, 0x00,// k
  0x00, 0x00, 0x41, 0x7F, 0x40, 0x00,// l
  0x00, 0x7C, 0x04, 0x18, 0x04, 0x78,// m
  0x00, 0x7C, 0x08, 0x04, 0x04, 0x78,// n
  0x00, 0x38, 0x44, 0x44, 0x44, 0x38,// o
  0x00, 0xFC, 0x24, 0x24, 0x24, 0x18,// p
  0x00, 0x18, 0x24, 0x24, 0x18, 0xFC,// q
  0x00, 0x7C, 0x08, 0x04, 0x04, 0x08,// r
  0x00, 0x48, 0x54, 0x54, 0x54, 0x20,// s
  0x00, 0x04, 0x3F, 0x44, 0x40, 0x20,// t
  0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C,// u
  0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C,// v
  0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C,// w
  0x00, 0x44, 0x28, 0x10, 0x28, 0x44,// x
  0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C,// y
  0x00, 0x44, 0x64, 0x54, 0x4C, 0x44,// z
  0x14, 0x14, 0x14, 0x14, 0x14, 0x14,// horiz lines
};

void Framebuffer::drawChar(char ch, uint8_t pos_x, uint8_t pos_y) {
    uint8_t current_byte, current_x, current_y;
    uint8_t c = ch - 32;
    for (current_x = 0; current_x < 6; current_x++) {
        current_byte = pgm_read_byte(&font6x8[c * 6 + current_x]);
        for (current_y = 0; current_y < 8; current_y++) {
            if (current_byte & (1 << current_y)) {
                this->drawPixel(current_x + pos_x, current_y + pos_y, 1);
            } else {
                this->drawPixel(current_x + pos_x, current_y + pos_y, 0);
            }
        }
    }
}

void Framebuffer::drawString(const char* s, uint8_t pos_x, uint8_t pos_y) {
    uint8_t current_x = pos_x;
    while(*s) {
        this->drawChar(*s++, current_x, pos_y);
        current_x += 6;
    }
}

void Framebuffer::drawBuffer(const uint8_t *progmem_buffer) {
    uint8_t current_byte;

    for (uint8_t y_pos = 0; y_pos < 64; y_pos++) {
        for (uint8_t x_pos = 0; x_pos < 128; x_pos++) {
            current_byte = pgm_read_byte(progmem_buffer + y_pos*16 + x_pos/8);
            if (current_byte & (128 >> (x_pos&7))) {
                this->drawPixel(x_pos,y_pos,1);
            } else {
                this->drawPixel(x_pos,y_pos,0);
            }
        }
    }
}
#endif

void Framebuffer::drawPixel(uint8_t pos_x, uint8_t pos_y, uint8_t pixel_status) {
    if (pos_x >= SSD1306_WIDTH || pos_y >= SSD1306_HEIGHT) {
        return;
    }

    if (pixel_status) {
        this->buffer[pos_x+(pos_y/8)*SSD1306_WIDTH] |= (1 << (pos_y&7));
    } else {
        this->buffer[pos_x+(pos_y/8)*SSD1306_WIDTH] &= ~(1 << (pos_y&7));
    }
}

void Framebuffer::drawPixel(uint8_t pos_x, uint8_t pos_y) {
    if (pos_x >= SSD1306_WIDTH || pos_y >= SSD1306_HEIGHT) {
        return;
    }

    this->buffer[pos_x+(pos_y/8)*SSD1306_WIDTH] |= (1 << (pos_y&7));
}

void Framebuffer::drawPixelInverse(uint8_t pos_x, uint8_t pos_y) {
    if (pos_x >= SSD1306_WIDTH || pos_y >= SSD1306_HEIGHT) {
        return;
    }
    this->buffer[pos_x+(pos_y/8)*SSD1306_WIDTH] ^= (1 << (pos_y&7));
}

void Framebuffer::drawVLine(uint8_t x, uint8_t y, uint8_t length) {
    for (uint8_t i = 0; i < length; ++i) {
        this->drawPixel(x,i+y);
    }
}

void Framebuffer::drawVLineInverse(uint8_t x, uint8_t y, uint8_t length) {
    for (uint8_t i = 0; i < length; ++i) {
        this->drawPixelInverse(x,i+y);
    }
}

void Framebuffer::drawHLine(uint8_t x, uint8_t y, uint8_t length) {
    for (uint8_t i = 0; i < length; ++i) {
        this->drawPixel(i+x,y);
    }
}

void Framebuffer::drawHLineInverse(uint8_t x, uint8_t y, uint8_t length) {
    for (uint8_t i = 0; i < length; ++i) {
        this->drawPixelInverse(i+x,y);
    }
}

void Framebuffer::drawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
    uint8_t length = x2 - x1 + 1;
    uint8_t height = y2 - y1;

    this->drawHLine(x1,y1,length);
    this->drawHLine(x1,y2,length);
    this->drawVLine(x1,y1,height);
    this->drawVLine(x2,y1,height);
}

void Framebuffer::drawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t fill) {
    if (!fill) {
        this->drawRectangle(x1,y1,x2,y2);
    } else {
        uint8_t length = x2 - x1 + 1;
        uint8_t height = y2 - y1;

        for (int x = 0; x < length; ++x) {
            for (int y = 0; y <= height; ++y) {
                this->drawPixel(x1+x,y+y1);
            }
        }
    }
}

void Framebuffer::clear() {
    for (uint16_t buffer_location = 0; buffer_location < SSD1306_BUFFERSIZE; buffer_location++) {
        this->buffer[buffer_location] = 0x00;
    }
}

void Framebuffer::invert(uint8_t status) {
    this->oled.invert(status);
}

void Framebuffer::show() {
    this->oled.sendFramebuffer(this->buffer);
}
