#ifndef BITMAPS_H
#define BITMAPS_H

#include <avr/pgmspace.h>

//Magic that allows BXXXXXXXX format
#include <SPI.h>

PROGMEM const unsigned char ArduShip_TD_Up_16_16[] = {16,16,
B00011110,B00000000,
B01100001,B10000000,
B10001100,B01000000,
B10100001,B01000000,
B10000000,B01000000,
B01101101,B10000000,
B00111111,B00000000,
B00010010,B00000000,
B10110011,B01000000,
B11010010,B11000000,
B10111111,B01000000,
B11001100,B11000000,
B10000000,B01000000,
B10000000,B01000000,
B00000000,B00000000,
B00000000,B00000000,
/*  0x1C, 0x22, 0x6A, 0xC1, 0x65, 0x65, 0xC1, 0x6A, 
  0x22, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x3F, 0x0A, 0x05, 0x07, 0x0C, 0x0C, 0x07, 0x05, 
  0x0A, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00*/
};

PROGMEM const unsigned char ArduShip_TD_Left_16_16[] = {16,16,
B00111000,B11111100,
B01000100,B01010000,
B01010110,B10100000,
B10000011,B11100000,
B10100110,B00110000,
B10100110,B00110000,
B10000011,B11100000,
B01010110,B10100000,
B01000100,B01010000,
B00111000,B11111100,
B00000000,B00000000,
B00000000,B00000000,
B00000000,B00000000,
B00000000,B00000000,
B00000000,B00000000,
B00000000,B00000000,
/*  0x78, 0x86, 0x31, 0x85, 0x01, 0xB6, 0xFC, 0x48, 
  0xCD, 0x4B, 0xFD, 0x33, 0x01, 0x01, 0x00, 0x00, 
  0x00, 0x01, 0x02, 0x02, 0x02, 0x01, 0x00, 0x00, 
  0x02, 0x03, 0x02, 0x03, 0x02, 0x02, 0x00, 0x00*/
};

PROGMEM const unsigned char ArduShip_TD_Right_16_16[] = {16,16,
B11111100,B01110000,
B00101000,B10001000,
B00010101,B10101000,
B00011111,B00000100,
B00110001,B10010100,
B00110001,B10010100,
B00011111,B00000100,
B00010101,B10101000,
B00101000,B10001000,
B11111100,B01110000,
B00000000,B00000000,
B00000000,B00000000,
B00000000,B00000000,
B00000000,B00000000,
B00000000,B00000000,
B00000000,B00000000,
/* 0x01, 0x01, 0x33, 0xFD, 0x4B, 0xCD, 0x48, 0xFC, 
  0xB6, 0x01, 0x85, 0x31, 0x86, 0x78, 0x00, 0x00, 
  0x02, 0x02, 0x03, 0x02, 0x03, 0x02, 0x00, 0x00, 
  0x01, 0x02, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00 */
};

PROGMEM const unsigned char ArduShip_TD_Down_16_16[] = {16,16,
B10000000,B01000000,
B10000000,B01000000,
B11001100,B11000000,
B10111111,B01000000,
B11010010,B11000000,
B10110011,B01000000,
B00010010,B00000000,
B00111111,B00000000,
B01101101,B10000000,
B10000000,B01000000,
B10100001,B01000000,
B10001100,B01000000,
B01100001,B10000000,
B00011110,B00000000,
B00000000,B00000000,
B00000000,B00000000,
/*  0x3F, 0x14, 0xA8, 0xF8, 0x8C, 0x8C, 0xF8, 0xA8, 
  0x14, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x0E, 0x11, 0x15, 0x20, 0x29, 0x29, 0x20, 0x15, 
  0x11, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 */
};

