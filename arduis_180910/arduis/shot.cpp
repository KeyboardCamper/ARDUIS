#include "gamecore.h"
#include "shot.h"
#include "jiki.h"
#include "ui.h"
#include "arduis_bitmaps.h"

extern Jiki jiki;
extern Option option[OPTION_MAX];
ShotManager shotManager;
Shot shot[SHOT_MAX];
EnemyShot enemyShot[ENEMY_SHOT_MAX];
EnemyShot2 enemyShot2[ENEMY_IONRING_MAX];
BossShot bossShot[4];
Barrier barrier[2];

void ShotManager::initialize() {
	byte i;
	for (i = 0; SHOT_MAX > i; i++) {
		shot[i].dead();
	}
	for (i = 0; ENEMY_SHOT_MAX > i; i++) {
		enemyShot[i].dead();
	}
	for (i = 0; ENEMY_IONRING_MAX > i; i++) {
		enemyShot2[i].dead();
	}
	for (i = 0; 4 > i; i++) {
		bossShot[i].dead();
	}
	for (i = 0; 2 > i; i++) {
		barrier[i].dead();
	}
}

void ShotManager::init() {
	byte i;
	for (i = 0; 5 > i; i++) {
		shotCount[i] = 0;
	}
	for (i = 0; shotTotal > i; i++) {
		if (shot[i].getname() == shotType) {
			shotCount[0] += 1;
		}
		if (shot[i].getname() == shotType * 10) {
			shotCount[1] += 1;
		}
		if (shot[i].getname() == shotType * 10 + 1) {
			shotCount[2] += 1;
		}
		if (shot[i].getname() == shotType * 10 + 2) {
			shotCount[3] += 1;
		}
		if (shot[i].getname() == shotType * 10 + 3) {
			shotCount[4] += 1;
		}
		if (shotType == SHOT_DOUBLE) {
			if (shot[i].getname() == SHOT_NORMAL) {
				shotCount[0] += 1;
			}
			if (shot[i].getname() == SHOT_NORMAL * 10) {
				shotCount[1] += 1;
			}
			if (shot[i].getname() == SHOT_NORMAL * 10 + 1) {
				shotCount[2] += 1;
			}
			if (shot[i].getname() == SHOT_NORMAL * 10 + 2) {
				shotCount[3] += 1;
			}
			if (shot[i].getname() == SHOT_NORMAL * 10 + 3) {
				shotCount[4] += 1;
			}
		}
	}

	switch (shotType) {
	case SHOT_NORMAL:
		shotWait = 8;
		break;
	case SHOT_DOUBLE:
		shotWait = 8;
		shotType = SHOT_NORMAL;
		this->init2();
		shotType = SHOT_DOUBLE;
		break;
	case SHOT_LASER:
		shotWait = 0;
		break;
	}
	this->init2();
}

void ShotManager::init2() {
	byte i, p;
	for (i = 0; shotTotal > i; i++) {
		if (!shot[i].getalive()) {
			if (rapidMax > shotCount[0]) {
				shot[i].init(jiki.getx(), jiki.gety(), shotType);
				break;
			}
		}
	}
	for (p = 0; OPTION_MAX > p; p++) {
		for (i = 0; shotTotal > i; i++) {
			if (option[p].getalive()) {
				if (!shot[i].getalive()) {
					if (rapidMax > shotCount[p + 1]) {
						shot[i].init(option[p].getx() - 8, option[p].gety(), (shotType * 10) + p);
						break;
					}
				}
			}
		}
	}
}

void ShotManager::update() {
	byte i;
	for (i = 0; shotTotal > i; i++) {
		if (shot[i].getalive()) { shot[i].update(); }
		else { shot[i].dead(); }
	}

	if (barrierAlive) {
		if (!barrierLife) {
			barrierLife = BARRIER_LIFE;
			barrier[0].init(4);
			barrier[1].init(60);
		}
		barrier[0].update(jiki.gety() - 4);
		barrier[1].update(jiki.gety() + 4);
	}
}

