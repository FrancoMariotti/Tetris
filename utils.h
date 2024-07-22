#ifndef UITLS_H
#define UITLS_H

typedef struct Color {
  unsigned int red;
  unsigned int green;
  unsigned int blue;
} Color_t;

enum ColorCode: int;

const Color_t Red = {0xFF, 0x00, 0x00};
const Color_t Magenta = {0xF5, 0x2A, 0xC2};
const Color_t Green = {0x94, 0xE3, 0x4B};
const Color_t Blue = {0x22, 0x65, 0xBD};
const Color_t Cian = {0x05, 0xD5, 0xF5};
const Color_t Orange = {0xFA, 0x90, 0x05};
const Color_t Yellow = {0xFC, 0xF0, 0x00};
const Color_t Black = {0x00, 0x00, 0x00};
const Color_t Grey = {0x80, 0x80, 0x80};

int getColorId(void);
const Color_t* getColor(int id);

#endif