PROGMEM const unsigned char ArduShip_TD_UpLeft_16_16[] = {16,16,
B00111110,B00000000,
B01000001,B00000000,
B10010101,B00000000,
B10100001,B00000000,
B10000001,B00100000,
B10100011,B00010000,
B10000110,B11101000,
B01111100,B01001100,
B00000010,B00110010,
B00000011,B00100000,
B00001010,B11010000,
B00000100,B10110000,
B00000011,B00000000,
B00000001,B00000000,
B00000000,B10000000,
B00000000,B00000000,
/*  0x7C, 0x82, 0xA9, 0x85, 0x81, 0xC5, 0x61, 0x3E, 
  0x40, 0xC0, 0x50, 0x20, 0xC0, 0x80, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x04, 0x08, 0x17, 0x32, 
  0x4C, 0x04, 0x0B, 0x0D, 0x00, 0x00, 0x01, 0x00*/
};

PROGMEM const unsigned char ArduShip_TD_UpRight_16_16[] = {16,16,
B00000000,B11111000,
B00000001,B00000100,
B00000001,B01010010,
B00000001,B00001010,
B00001001,B00000010,
B00010001,B10001010,
B00101110,B11000010,
B01100100,B01111100,
B10011000,B10000000,
B00001001,B10000000,
B00010110,B10100000,
B00011010,B01000000,
B00000001,B10000000,
B00000001,B00000000,
B00000010,B00000000,
B00000000,B00000000,
/*  0x00, 0x80, 0xC0, 0x20, 0x50, 0xC0, 0x40, 0x3E, 
  0x61, 0xC5, 0x81, 0x85, 0xA9, 0x82, 0x7C, 0x00, 
  0x01, 0x00, 0x00, 0x0D, 0x0B, 0x04, 0x4C, 0x32, 
  0x17, 0x08, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00 */
};

PROGMEM const unsigned char ArduShip_TD_DownLeft_16_16[] = {16,16,
B00000000,B10000000,
B00000001,B00000000,
B00000011,B00000000,
B00000100,B10110000,
B00001010,B11010000,
B00000011,B00100000,
B00000010,B00110010,
B01111100,B01001100,
B10000110,B11101000,
B10100011,B00010000,
B10000001,B00100000,
B10100001,B00000000,
B10010101,B00000000,
B01000001,B00000000,
B00111110,B00000000,
B00000000,B00000000,
/*  0x00, 0x80, 0x80, 0x80, 0x90, 0x88, 0x74, 0x26, 
  0x19, 0x90, 0x68, 0x58, 0x80, 0x80, 0x40, 0x00, 
  0x1F, 0x20, 0x4A, 0x50, 0x40, 0x51, 0x43, 0x3E, 
  0x01, 0x01, 0x05, 0x02, 0x01, 0x00, 0x00, 0x00 */
};

PROGMEM const unsigned char ArduShip_TD_DownRight_16_16[] = {16,16,
B00000010,B00000000,
B00000001,B00000000,
B00000001,B10000000,
B00011010,B01000000,
B00010110,B10100000,
B00001001,B10000000,
B10011000,B10000000,
B01100100,B01111100,
B00101110,B11000010,
B00010001,B10001010,
B00001001,B00000010,
B00000001,B00001010,
B00000001,B01010010,
B00000001,B00000100,
B00000000,B11111000,
B00000000,B00000000,
/*  0x40, 0x80, 0x80, 0x58, 0x68, 0x90, 0x19, 0x26, 
  0x74, 0x88, 0x90, 0x80, 0x80, 0x80, 0x00, 0x00, 
  0x00, 0x00, 0x01, 0x02, 0x05, 0x01, 0x01, 0x3E, 
  0x43, 0x51, 0x40, 0x50, 0x4A, 0x20, 0x1F, 0x00 */
};