void ShotManager::enemyShotManager(byte argumentX, byte argumentY) {
	byte i;
	for (i = 0; ENEMY_SHOT_MAX > i; i++) {
		if (!enemyShot[i].getalive()) {
			enemyShot[i].init(argumentX, argumentY);
			break;
		}
	}
}

void ShotManager::enemyShotManager2(byte argumentX, byte argumentY) {
	byte i;
	for (i = 0; ENEMY_IONRING_MAX > i; i++) {
		if (!enemyShot2[i].getalive()) {
			enemyShot2[i].init(argumentX, argumentY);
			break;
		}
	}
}

void Shot::init(byte argumentX, byte argumentY, byte aname) {
	x = argumentX;
	y = argumentY;
	w = 0;
	l = 0;
	laserLength = 127;
	name = aname;
	alive = true;
	hit = false;
	btnRelease = false;
}

void Shot::update() {
	if (name >= 10) { i = name / 10; }
	else { i = name; }

	switch (i) {
	case SHOT_NORMAL:
		Shot::updateN();
		break;
	case SHOT_DOUBLE:
		Shot::updateD();
		break;
	case SHOT_LASER:
		Shot::updateL();
		break;
	}
}

void Shot::updateN() {
	w = 4;
	h = 1;

	x += 4;
	cx = x - 4;
	drawBitmap(x - 8, y - 4, ShotP, 8, 8);

	if (x > SCREEN_WIDTH + 8) { this->dead(); }

	if (hit) {
		hit = false;
		alive = false;
	}
}

void Shot::updateD() {
	w = 4;
	h = 1;

	x += 4;
	y -= 4;
	cx = x - 4;
	drawBitmap(x - 8, y - 4, ShotP2, 8, 8);

	if (x > SCREEN_WIDTH + 8) { this->dead(); }

	if (hit) {
		hit = false;
		alive = false;
	}
}

void Shot::updateL() {
	h = 1;
	if (!btnRelease) {
		l += 4;
		switch (name) {
		case SHOT_LASER:
			x = jiki.getx() + 8;
			break;
		case SHOT_LASER * 10:
			x = option[0].getx() - 8;
			break;
		case SHOT_LASER * 10 + 1:
			x = option[1].getx() - 8;
			break;
		case SHOT_LASER * 10 + 2:
			x = option[2].getx() - 8;
			break;
		case SHOT_LASER * 10 + 3:
			x = option[3].getx() - 8;
			break;
		}
		if (l > laserLength) { btnRelease = true; }
	}
	else{
		x += 4;
	}
	if (!pressed) { btnRelease = true; }

	if (SCREEN_WIDTH > x) {
		switch (name) {
		case SHOT_LASER:
			y = jiki.gety();
			break;
		case SHOT_LASER * 10:
			y = option[0].gety();
			break;
		case SHOT_LASER * 10 + 1:
			y = option[1].gety();
			break;
		case SHOT_LASER * 10 + 2:
			y = option[2].gety();
			break;
		case SHOT_LASER * 10 + 3:
			y = option[3].gety();
			break;
		}
	}
	else {
		y = SCREEN_HEIGHT + 8;
	}

	if (255 >= laserLength && laserLength > 127) {
		l = 0;
		alive = false;
	}

	w = l / 2;
	cx = x + w;
	drawLine(x, y, x + l, y);

	if (x > 248) {	this->dead(); }

	if (hit) {
		laserLength -= 4;
		l -= 4;
		hit = false;
	}
}

void Shot::dead() {
	x = 0;
	y = SCREEN_HEIGHT + 8;
	cx = 0;
	w = 0;
	h = 0;
	l = 0;
	name = 0;
	alive = false;
}

byte Shot::getx(bool type) const {
	if (type) {
		if (name == SHOT_LASER) {
			return x + l;
		}
	}
	return cx;
}

byte Shot::getw(bool type) const {
	if (type) {
		if (name == SHOT_LASER) {
			return 1;
		}
	}
	return w;
}
byte Shot::geth(bool type) const {
	if (type) {
		if (name == SHOT_LASER) {
			return 1;
		}
	}
	return h;
}

