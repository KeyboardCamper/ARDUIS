#include "gamecore.h"
#include "enemy.h"
#include "shot.h"
#include "jiki.h"
#include "stage.h"
#include "arduis_bitmaps.h"

Capsule capsule;
extern ShotManager shotManager;
extern Jiki jiki;
extern StageManager stageManager;

void Enemy::initialize() {
	this->dead();
}

void Enemy::init() {
	if (stageNum > 5) {
		this->initE2();
		return;
	}
	switch (stageNum % 3) {
	case 0:
	case 1:
		this->initE1();
		break;
	case 2:
		this->initE2();
		break;
	}
}

void Enemy::update() {
	if (timerPriv == 128) {
		score++;
		if (!capsule.getalive()) { capsule.init(x - 4, y); }
		if (stageNum > 3) { shotManager.enemyShotManager(x - 4, y); }
		timerPriv = 255 - 32;
	}
	else if (timerPriv == 255) {
		this->dead();
	}
	else if (timerPriv > 128) {
		framePriv = (timerPriv / 8) % 4;
		timerPriv++;
		drawBitmap(x - 8, y - 4, bitmapsB1[framePriv], 8, 8);
	}
	else {
		this->update2();
	}

	if (x > SCREEN_WIDTH + 8)  {
		this->dead();
	}
}

void Enemy::update2() {
	if (stageNum > 5) {
		this->updateE2();
		return;
	}
	switch (stageNum % 3) {
	case 0:
	case 1:
		this->updateE1();
		if (x == 112) {
			if (gameRank > 9) {
				shotManager.enemyShotManager(x - 4, y);
			}
		}
		break;
	case 2:
		this->updateE2();
		break;
	}
}

void Enemy::dead() {
	x = 0;
	y = SCREEN_HEIGHT + 8;
	w = 0;
	timerPriv = 0;
}

void Enemy::initE1() {
	x = SCREEN_WIDTH + 8;
	y = rndH;
	w = 4;
	timerPriv = 64;
	framePriv = 0;
}

void Enemy::initE2() {
	x = rndW / 8 * 8 + 8;
	if (x > SCREEN_WIDTH) { x = 120; }
	y = rndH / 8 * 8 + 4;
	timerPriv = 0;
}

void Enemy::updateE1() {
	if (timer % 2) {
		y += pgm_read_byte(&(f[framePriv]));
		framePriv = (framePriv + 1) % 34;
	}
	x--;
	drawBitmap(x - 8, y - 4, bitmapsE1[frame], 8, 8);
}

void Enemy::updateE2() {
	if (24 > timerPriv) {
		if (timer % 2) { timerPriv++; }
		w = 0;
		framePriv = (timerPriv / 8) % 4;
	}
	else {
		if (timerPriv == 24) {
			w = 4;
			angle = getatan2TBL(x - jiki.getx(), y - jiki.gety());
			timerPriv = 64;
		}
		x += getcosTBL(timer % 4, angle);
		y += getsinTBL(timer % 4, angle);
	}

	drawBitmap(x - 8, y - 4, bitmapsE2[framePriv], 8, 8);

	if (y > SCREEN_HEIGHT + 4) {
		this->dead();
	}
}

bool Enemy::getalive() const {
	if (timerPriv == 64) { return true; }
	return false;
}

void MapObj::initialize() {
	this->dead();
}

void MapObj::init(byte aparts) {
	parts = aparts;
	switch (stageNum % 3) {
	case 1:
		this->initS1();
		break;
	case 2:
		this->initS2();
		break;
	case 0:
		this->initS3();
		break;
	}
	hit = false;
	timerPriv = 0;
}

void MapObj::update() {
	if (timerPriv != 255 && timer % 2) {
			x--;
		}

	switch (stageNum % 3) {
	case 1:
		this->updateS1();
		break;
	case 2:
		this->updateS2();
		break;
	case 0:
		this->updateS3();
		break;
	}
	if (x > 255 - 8) {
		switch (parts) {
		case 0:
			stageManager.setobjTimerD();
			break;
		case 3:
			stageManager.setobjTimerU();
			break;
		}
		this->dead();
	}
}

