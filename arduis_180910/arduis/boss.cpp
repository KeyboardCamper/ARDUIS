#include "gamecore.h"
#include "boss.h"
#include "shot.h"
#include "arduis_bitmaps.h"

Boss boss;
BossU bossU;
BossD bossD;
BossCore bossCore;
BossExplosion bossExp[6];
extern BossShot bossShot[4];
extern ShotManager shotManager;

void Boss::initialize() {
	this->dead();
	bossCore.dead();
}

void Boss::init() {
	w = 20;
	h = 12;
	x = 88;
	y = 80;
	moveEnd = 0;
	wait = 0;
	timerPriv = 0;
	timer = 0;
	alive = true;

	bossCore.init();
	byte i;
	for (i = 0; 6 > i; i++) { bossExp[i].clear(); }
}

void Boss::update() {
	byte i;
	if (bossCore.getalive()) {
		if (!moveEnd) {
			this->appearance();
		}
		else {
			this->attack();
		}

		cx = x - 24;
		drawBitmap(x - 44, y - 4, bossBase, 44, 8);
		bossCore.update();
	}
	else {
		if (64 > timerPriv) {
			if (timerPriv == 32){
				score += 100;
				timer = 0;
				if (stageNum > 3) {
					shotManager.enemyShotManager(cx, y);
				}
			}
			if (64 > timerPriv && timerPriv > 31) {
				framePriv = (timerPriv / 8) % 4;				
				drawBitmap(x - 32, y - 8, bitmapsB2[framePriv], 16, 16);
				alive = false;
			}
			else {
				drawBitmap(x - 44, y - 4, bossBase, 44, 8);
			}
			timerPriv++;
		}
		else {
			this->dead();
		}
	}
	bossU.update();
	bossD.update();
	for (i = 0; 6 > i; i++) { bossExp[i].update(); }
	for (i = 0; 6 > i; i++) { bossShot[i].update(); }
}

void Boss::appearance() {
	bool frameSkip = timer % 2;
	if (frameSkip) {
		if (y != 32) { y--; }
	}
	else {
		if (y == 32) {
			if (120 != x) { x++; }
			else { wait++; }
		}
	}
	if (wait > 24) { moveEnd = true; wait = 0; }
}

void Boss::attack() {
	if (wait == 40) { muki = rndW % 2; wait = 0; }
	if (wait == 32) {
		if (!bossShot[0].getalive()) {
			bossShot[0].init(x - 24, y - 14);
			bossShot[1].init(x - 36, y - 6);
			bossShot[2].init(x - 36, y + 6);
			bossShot[3].init(x - 24, y + 14);
		}

	}
	if (24 > wait) {
		if (muki) { y++; }
		else { y--; }
		if (8 > y) { y = 8; }
		if (y > 56) { y = 56; }
	}
	wait++;
}

void Boss::dead() {
	x = 88;
	cx = x - 24;
	y = 80;
	alive = false;
}

void BossU::update() {
	if (boss.getalive()) {
		w = 20;
		h = 6;
		x = boss.getx();
		y = boss.gety() - 10;
		drawBitmap(x - 24, y - 6, bossBaseU, 48, 16);
	}
	else {
		x = 0;
		y = 0;
		w = 0;
		h = 0;
	}
}

void BossD::update() {
	if (boss.getalive()) {
		w = 20;
		h = 6;
		x = boss.getx();
		y = boss.gety() + 10;
		drawBitmap(x - 24, y - 6, bossBaseD, 48, 16);
	}
	else {
		x = 0;
		y = 0;
		w = 0;
		h = 0;
	}
}

void BossCore::initialize() {
	this->dead();
}

void BossCore::init() {
	w = 4;
	h = 4;
	life = 24;
	lifed = life / 6;
	counter = 0;
	alive = true;
}

void BossCore::update() {
	static const byte* bitmaps[] = { bossCore_1, bossCore_2, bossCore_3,
							  bossCore_4, bossCore_5, bossCore_6 };
	if (alive) {
		x = boss.getx() + 4;
		y = boss.gety();

		byte i, p;
		for (i = 0; 6 > i; i++) {
			if (lifed * (6 - i) >= life && life > lifed * (5 - i)) {
				p = i;
				cx = x - 23 + (i * 2);
				if (i == 5) { cx = x - 4; }
			}
			if (lifed * (5 - i) == life && (bossExp[i].getalive())) {
				bossExp[i].init(cx + 4, y);
				if (stageNum > 3) {
					shotManager.enemyShotManager(cx, y);
				}
			}
		}		

		drawBitmap(x - 24, y - 4, bitmaps[p], 24, 8);

		}
		else {
			if (32 > counter) {
				counter++;
			}
			else {
				this->dead();
			}
		}

	if (boss.getMoveEnd() && hit) {
		life--;
		counter++;
		if (3 > counter && counter > 0) {
			life++;
		}
		else {
			counter = 0;
			hit = false;
		}

		if(life==0){
			counter = 0;
			bossExp[5].init(cx + 4, y);
			alive = false;
		}
	}
}

void BossCore::dead() {
	x = 0;
	cx = x - 23;
	y = 0;
	alive = false;
}

void BossExplosion::clear() {
	x = 0;
	y = 0;
	timerPriv = 0;
	alive = true;
}

void BossExplosion::init(byte argumentX, byte argumentY) {
	x = argumentX;
	y = argumentY;
	alive = false;
}

void BossExplosion::update() {
	if (!alive) {
		if (32 > timerPriv) {
			if(timerPriv ==0){ score++; }
			framePriv = (timerPriv / 8) % 4;
			timerPriv++;
			drawBitmap(x - 8, y - 4, bitmapsB1[framePriv], 8, 8);
		}
		else {
			x = 0;
			y = 0;
			alive = true;
		}
	}
}