void EnemyShot::init(byte argumentX, byte argumentY) {
	x = argumentX;
	y = argumentY;
	argumentX = x - jiki.getx();
	argumentY = y - jiki.gety();
	angle = getatan2TBL(argumentX, argumentY);
	w = 2;
	alive = true;
	hit = false;
}

void EnemyShot::update() {
	if (alive) {
		x += getcosTBL(timer % 4, angle);
		y += getsinTBL(timer % 4, angle);

		drawBitmap(x - 8, y - 4, ShotE, 8, 8);

		if (x > SCREEN_WIDTH + 8 || y > SCREEN_HEIGHT + 8) { alive = false; }
	}
	else {
		this->dead();
	}

	if (hit) {
		hit = false;
		alive = false;
	}
}

void EnemyShot::dead() {
	x = 0;
	y = SCREEN_HEIGHT + 8;
	w = 0;
	alive = false;
}

void EnemyShot2::init(byte argumentX, byte argumentY) {
	x = argumentX;
	y = argumentY;
	argumentX = x - jiki.getx();
	argumentY = y - jiki.gety();
	angle = getatan2TBL(argumentX, argumentY);
	w = 4;
	alive = true;
	hit = false;
	timerPriv = 0;
}

void EnemyShot2::update() {
	if (alive) {
		x += getcosTBL(timer % 4, angle);
		y += getsinTBL(timer % 4, angle);

		drawBitmap(x - 8, y - 4, ShotE2, 8, 8);

		if (x > SCREEN_WIDTH + 8 || y > SCREEN_HEIGHT + 8) { alive = false; }
	}
	else {
		if (32 > timerPriv) {
			framePriv = (timerPriv / 8) % 4;
			timerPriv++;
			drawBitmap(x - 8, y - 4, bitmapsB1[framePriv], 8, 8);
		}
		else {
			this->dead();
		}
	}

	if (hit) {
		score++;
		hit = false;
		timerPriv = 0;
		alive = false;
	}
}

void EnemyShot2::dead() {
	x = 0;
	y = SCREEN_HEIGHT + 8;
	w = 0;
	timerPriv = 255;
	alive = false;
}

void BossShot::init(byte argumentX, byte argumentY) {
	x = argumentX;
	y = argumentY;
	w = 6;
	h = 2;
	alive = true;
}

void BossShot::update() {
	if (alive) {
		x -= 2;
		drawBitmap(x - 12, y - 2, ShotB, 12, 8);

		if (x > 255 - 12) { alive = false;	}
	}
	else {
		this->dead();
	}

	if (hit) {
		hit = false;
	}
}

void BossShot::dead() {
	x = 0;
	y = SCREEN_HEIGHT + 8;
	w = 0;
	h = 0;
	alive = false;
}

void Barrier::init(byte argumentY) {
	x = 136;
	y = argumentY;
	w = 4;
	alive = true;
	moveEnd = false;
}

void Barrier::update(byte argumentY) {
	static const byte* bitmaps[] = { Barrier_1, Barrier_2 };

	byte cy = argumentY;
	if (!moveEnd) {
		char directionX = jiki.getx() + 16 - x;
		char directionY = cy - y;
		if (directionX > 0) { x++; }
		else if (0 > directionX) { x--; }
		if (directionY > 0) { y++; }
		else if (0 > directionY) { y--; }
		if (x == jiki.getx() + 16 && y == cy) {
			moveEnd = true;
		}
	}
	else {
		x = jiki.getx() + 16;
		y = cy;
	}

	drawBitmap(x - 8, y - 4, bitmaps[frame % 2], 8, 8);

	if (hit) {
		barrierLife--;
		hit = false;
	}
	if (barrierLife == 255 || barrierLife == 0) {
		this->dead();
	}
}

void Barrier::dead() {
	x = 0;
	y = SCREEN_HEIGHT + 8;
	w = 0;
	barrierLife = 0;
	alive = false;
	barrierAlive = false;
	moveEnd = false;
}