void MapObj::dead() {
	x = 0;
	y = SCREEN_HEIGHT + 64;
	cx = 0;
	w = 0;
	h = 0;
	timerPriv = 255;
	alive = false;
}

void MapObj::initS1() {
	switch (parts) {
	case 0:
		x = stageManager.getObjRxD();
		y = stageManager.getObjRyD();
		w = 10;
		h = 6;
		alive = true;
		break;
	case 1:
		x = stageManager.getObjRxD() - 4;
		y = stageManager.getObjRyD() -10;
		w = 6;
		h = 4;
		alive = true;
		break;
	case 2:
		alive = false;
		break;
	case 3:
		x = stageManager.getObjRxU();
		y = stageManager.getObjRyU();
		w = 10;
		h = 6;
		alive = true;
		break;
	case 4:
		x = stageManager.getObjRxU() - 4;
		y = stageManager.getObjRyU() + 10;
		w = 6;
		h = 4;
		alive = true;
		break;
	case 5:
		alive = false;
		break;
	}
	type = TYPE_MUTEKI;
}

void MapObj::updateS1() {
	switch (parts) {
	case 0:
		cx = x - 14;
		drawBitmap(x - 32, y - 6, mountain1_1, 32, 16);
		break;
	case 1:
		cx = x - 10;
		drawBitmap(x - 20, y - 4, mountain1_2, 20, 8);
		break;
	case 2:
		break;
	case 3:
		cx = x - 14;
		drawBitmap(x - 32, y - 6, mountain2_1, 32, 16);
		break;
	case 4:
		cx = x - 10;
		drawBitmap(x - 20, y - 4, mountain2_2, 20, 8);
		break;
	case 5:
		break;
	}
	if (hit) { hit = false; }
}

void MapObj::initS2() {
	switch (parts) {
	case 0:
		x = stageManager.getObjRxD();
		y = stageManager.getObjRyD();
		w = 16;
		h = 2;
		alive = true;
		type = TYPE_MUTEKI;
		break;
	case 1:
		x = stageManager.getObjRxD() - 20 + ((timer % 3) * 8);
		if (timer % 3 == 2) { x = stageManager.getObjRxD() - 12; }
		y = stageManager.getObjRyD() + 6;
		w = 4;
		h = 4;
		alive = true;
		type = TYPE_NORMAL;
		break;
	case 2:
		if (timer % 3 != 2) {
			x = stageManager.getObjRxD() - 4;
			y = stageManager.getObjRyD() + 6;
		}
		else {
			x = stageManager.getObjRxD() - 20;
			y = stageManager.getObjRyD() - 6;
		}
		w = 4;
		h = 4;
		alive = true;
		type = TYPE_NORMAL;
		break;
	case 3:
		x = stageManager.getObjRxU();
		y = stageManager.getObjRyU();
		w = 16;
		h = 2;
		alive = true;
		type = TYPE_MUTEKI;
		break;
	case 4:
		x = stageManager.getObjRxU() - 20 + ((timer % 3) * 8);
		if (timer % 3 == 1) { x = stageManager.getObjRxU() - 20; }
		y = stageManager.getObjRyU() - 6;
		w = 4;
		h = 4;
		alive = true;
		type = TYPE_NORMAL;
		break;
	case 5:
		x = stageManager.getObjRxU() - 12 + ((timer % 3) * 8);
		y = stageManager.getObjRyU() - 6;
		if (timer % 3 == 2) {
			x = stageManager.getObjRxU() - 20;
			y = stageManager.getObjRyU() + 6;
		}
		w = 4;
		h = 4;
		alive = true;
		type = TYPE_NORMAL;
		break;
	}
}

void MapObj::updateS2() {
	if (timer % 8) {
		angle = getatan2TBL(x - jiki.getx(), y - jiki.gety());
		i = angle;
		if (angle == 16) { i = 15; }
		else if (angle > 16) { i = 32 - angle; }
	}
	switch (parts) {
	case 0:
	case 3:
		cx = x - 16;
		drawBitmap(x - 32, y - 2, stage2Jimen, 32, 8);
		if (hit) { hit = false; }
		break;
	case 1:
	case 2:
		if (stageManager.getObjRyD() - y > 0) {
			this->updateS2EnemyU();
		}
		else {
			this->updateS2EnemyD();
		}
		break;
	case 4:
	case 5:
		if (stageManager.getObjRyU() - y > 0) {
			this->updateS2EnemyU();
		}
		else {
			this->updateS2EnemyD();
		}
		break;
	}
}

