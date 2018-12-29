#include "gamecore.h"
#include "bg.h"


StarManager starManager;
Star star[STAR];

void Title::update() {
	static const byte* bitmaps[] = { title_1, title_2, title_3, title_4, title_5, title_6,
		title_7, title_8, title_9, title_10, title_11, title_12, title_13, title_14 };

	timerPriv = (timerPriv + 1) % 8;
	if (15 > p) {
		if (!timerPriv) {
			p++;
		}
	}
	else {
		if (nowInput) {
			timer = 0;
			timerPriv = 0;
			p = 0;
			gameMode = GAME_START;
		}
	}

	byte i;
	for (i = 0; p > i; i++) {
		if (12 > i) {
			drawBitmap(32 * (i % 4), 8 + 8 * (i / 4), bitmaps[i], 32, 8);
		}
		else if (i > 12) {
			drawBitmap(32 * (i % 4), 8 + 8 * (i / 4), bitmaps[i - 1], 32, 8);
		}
	}

	drawBitmap(40, 40, title_15, 24, 8);
	drawBitmap(64, 40, title_16, 24, 8);
	drawBitmap(36, 56, title_17, 56, 8);
}

void Title::start() {
	drawBitmap(52, 26, title_16, 24, 8);

	drawBitmap(0, 0, scoreIcon, 8, 8);
	scoreDisp(score);

	drawBitmap(0, 5, lifeIcon, 8, 8);
	drawBitmap(12, 5, bitmapsNum[jikiLife], 8, 8);

	if (timer == 32) {
		timer = 0;
		gameMode = GAME_MAIN;
	}
}

void StarManager::init() {
	byte i;
	for (i = 0; STAR > i; i++) {
		star[i].type = i % 3;
		star[i].init();
	}
	set = true;
}

void StarManager::update() {
	if (!set) { starManager.init(); }

	byte i;
	for (i = 0; STAR > i; i++) {
		star[i].update();
	}
}

void Star::init() {
	rnd();
	x = rndW;
	y = rndH;
}

void Star::update() {
	switch (type) {
	case 0:
		if (timer % 2) {
			x--;
		}
		break;
	case 1:
		x--;
		break;
	case 2:
		x -= 2;
		break;
	}

	drawPixel(x, y);

	if (x > 255 - 4) {
		x = SCREEN_WIDTH;
		y = rndH;
	}
}

