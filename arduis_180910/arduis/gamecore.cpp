#include "gamecore.h"
#include "bg.h"
#include "jiki.h"
#include "enemy.h"
#include "shot.h"
#include "stage.h"
#include "collision.h"
#include "ui.h"

Arduboy2Base arduboy;
Title title;
extern StarManager starManager;
extern Jiki jiki;
extern ShotManager shotManager;
StageManager stageManager;
Collision collision;
Ui ui;


byte gameMode;
byte nowInput;
byte prevInput;
bool pressed;
byte stageNum;
byte gameRank;
byte gauge;
byte jikiLife;
byte playerSpeed;
byte shotWait;
byte shotTotal;
byte optionTotal;
byte shotType;
byte rapidMax;
bool barrierAlive;
byte barrierLife;
int score;
byte ox[OPTION_MAX];
byte oy[OPTION_MAX];
byte timer;
byte frame;
byte rndW;
byte rndH;


void setupcore() {
	//arduboy.begin();
	//arduboy.beginNoLogo();
  arduboy.boot();
  arduboy.flashlight();
	arduboy.setFrameRate(60);

}

void updatecore() {
	timer++;
	frame = (timer / 8) % 4;

	rnd();

	prevInput = nowInput;
	nowInput = 0;
	if (arduboy.pressed(UP_BUTTON)) { nowInput |= BTN_U; }
	if (arduboy.pressed(DOWN_BUTTON)) { nowInput |= BTN_D; }
	if (arduboy.pressed(LEFT_BUTTON)) { nowInput |= BTN_L; }
	if (arduboy.pressed(RIGHT_BUTTON)) { nowInput |= BTN_R; }
	if (arduboy.pressed(A_BUTTON)) { nowInput |= BTN_A; }
	if (arduboy.pressed(B_BUTTON)) { nowInput |= BTN_B; }

	if((nowInput & BTN_B) != 0){ pressed = true; }
	else { pressed = false; }

	switch (gameMode) {
	case BOOT:
		initialize();
	case TITLE:
		title.update();
		break;
	case GAME_START:
		title.start();
		starManager.update();
		break;
	case GAME_MAIN:
		ui.update();
		starManager.update();
		jiki.update();
		stageManager.update();
		collision.check();
		break;
	}

	if (!jiki.getalive()) {
		if (jikiLife == 255) {
			gameMode = BOOT;
		}
		else {
			jiki.initialize();
			stageManager.initialize();
			shotManager.initialize();
			timer = 0;
			gameMode = GAME_START;
		}
	}

/*
	starmanager.update();
	jiki.update();
	enemymanager.update();
	collision.check();
	ui.update();

	arduboy.setCursor(0, 56);
	arduboy.print(shot[0].x);
	arduboy.setCursor(16, 56);
	arduboy.print(shot[1].x);
	arduboy.setCursor(32, 56);
	arduboy.print(shot[2].x);
	arduboy.setCursor(48, 56);
	arduboy.print(shot[3].x);
	arduboy.setCursor(64, 56);
	arduboy.print(shot[4].x);
	arduboy.setCursor(80, 56);
	arduboy.print(shot[5].x);
	arduboy.setCursor(96, 56);
	arduboy.print(shot[6].x);
*/
}

void initialize() {
	gameMode = TITLE;
	stageNum = 1;
	gameRank = 0;
	gauge = 0;
	jikiLife = 2;
	playerSpeed = 1;
	shotWait = 0;
	shotTotal = 2;
	optionTotal = 0;
	shotType = SHOT_NORMAL;
	rapidMax = 2;
	barrierAlive = false;
	barrierLife = 0;
	score = 0;
	byte i;
	for (i = 0; OPTION_MAX > i; i++) {
		ox[i] = 0;
		oy[i] = 0;
	}
	jiki.initialize();
	stageManager.initialize();
	shotManager.initialize();
}

void scoreDisp(int num) {
	byte digit = 0;
	byte x;
	int i;

	for (i = 10; num >= i; i *= 10) { digit++; }

	x = 12 + 4 * digit;
	for (i = 0; digit >= i; i++) {
		drawBitmap(x, 0, bitmapsNum[num % 10], 8, 8);
		x -= 4;
		num = num / 10;
	}
}

void rnd() {
	rndW = random(0, SCREEN_WIDTH);
	rndH = random(8, (SCREEN_HEIGHT - 8));
}

void rankChk() {
	gameRank = stageNum + playerSpeed + (shotType * (optionTotal + 1)) + (barrierAlive * 3);
}

char getsinTBL(byte table, byte angle) {
	//32 = 360do
	//sinTbl[i] = (float)sin(2*PI /32*i);
	byte result;
	char sign = 1;
	if (angle >= 16) {
		sign = -1;
		angle -= 16;
	}
	if (8 > angle) { result = pgm_read_byte(&(sinTBL[table][angle])); }
	else if (angle == 8) { result = 1; }
	else{ result = pgm_read_byte(&(sinTBL[table][16 - angle])); }

	return sign * result;
}

char getcosTBL(byte table, byte angle) {
	if (angle >= 24) {
		angle -= 32;
	}
	return getsinTBL(table, angle + 8);
}

byte getatan2TBL(char x, char y) {
	x = x / 8;
	y = y / 8;
	byte n = 0;
	char sign = 1;

	if (0 > x) {
		if (y > 0) {
			sign = -1;
			n = 32;
		}
		else if (y == 0) { return 0; }
	}
	else if (x == 0) {
		if (y > 0) { return 24;	}
		else if (y == 0) { return 0; }
		else { return 8; }
	}
	else {
		n = 16;
		if (0 > y) {
			sign = -1;
		}
		else if (y == 0) { return 16; }
	}
	return n + sign * pgm_read_byte(&(atan2TBL[abs(y) - 1][abs(x) - 1]));
}

void drawBitmap(char x, char y, const byte* bitmap, byte w, byte h) {
	arduboy.drawBitmap(x, y, bitmap, w, h, 1);
}

void drawPixel(byte x, byte y) {
	arduboy.drawPixel(x, y, 1);
}

void drawLine(byte x, byte y, byte x2, byte y2) {
	arduboy.drawLine(x, y, x2, y2, 1);
}

void drawRect(byte x, byte y, byte x2, byte y2) {
	arduboy.drawRect(x, y, x2, y2, 1);
}

void fillRect(byte x, byte y, byte x2, byte y2) {
	arduboy.fillRect(x, y, x2, y2, 1);
}