void MapObj::updateS2EnemyU() {
	if (alive) {
		if (gameRank > 9) {
			if (x == 112) {
				if (angle > 15 && timer % 2) {
					shotManager.enemyShotManager(x - 4, y);
				}
			}
		}
		if (gameRank > 17) {
			if (x == 64) {
				if (angle > 15 && timer % 2) {
					shotManager.enemyShotManager(x - 4, y);
				}
			}
		}
		cx = x - 4;
		drawBitmap(x - 8, y - 4, bitmapsE3[pgm_read_byte(&(e3U[i]))], 8, 8);
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
		if (!capsule.getalive()) {
			capsule.init(x - 4, y);
		}
	}
}
void MapObj::updateS2EnemyD() {
	if (alive) {
		if (gameRank > 9) {
			if (x == 112) {
				if (angle > 15 && timer % 2) {
					shotManager.enemyShotManager(x - 4, y);
				}
			}
		}
		if (gameRank > 17) {
			if (x == 64) {
				if (angle > 15 && timer % 2) {
					shotManager.enemyShotManager(x - 4, y);
				}
			}
		}
		cx = x - 4;
		drawBitmap(x - 8, y - 4, bitmapsE3[pgm_read_byte(&(e3D[i]))], 8, 8);
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
		if (!capsule.getalive()) {
			capsule.init(x - 4, y);
		}
	}
}

void MapObj::initS3() {
	switch (parts) {
	case 0:
		x = stageManager.getObjRxD();
		y = stageManager.getObjRyD();
		w = 16;
		h = 2;
		alive = true;
		type = TYPE_MUTEKI;
		break;
	case 1:
		x = stageManager.getObjRxD();
		if (26 > stageManager.getObjRyD()) {
			y = stageManager.getObjRyD() + 14;
			n = 2;
		}
		else if (!(timer % 3)){
			y = stageManager.getObjRyD() - 10;
			n = 0;
		}
		else {
			y = stageManager.getObjRyD() + 14;
			n = 2;
		}
		w = 6;
		h = 8;
		alive = true;
		type = TYPE_NORMAL;
		break;
	case 2:
		x = stageManager.getObjRxD();
		if (26 > stageManager.getObjRyD()) {
			y = stageManager.getObjRyD() + 7;
			n = 2;
		}
		else if (!(timer % 3)) {
			y = stageManager.getObjRyD() - 7;
			n = 0;
		}
		else {
			y = stageManager.getObjRyD() + 7;
			n = 2;
		}
		life = 6;
		w = 4;
		h = 4;
		alive = true;
		type = TYPE_NORMAL;
		break;
	case 3:
		x = stageManager.getObjRxU();
		y = stageManager.getObjRyU();
		w = 16;
		h = 2;
		alive = true;
		type = TYPE_MUTEKI;
		break;
	case 4:
		x = stageManager.getObjRxU();
		if (stageManager.getObjRyU() > 38) {
			y = stageManager.getObjRyU() - 10;
			n = 0;
		}
		else if (!(timer % 3)) {
			y = stageManager.getObjRyU() - 10;
			n = 0;
		}
		else {
			y = stageManager.getObjRyU() + 14;
			n = 2;
		}
		w = 6;
		h = 8;
		alive = true;
		type = TYPE_NORMAL;
		break;
	case 5:
		x = stageManager.getObjRxU();
		if (stageManager.getObjRyU() > 38) {
			y = stageManager.getObjRyU() - 7;
			n = 0;
		}
		else if (!(timer % 3)) {
			y = stageManager.getObjRyU() - 7;
			n = 0;
		}
		else {
			y = stageManager.getObjRyU() + 7;
			n = 2;
		}
		life = 6;
		w = 4;
		h = 4;
		alive = true;
		type = TYPE_NORMAL;
		break;
	}
}