PROGMEM const unsigned char ArduShip_1_32_10[] = {32,10,
  0x7F, 0xE0, 0x00, 0x00, 0x80, 0x10, 0x7F, 0x00,
  0x7F, 0xE1, 0x80, 0xE0, 0x02, 0x82, 0x00, 0xC0,
  0x01, 0x45, 0xFF, 0x00, 0x00, 0xA9, 0x00, 0x00,
  0x1F, 0xFE, 0x00, 0x00, 0x08, 0x01, 0x00, 0x00,
  0x07, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// Enemy Ship
PROGMEM const unsigned char EnemyShip_16_16[] = {16,16,
  0xF0, 0x18, 0xE0, 0x00, 0x04, 0x8C, 0x72, 0x09, 
  0x09, 0x72, 0x8C, 0x04, 0x00, 0xE0, 0x18, 0xF0, 
  0x1F, 0x20, 0x29, 0x42, 0x41, 0x48, 0xA4, 0xA2, 
  0xA2, 0xA4, 0x48, 0x41, 0x42, 0x29, 0x20, 0x1F
};

// Ship diagram
PROGMEM const unsigned char ShipStatus_48_60[] = {48,60,
  0x00, 0x00, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x0F, 
  0x00, 0x3C, 0x00, 0x00, 0x00, 0x30, 0x00, 0x03, 
  0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0xC0, 0x00, 
  0x01, 0x00, 0x00, 0x00, 0x20, 0x00, 0x06, 0x00, 
  0x00, 0x00, 0x18, 0x00, 0x08, 0x00, 0x00, 0x00, 
  0x04, 0x00, 0x10, 0x00, 0x00, 0x00, 0x02, 0x00, 
  0x20, 0x00, 0x00, 0x00, 0x01, 0x00, 0x20, 0x00, 
  0x00, 0x00, 0x01, 0x00, 0x40, 0x00, 0x00, 0x00, 
  0x00, 0x80, 0x40, 0x00, 0x00, 0x00, 0x00, 0x80, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x40, 0x80, 0x00, 
  0x00, 0x00, 0x00, 0x40, 0x80, 0x00, 0x00, 0x00, 
  0x00, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x40, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x40, 0x80, 0x00, 
  0x00, 0x00, 0x00, 0x40, 0x40, 0x00, 0x00, 0x00, 
  0x00, 0x80, 0x40, 0x00, 0x00, 0x00, 0x00, 0x80, 
  0x20, 0x00, 0x00, 0x00, 0x01, 0x00, 0x20, 0x00, 
  0x00, 0x00, 0x01, 0x00, 0x10, 0x00, 0x00, 0x00, 
  0x02, 0x00, 0x08, 0x00, 0x00, 0x00, 0x04, 0x00, 
  0x06, 0x00, 0x00, 0x00, 0x18, 0x00, 0x01, 0x00, 
  0x00, 0x00, 0x20, 0x00, 0x00, 0xC0, 0x00, 0x00, 
  0xC0, 0x00, 0x00, 0x30, 0x00, 0x03, 0x00, 0x00, 
  0x00, 0x0F, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x01, 
  0xFF, 0xE0, 0x00, 0x00, 0x00, 0x02, 0x00, 0x10, 
  0x00, 0x00, 0x00, 0x02, 0x00, 0x10, 0x00, 0x00, 
  0x00, 0x02, 0x00, 0x10, 0x00, 0x00, 0x01, 0xC2, 
  0x00, 0x10, 0xE0, 0x00, 0x01, 0x42, 0x00, 0x10, 
  0xA0, 0x00, 0x02, 0x22, 0x00, 0x11, 0x10, 0x00, 
  0x04, 0x12, 0x00, 0x12, 0x08, 0x00, 0x04, 0x12, 
  0x00, 0x12, 0x08, 0x00, 0x04, 0x12, 0x00, 0x12, 
  0x08, 0x00, 0x04, 0x12, 0x00, 0x12, 0x08, 0x00, 
  0x08, 0x0A, 0x00, 0x14, 0x04, 0x00, 0x08, 0x09, 
  0x00, 0x24, 0x04, 0x00, 0x08, 0x0D, 0x00, 0x2C, 
  0x04, 0x00, 0x08, 0x0F, 0x00, 0x3C, 0x04, 0x00, 
  0x08, 0x09, 0x00, 0x24, 0x04, 0x00, 0x08, 0x08, 
  0x80, 0x44, 0x04, 0x00, 0x08, 0x09, 0x80, 0x64, 
  0x04, 0x00, 0x08, 0x0A, 0x80, 0x54, 0x04, 0x00, 
  0x08, 0x0C, 0x40, 0x8C, 0x04, 0x00, 0x08, 0x08, 
  0x21, 0x04, 0x04, 0x00, 0x08, 0x08, 0x12, 0x04, 
  0x04, 0x00, 0x08, 0x08, 0x0C, 0x04, 0x04, 0x00, 
  0x08, 0x08, 0x00, 0x04, 0x04, 0x00, 0x04, 0x10, 
  0x00, 0x02, 0x08, 0x00, 0x04, 0x10, 0x00, 0x02, 
  0x08, 0x00, 0x04, 0x10, 0x00, 0x02, 0x08, 0x00, 
  0x04, 0x10, 0x00, 0x02, 0x08, 0x00, 0x02, 0x20, 
  0x00, 0x01, 0x10, 0x00, 0x01, 0x40, 0x00, 0x00, 
  0xA0, 0x00, 0x01, 0xC0, 0x00, 0x00, 0xE0, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

PROGMEM const unsigned char ShipStatusText__0004_Repair_32_7[] = {32,7,
  0xC0, 0x00, 0x08, 0x00, 0xA0, 0x00, 0x00, 0x00, 
  0xA7, 0x39, 0xC8, 0xC0, 0xC7, 0x28, 0xC8, 0x80, 
  0xA4, 0x29, 0x48, 0x80, 0x27, 0x39, 0xDC, 0x80, 
  0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

PROGMEM const unsigned char ShipStatusText__0006_AuxPower_48_6[] = {48,6,
  0x20, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x60, 0x00, 
  0x0A, 0x00, 0x00, 0x00, 0x50, 0x94, 0x0A, 0x75, 
  0x5D, 0x80, 0x52, 0x88, 0x0C, 0x97, 0x9D, 0x00, 
  0xB2, 0x98, 0x08, 0x93, 0x91, 0x00, 0x8B, 0x14, 
  0x00, 0x72, 0x9D, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

PROGMEM const unsigned char SelectionArrow_8_8[] = {8,8,
  0x18, 0x18, 0xFF, 0xFF, 0x7E, 0x3C, 0x18, 0x00
};

PROGMEM const unsigned char Arrow_Left_8_5[] = {8,5,
  0x10, 0x70, 0xF0, 0x70, 0x10, 0x00, 0x00, 0x00
};

PROGMEM const unsigned char Arrow_Right_8_5[] = {8,5,
  0x80, 0xE0, 0xF0, 0xE0, 0x80, 0x00, 0x00, 0x00
};

PROGMEM const unsigned char Menu_Fire_16_5[] = {16,5,
  0xE0, 0x00, 0x90, 0x20, 0xC7, 0x50, 0x94, 0x60, 
  0x94, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

PROGMEM const unsigned char Menu_Warp_24_6[] = {24,6,
  0x88, 0x00, 0x00, 0x88, 0x00, 0x00, 0x8B, 0x9D, 
  0xC0, 0xAA, 0x91, 0x40, 0xFB, 0x51, 0xC0, 0x00, 
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

PROGMEM const unsigned char Menu_Com_16_5[] = {16,5,
  0xE0, 0x00, 0x80, 0x00, 0x8E, 0xF8, 0x8A, 0xA8, 
  0xEE, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

PROGMEM const unsigned char Menu_Evade_24_5[] = {24,5,
  0xE0, 0x00, 0x00, 0x80, 0x01, 0x20, 0xCA, 0xE7, 
  0x50, 0x8C, 0xA5, 0x60, 0xE8, 0xD7, 0x70, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

PROGMEM const unsigned char Menu_Status_24_5[] = {24,5,
  0xE4, 0x04, 0x00, 0x84, 0x04, 0x07, 0x4E, 0xEE, 
  0xA6, 0x24, 0xA4, 0xA1, 0xE4, 0xD4, 0xD7, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

PROGMEM const unsigned char Menu_Engine_24_5[] = {24,5,
  0xE0, 0xE8, 0x00, 0x80, 0xA0, 0x10, 0xCE, 0xEB, 
  0xA8, 0x8A, 0x2A, 0xB0, 0xEA, 0xEA, 0xB8, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

PROGMEM const unsigned char Menu_Hull_16_5[] = {16,5,
  0xA0, 0xA0, 0xA0, 0xA0, 0xEA, 0xA0, 0xAA, 0xA0, 
  0xAE, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

PROGMEM const unsigned char Menu_Weapons_32_5[] = {32,5,
  0x88, 0x00, 0x00, 0x00, 0x89, 0x01, 0xC0, 0x1C, 
  0x8A, 0xB9, 0x5D, 0xD8, 0xAB, 0x29, 0xD5, 0x44, 
  0x53, 0xB5, 0x1D, 0x5C, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

PROGMEM const unsigned char Menu_Shields_24_5[] = {24,5,
  0xE8, 0x82, 0x20, 0x88, 0x12, 0x2E, 0x4E, 0xAA, 
  0xEC, 0x2A, 0xB2, 0xA2, 0xEA, 0xBA, 0xEE, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

PROGMEM const unsigned char Menu_Offline_24_5[] = {24,5,
  0xE0, 0x28, 0x00, 0xAD, 0xA0, 0x10, 0xA9, 0x2B, 
  0xA8, 0xAD, 0xAA, 0xB0, 0xE9, 0x2A, 0xB8, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

PROGMEM const unsigned char Menu_Auxilary_32_5[] = {32,5,
  0xE0, 0x0A, 0x00, 0x00, 0xA0, 0x02, 0x00, 0x50, 
  0xEA, 0xAA, 0xE7, 0x70, 0xAA, 0x4A, 0xA4, 0x10, 
  0xAE, 0xAA, 0xD4, 0x70, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


///
/// Planets
///

PROGMEM const unsigned char Planet_1_16_16[] = {16,16,
  0xC0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFE, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFE, 0xFA, 0xE4, 0xC8, 0x30, 0xC0, 
  0x03, 0x0F, 0x13, 0x27, 0x4F, 0x55, 0x8B, 0xBF, 
  0xBF, 0xBF, 0x7B, 0x7F, 0x3F, 0x1F, 0x0E, 0x03
};

PROGMEM const unsigned char Planet_2_16_16[] = {16,16,
  0xC0, 0x30, 0x28, 0x7C, 0x72, 0xE2, 0xE7, 0xE7, 
  0xF7, 0x17, 0x12, 0x02, 0x44, 0xF8, 0xF0, 0xC0, 
  0x03, 0x0C, 0x10, 0x20, 0x40, 0x41, 0x83, 0x83, 
  0xFF, 0xBD, 0x78, 0x40, 0x20, 0x10, 0x0C, 0x03
};

PROGMEM const unsigned char Planet_3_16_16[] = {16,16,
  0xC0, 0x30, 0x08, 0xE4, 0x12, 0x0A, 0x89, 0x89, 
  0x09, 0x19, 0xF2, 0x02, 0x04, 0xF8, 0xF0, 0xC0, 
  0x03, 0x0C, 0x10, 0x27, 0x48, 0x58, 0x91, 0x93, 
  0xB2, 0xB3, 0x51, 0x58, 0x2C, 0x17, 0x0C, 0x03
};

PROGMEM const unsigned char Planet_4_16_16[] = {16,16,
  0xC0, 0x70, 0xC8, 0x8C, 0x1A, 0x32, 0x61, 0xC3, 
  0x87, 0x0D, 0x1A, 0x32, 0x64, 0xC8, 0xB0, 0xC0, 
  0x03, 0x0C, 0x10, 0x21, 0x43, 0x46, 0x8C, 0x98, 
  0xB1, 0xE3, 0x46, 0x4C, 0x38, 0x10, 0x0D, 0x03
};

PROGMEM const unsigned char Planet_5_16_16[] = {16,16,
  0xC0, 0x30, 0x08, 0x1C, 0x3E, 0x3A, 0xF1, 0x39, 
  0x01, 0x81, 0x82, 0xF2, 0x74, 0x18, 0x30, 0xC0, 
  0x03, 0x0C, 0x14, 0x26, 0x4E, 0x5E, 0xB0, 0xB0, 
  0x80, 0x81, 0x5B, 0x4B, 0x2F, 0x10, 0x0C, 0x03
};

PROGMEM const unsigned char Planet_6_16_16[] = {16,16,
  0xC0, 0x30, 0x08, 0x04, 0x0E, 0x0E, 0x05, 0xC1, 
  0xE1, 0xC1, 0x82, 0x0E, 0x0C, 0x08, 0xB0, 0xC0, 
  0x03, 0x0C, 0x10, 0x23, 0x4E, 0x4E, 0x8E, 0x80, 
  0xE0, 0xA3, 0x63, 0x40, 0x2C, 0x1F, 0x0F, 0x03
};

PROGMEM const unsigned char Planet_7_16_16[] = {16,16,
  0xC0, 0x30, 0x88, 0x44, 0x42, 0x4A, 0x89, 0x09, 
  0x09, 0x49, 0x8A, 0x8A, 0x8C, 0x08, 0x30, 0xC0, 
  0x03, 0x0C, 0x10, 0x21, 0x51, 0x51, 0x80, 0x84, 
  0x8A, 0x8A, 0x44, 0x40, 0x20, 0x10, 0x0C, 0x03
};

PROGMEM const unsigned char Planet_8_16_16[] = {16,16,
  0xC0, 0x30, 0x08, 0x04, 0x02, 0x12, 0x29, 0x11, 
  0x01, 0x81, 0x82, 0x22, 0x54, 0x28, 0x30, 0xC0, 
  0x03, 0x0C, 0x10, 0x2C, 0x52, 0x52, 0x8C, 0x80, 
  0x83, 0x84, 0x44, 0x43, 0x20, 0x10, 0x0C, 0x03
};

PROGMEM const unsigned char Planet_9_16_16[] = {16,16,
  0xC0, 0x30, 0x08, 0x04, 0x3A, 0x2A, 0x39, 0x01, 
  0xC1, 0x41, 0x62, 0x42, 0xC4, 0x08, 0x30, 0xC0, 
  0x03, 0x0C, 0x10, 0x3C, 0x54, 0x5C, 0x80, 0x81, 
  0x87, 0x84, 0x4D, 0x44, 0x27, 0x11, 0x0C, 0x03
};

PROGMEM const unsigned char Planet_10_16_16[] = {16,16,
  0xFF, 0x01, 0x01, 0x1D, 0x15, 0x15, 0xDD, 0x41, 
  0x41, 0x41, 0xDD, 0x15, 0x1D, 0x01, 0x01, 0xFF, 
  0xFF, 0x80, 0x9C, 0x94, 0x9C, 0x80, 0x8F, 0x88, 
  0x88, 0x88, 0x8F, 0xF0, 0xD0, 0xF0, 0x80, 0xFF
};

PROGMEM const unsigned char PlanetHome_16_64[] = {16,64,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF, 0xFF, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFC, 0xE3, 
  0xC0, 0x81, 0x81, 0x07, 0x0F, 0x0F, 0x0F, 0x00, 
  0x00, 0x00, 0xE0, 0xF8, 0xFF, 0x3F, 0x0F, 0x9F, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xDE, 0x80, 0x00, 0x00, 
  0xF0, 0xFF, 0x7F, 0x3F, 0xFF, 0xFF, 0x7F, 0x3F, 
  0x3F, 0x3F, 0x7F, 0x7F, 0x7F, 0x3F, 0x1C, 0x00, 
  0x0F, 0xFF, 0x7F, 0x3F, 0x1F, 0x1F, 0x00, 0x00, 
  0x00, 0x80, 0xC0, 0xC0, 0xC0, 0xE0, 0xA0, 0xE0, 
  0x00, 0x00, 0x07, 0x18, 0xE0, 0x20, 0x98, 0xCC, 
  0xF7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x3F, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x03, 0x07, 0x0F, 0x17, 0x27, 0x41, 0x80, 0x00
};

PROGMEM const unsigned char Bubble_8_8[] = {8,8,
  0x0C, 0x1E, 0x3F, 0x3F, 0x1E, 0x0C, 0x00, 0x00
};

PROGMEM const unsigned char Bubble_Empty_8_8[] = {8,8,
  0x0C, 0x12, 0x21, 0x21, 0x12, 0x0C, 0x00, 0x00
};

///
/// Weapon Bitmaps
///

PROGMEM const unsigned char Torpedo_8_3[] = {
  0x40, 0xA0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00
};

#endif
