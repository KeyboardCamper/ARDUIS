#include "gamecore.h"
#include "jiki.h"
#include "shot.h"
#include "ui.h"
#include "arduis_bitmaps.h"

Jiki jiki;
Option option[OPTION_MAX];
extern ShotManager shotManager;
extern Shot shot[SHOT_MAX];
extern Ui ui;

Jiki::Jiki() {
	this->initialize();
	w = 4;
	h = 2;
}

void Jiki::initialize() {
	x = SCREEN_WIDTH / 3;
	y = SCREEN_HEIGHT / 2;
	alive = true;
	hit = false;
	timerPriv = 0;

	gauge = 0;
	playerSpeed = 1;
	shotWait = 0;
	shotTotal = 2;
	optionTotal = 0;
	shotType = SHOT_NORMAL;
	rapidMax = 2;
	barrierAlive = false;
	barrierLife = 0;
	byte i;
	for (i = 0; OPTION_MAX > i; i++) {
		option[i].dead();
	}
}

void Jiki::update() {
	static const byte* bitmaps[] = { player1_1, player1_2, player2_1, player2_2, player3_1, player3_2,
		explosion1_1, explosion1_2, explosion1_3, explosion1_4};
	move = false;
	byte anim = 0;
	if (!hit) {
		if (nowInput & BTN_U) { y -= playerSpeed; move = true; anim = 2; }
		if (nowInput & BTN_D) { y += playerSpeed; move = true; anim = 4; }
		if (nowInput & BTN_L) { x -= playerSpeed; move = true; }
		if (nowInput & BTN_R) { x += playerSpeed; move = true; }

		if (8 >= x) { x = 8; }
		if (x > SCREEN_WIDTH + 8) { x = SCREEN_WIDTH + 8; }
		if (4 >= y) { y = 4; }
		if (y > SCREEN_HEIGHT - 4) { y = SCREEN_HEIGHT - 4; }

		if (nowInput & BTN_A) {
			ui.powerup();
			rankChk();
		}
		if (shotWait) { shotWait--; }
		else {
			if (nowInput & BTN_B) { shotManager.init(); }
		}

		byte i;
		for (i = 0; OPTION_MAX > i; i++) {
			if (option[i].getalive()) { option[i].update(ox[i], oy[i]); }
		}

		if (move) {
			counter = counter % 16;
			if (counter == 15) {
				for (i = OPTION_MAX - 1; i > 0; i--) {
					ox[i] = ox[i - 1];
					oy[i] = oy[i - 1];
				}
				ox[0] = x;
				oy[0] = y;
			}
			counter++;
		}
		drawBitmap(x - 16, y - 4, bitmaps[(frame % 2) + anim], 16, 8);
	}
	else {
		if (32 > timerPriv) {
			framePriv = (timerPriv / 8) % 4;
			timerPriv++;
			drawBitmap(x - 16, y - 4, bitmaps[6 + framePriv], 16, 8);
		}
		else{ this->dead(); }
	}

	shotManager.update();
}

void Jiki::dead() {
	hit = false;
	jikiLife--;
	alive = false;

/*
	if (life == 0) {
		alive = false;
	}

	if (!alive) {
		x = 0;
		y = 0;
		life = 0;
	}
*/
}

void Option::init(byte argumentX, byte argumentY) {
	x = argumentX;
	y = argumentY;
	alive = true;
}

void Option::update(byte argumentX, byte argumentY) {
	if (jiki.getmove()) {
		char directionX = argumentX - x;
		char directionY = argumentY - y;
		byte optionSpeedX = playerSpeed;
		byte optionSpeedY = playerSpeed;

		char signX = (directionX > 0) - (0 > directionX);
		char signY = (directionY > 0) - (0 > directionY);

		if (abs(directionX) == 1) { optionSpeedX = 1; }
		if (abs(directionY) == 1) { optionSpeedY = 1; }

		x += signX * optionSpeedX;
		y += signY * optionSpeedY;
	}
	drawBitmap(x - 16, y - 4, bitmapsOp[frame], 8, 8);
}

void Option::dead() {
	x = 0;
	y = SCREEN_HEIGHT + 8;
	alive = false;
}