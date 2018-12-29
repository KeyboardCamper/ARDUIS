#ifndef GAMECORE_H
#define GAMECORE_H

#include <Arduboy2.h>
#include <avr/pgmspace.h>
#include "arduis_bitmaps.h"

const byte SCREEN_WIDTH = 128;
const byte SCREEN_HEIGHT = 64;
const byte BOOT = 0;
const byte TITLE = 1;
const byte GAME_START = 2;
const byte GAME_MAIN = 3;
const byte GAME_OVER = 4;
const byte STAR = 12;
const byte STAGE_LIMIT = 10;
const byte SHOT_NORMAL = 1;
const byte SHOT_DOUBLE = 2;
const byte SHOT_LASER = 3;
const byte SHOT_MAX = 10;
const byte OPTION_MAX = 5;
const byte BARRIER_LIFE = 16;
const byte ENEMY_SHOT_MAX = 4;
const byte ENEMY_IONRING_MAX = 8;
const byte MAPOBJ_MAX = 6;
const bool TYPE_NORMAL = false;
const bool TYPE_MUTEKI = true;

const byte BTN_U = 1;
const byte BTN_D = 2;
const byte BTN_L = 4;
const byte BTN_R = 8;
const byte BTN_A = 16;
const byte BTN_B = 32;

extern Arduboy2Base arduboy;
extern byte gameMode;
extern byte nowInput;
extern byte prevInput;
extern bool pressed;
extern byte stageNum;
extern byte gameRank;
extern byte gauge;
extern byte jikiLife;
extern byte playerSpeed;
extern byte shotType;
extern byte shotWait;
extern byte shotTotal;
extern byte optionTotal;
extern byte rapidMax;
extern bool barrierAlive;
extern byte barrierLife;
extern int score;
extern byte ox[OPTION_MAX];
extern byte oy[OPTION_MAX];
extern byte timer;
extern byte frame;
extern byte rndW;
extern byte rndH;

static const byte* bitmapsNum[] = { num0, num1, num2, num3, num4, num5, num6, num7, num8, num9 };
static const byte* bitmapsB1[] = { explosion2_1, explosion2_2, explosion2_3, explosion2_4 };
static const byte* bitmapsB2[] = { explosion3_1, explosion3_2, explosion3_3, explosion3_4 };
static const byte* bitmapsOp[] = { option_1, option_2, option_3, option_2 };
static const byte* bitmapsE1[] = { enemy1_1, enemy1_2, enemy1_3, enemy1_4 };
static const byte* bitmapsE2[] = { enemy2_1, enemy2_2, enemy2_3, enemy2_4 };
static const byte* bitmapsE3[] = { enemy3_1, enemy3_2, enemy3_3, enemy3_4, enemy3_5, enemy3_6, enemy3_7, enemy3_8, enemy3_9, enemy3_10 };
static const byte* bitmapsE4[] = { MoaiBase1_1, MoaiBase1_2, MoaiBase2_1, MoaiBase2_2 };
static const byte* bitmapsE4_2[] = { MoaiMouth1_1, MoaiMouth1_2, MoaiMouth2_1, MoaiMouth2_2 };
PROGMEM const char f[34] = { -4, -3, -2, -2, -1, -1, -1, 0, 0, 0, 0, 1, 1, 1, 2, 2, 3,
4, 3, 2, 2, 1, 1, 1, 0, 0, 0, 0, -1, -1, -1, -2, -2, -3 };
PROGMEM const byte sinTBL[4][8] = {
	{ 0, 0, 0, 1, 1, 1, 1, 1 },
	{ 0, 0, 1, 0, 0, 1, 1, 1 },
	{ 0, 1, 0, 1, 1, 0, 1, 1 },
	{ 0, 0, 1, 0, 1, 1, 1, 1 },
};
PROGMEM const byte atan2TBL[8][16] = {
	{ 4,3,3,2,2,1,1,1,1,1,1,1,1,1,1,1 },
	{ 5,4,3,3,2,2,2,2,1,1,1,1,1,1,1,1 },
	{ 5,5,4,3,3,3,2,2,2,2,2,1,1,1,1,1 },
	{ 6,5,5,4,3,3,3,3,2,2,2,2,2,2,1,1 },
	{ 6,6,5,5,4,4,3,3,3,3,2,2,2,2,2,2 },
	{ 7,6,5,5,4,4,4,3,3,3,3,2,2,2,2,2 },
	{ 7,6,6,5,5,4,4,4,3,3,3,3,3,2,2,2 },
	{ 7,6,6,5,5,5,4,4,4,3,3,3,3,3,3,2 },
};
PROGMEM const char e3U[16] = { 9, 9, 9, 8, 8, 8, 8, 7, 7, 7, 6, 6, 6, 6, 5, 5 };
PROGMEM const char e3D[16] = { 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 4 };

void setupcore();
void updatecore();
void initialize();
void scoreDisp(int);
void rnd();
void rankChk();
char getsinTBL(byte, byte);
char getcosTBL(byte, byte);
byte getatan2TBL(char, char);

void drawBitmap(char, char, const byte*, byte, byte);
void drawPixel(byte, byte);
void drawLine(byte, byte, byte, byte);
void drawRect(byte, byte, byte, byte);
void fillRect(byte, byte, byte, byte);
#endif