void MapObj::updateS3() {
	if (timer % 8) {
		angle = getatan2TBL(x - jiki.getx(), y - jiki.gety());
		i = angle;
		if (angle == 16) { i = 15; }
		else if (angle > 16) { i = 32 - angle; }
	}
	switch (parts) {
	case 0:
	case 3:
		cx = x - 16;
		drawBitmap(x - 32, y - 2, stage3Jimen, 32, 8);
		if (hit) { hit = false; }
		break;
	case 1:
		if (alive) {
			if (!stageManager.getFlagD()) {
				cx = x - 12;
				drawBitmap(x - 24, y - 12, bitmapsE4[0 + n], 24, 24);
			}
			else {
				cx = x - 14;
				w = 6;
				h = 2;
				if (!n) { y = stageManager.getObjRyD() - 4; }
				else { y = stageManager.getObjRyD() + 4; }
				drawBitmap(x - 20, y - 2, bitmapsE4[1 + n], 16, 8);
			}
		}
		break;
	case 2:
	case 5:
		this->updateS3EnemyMouth();
		break;
	case 4:
		if (alive) {
			if (!stageManager.getFlagU()) {
				cx = x - 12;
				drawBitmap(x - 24, y - 12, bitmapsE4[0 + n], 24, 24);
			}
			else {
				cx = x - 14;
				w = 6;
				h = 2;
				if (!n) { y = stageManager.getObjRyU() - 4; }
				else { y = stageManager.getObjRyU() + 4; }
				drawBitmap(x - 20, y - 2, bitmapsE4[1 + n], 16, 8);
			}
		}
		break;
	}
}

void MapObj::updateS3EnemyMouth() {
	if (alive) {
		char distX = cx - jiki.getx();
		char distY = y - jiki.gety();
		if (64 > distX && distX > 0) {
			if (distY + 8 > 0 && n == 0) {
				this->updateS3EnemyShot();
			}
			if (0 > distY - 8 && n == 2) {
				this->updateS3EnemyShot();
			}
		}
		else {
			timerPriv = 0;
			framePriv = 0;
			if (hit) { hit = false; }
		}
		cx = x - 20;
		drawBitmap(x - 24, y - 4, bitmapsE4_2[framePriv + n], 8, 8);
	}
	else {
		if (32 > timerPriv) {
			framePriv = (timerPriv / 8) % 4;
			timerPriv++;
			drawBitmap(x - 20, y - 8, bitmapsB2[framePriv], 16, 16);
		}
		else {
			this->dead();
		}
	}
}

void MapObj::updateS3EnemyShot() {
	if (32 > timerPriv) {
		framePriv = 1;
		if (10 > gameRank) {
			if (!(timerPriv % 24)) {
				shotManager.enemyShotManager2(cx, y);
			}
		}
		else {
			if (!(timerPriv % 12)) {
				shotManager.enemyShotManager2(cx, y);
			}
		}
		if (hit) {
			life--;
			hit = false;
			if (!life) {
				score += 10;
				timerPriv = 0;
				alive = false;
			}
		}
	}
	else if (40 > timerPriv) {
		framePriv = 0;
		if (hit) { hit = false; }
	}
	else {
		timerPriv = 0;
	}
	timerPriv++;
}

void Capsule::initialize() {
	x = 0;
	y = SCREEN_HEIGHT + 8;
	w = 0;
	alive = false;
}

void Capsule::init(byte argumentX, byte argumentY) {
	x = argumentX + 4;
	y = argumentY;
	w = 4;
	alive = true;
	hit = false;
}

void Capsule::update() {
	const byte* bitmaps[] = { capsule_1, capsule_2 };
	if (alive) {
		if (timer % 2) {
			x--;
		}
		drawBitmap(x - 8, y - 4, bitmaps[frame % 2], 8, 8);

		if (x > 255 - 8) { alive = false; }
	}
	else {
		x = 0;
		y = SCREEN_HEIGHT + 8;
		w = 0;
	}

	if (hit) {
		score++;
		gauge++;
		if (gauge > 5) {
			gauge = 1;
		}
		hit = false;
		alive = false;
	}
}