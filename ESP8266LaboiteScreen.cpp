#include "Arduino.h"
#include "ESP8266LaboiteScreen.h"
#include <fonts.h>

Bitmap::Bitmap(uint8_t width, uint8_t height, String raw) {
  this->width = width;
  this->height = height;
  this->raw = raw;
};

Font::Font(uint8_t min, uint8_t max, uint8_t unknown, Bitmap* characters) {
  // attention, aucun buffer n'est initialisé à ce stade !
  this->min = min;
  this->max = max;
  this->unknown = unknown;
  this->characters = characters;
};

Bitmap Font::getBitmap(char c) {
  if (c < min || c > max) {
    c = unknown;
  }
  return characters[c - min];
};

Screen::Screen(void) {
  // attention, aucun buffer n'est initialisé à ce stade !
};

void Screen::clear() {
  for (int i = 0; i < buffer_lenght; i++) {
    buffer[i] = 0b00000000;
  }
};

uint8_t* Screen::getBuffer() {
  return buffer;
};

void Screen::setPixel(uint8_t x, uint8_t y) {
  if (x >= width or y >= height) {
    // en dehors de l'écran !
    return;
  }
  buffer[(x / 8) + (y * (width / 8) )] = buffer[(x / 8) + (y * (width / 8))] | (0b10000000 >> (x % 8));
};

void Screen::drawBitmap(uint8_t x, uint8_t y, Bitmap bitmap) {
  // cette fonction est très moche !
  // elle nécessite d'être réecrite
  int bitIndex = 0;
  int demiOctetIndex = 0;
  int demiOctetOffset = 0;
  int demiOctet = 0;

  for (int j = 0; j < bitmap.height; j++) {
    for (int i = 0; i < bitmap.width; i++) {
      demiOctetIndex = 3 - (bitIndex % 4);
      demiOctetOffset = bitIndex / 4;
      uint8_t masque = 0b00000001;
      char contentChar = bitmap.raw[demiOctetOffset + 2];
      switch (contentChar) {
        case '0':
          demiOctet = 0;
          break;

        case '1':
          demiOctet = 1;
          break;

        case '2':
          demiOctet = 2;
          break;

        case '3':
          demiOctet = 3;
          break;

        case '4':
          demiOctet = 4;
          break;

        case '5':
          demiOctet = 5;
          break;

        case '6':
          demiOctet = 6;
          break;

        case '7':
          demiOctet = 7;
          break;

        case '8':
          demiOctet = 8;
          break;

        case '9':
          demiOctet = 9;
          break;

        case 'a':
          demiOctet = 10;
          break;

        case 'b':
          demiOctet = 11;
          break;

        case 'c':
          demiOctet = 12;
          break;

        case 'd':
          demiOctet = 13;
          break;

        case 'e':
          demiOctet = 14;
          break;

        case 'f':
          demiOctet = 15;
          break;
      }
      if ((demiOctet >> demiOctetIndex) & masque) {
        if (bitmap.raw.length() - 2 > demiOctetOffset) { // bug de l'icone vélo
          setPixel(i + x, j + y);
        }
      }
      bitIndex += 1;
    }
  }
};

void Screen::print(uint8_t x, uint8_t y, char c, Font * font) {
  drawBitmap(x, y, font->getBitmap(c));
};

void Screen::print(uint8_t x, uint8_t y, String s, uint8_t font_name) {
  int offset = 0;
  for (int i = 0; i < s.length(); i++) {
    switch (font_name) {
      case FONT_4X6:
        print(x + offset, y, s[i], font_4x6);
        // on déplace le curseur de la largeur du caractère imprimé
        offset += font_4x6->getBitmap(s[i]).width;
        break;
      case FONT_5X7:
      default:
        print(x + offset, y, s[i], font_5x7);
        // on déplace le curseur de la largeur du caractère imprimé
        offset += font_5x7->getBitmap(s[i]).width;
        break;
    }
  }
};

Screen_32_16_2::Screen_32_16_2(void) {
  buffer_lenght = BUFFER_32_16_2;
  width = 32;
  height = 16;
  colors = 2;
  buffer = _buffer;
  clear();
}

void Screen_32_16_2::demo() {
  print(1, 1, "Hello", FONT_DEFAULT);
  print(1, 9, "World!", FONT_DEFAULT);
};
