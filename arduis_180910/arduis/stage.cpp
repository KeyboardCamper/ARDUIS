#include "gamecore.h"
#include "stage.h"
#include "enemy.h"
#include "boss.h"
#include "shot.h"

Enemy enemy;
MapObj mapObj[MAPOBJ_MAX];
extern Capsule capsule;
extern EnemyShot enemyShot[ENEMY_SHOT_MAX];
extern EnemyShot2 enemyShot2[ENEMY_IONRING_MAX];
extern Boss boss;
extern BossShot bossShot[4];

void StageManager::initialize() {
	capsule.initialize();
	enemy.initialize();
	byte i;
	for (i = 0; MAPOBJ_MAX > i; i++) {
		mapObj[i].initialize();
	}
	boss.initialize();
	stageTimer = 0;
	boss_set = false;
}

void StageManager::update() {
	if (!timer) { stageTimer++; }
	if (!stageTimer) {
		this->setup();
	}

	if (stageTimer > 0 && STAGE_LIMIT >= stageTimer) {
		this->stage();
	}

	if (stageTimer > STAGE_LIMIT + 1) {
		this->boss_stage();
	}

	enemy.update();
	byte i;
	for (i = 0; ENEMY_SHOT_MAX > i; i++) { enemyShot[i].update(); }
	if (!(stageNum % 3)) {
		for (i = 0; ENEMY_IONRING_MAX > i; i++) { enemyShot2[i].update(); }
		if (!mapObj[2].getalive() && mapObj[0].getalive()) { flagD = true; }
		if (!mapObj[5].getalive() && mapObj[3].getalive()) { flagU = true; }
	}
	capsule.update();

	for (i = 0; MAPOBJ_MAX > i; i++) {
		mapObj[i].update();
	}
}

void StageManager::setup(){
	objTimerD = 0;
	objTimerU = ((rndW % 8) * 8) + 184;	//zurasu
	rankChk();

	enemyTimer = 96;
	if (6 > stageNum) {
		switch (stageNum % 3) {
		case 0:
		case 1:
			enemyTimer = 64;
			break;
		case 2:
			enemyTimer = 128;
			break;
		}
	}
}

void StageManager::stage() {
	if (timer % enemyTimer == 0) {
		if (!enemy.getalive()) {
			enemy.init();
		}
	}

	byte TimerDtmp;
	byte TimerUtmp;
	if (objTimerD > 128) { TimerDtmp = objTimerD - 255; }
	else { TimerDtmp = objTimerD; }
	if (objTimerU > 128) { TimerUtmp = objTimerU - 255; }
	else { TimerUtmp = objTimerU; }

	byte i;
	if (timer == objTimerD) {
		if (mapObj[3].getalive()) {
			if (!mapObj[0].getalive()) {
				switch (stageNum % 3) {
				case 1:
					flagD = false;
					objRxD = SCREEN_WIDTH + 32;
					objRyD = SCREEN_HEIGHT - 10;
					for (i = 0; MAPOBJ_MAX - 3 > i; i++) {
						mapObj[i].init(i);
					}
					break;
				case 2:
					flagD = false;
					objRxD = SCREEN_WIDTH + 32;
					objRyD = (rndH / 16) * 8 + 2;
					if (objRyD == 2) { objRyD = 18; }
					for (i = 0; MAPOBJ_MAX - 3 > i; i++) {
						mapObj[i].init(i);
					}
					break;
				case 0:
					if (72 > TimerDtmp - TimerUtmp) {
						objTimerD = objTimerU + 128;
					}
					else {
						flagD = false;
						objRxD = SCREEN_WIDTH + 32;
						objRyD = (rndH / 16) * 8 + 2;
						if (objRyD == 2) { objRyD = 10; }
						for (i = 0; MAPOBJ_MAX - 3 > i; i++) {
							mapObj[i].init(i);
						}
						break;
					}
					break;
				}
			}
		}
		else {
			if (!mapObj[0].getalive()) {
				if (TimerDtmp == TimerUtmp) {
					switch (stageNum % 3) {
					case 1:
						if (timer % 3) {
							objTimerU += 64;
						}
						else {
							flagD = false;
							objRxD = SCREEN_WIDTH + 32;
							objRyD = SCREEN_HEIGHT - 10;
							for (i = 0; MAPOBJ_MAX - 3 > i; i++) {
								mapObj[i].init(i);
							}
						}
						break;
					case 2:
						if (timer % 3) {
							objTimerU += 64;
						}
						else {
							flagD = false;
							objRxD = SCREEN_WIDTH + 32;
							objRyD = (rndH / 16) * 8 + 2;
							if (objRyD == 2) { objRyD = 18; }
							for (i = 0; MAPOBJ_MAX - 3 > i; i++) {
								mapObj[i].init(i);
							}
						}
						break;
					case 0:
						objTimerU = objTimerD + 128;
						break;
					}
				}
				else {
					flagD = false;
					switch (stageNum % 3) {
					case 1:
						objRxD = SCREEN_WIDTH + 32;
						objRyD = SCREEN_HEIGHT - 10;
						break;
					case 2:
						objRxD = SCREEN_WIDTH + 32;
						objRyD = (rndH / 16) * 8 + 2;
						if (objRyD == 2) { objRyD = 18; }
						break;
					case 0:
						objRxD = SCREEN_WIDTH + 32;
						objRyD = (rndH / 16) * 8 + 2;
						if (objRyD == 2) { objRyD = 10; }
						break;
					}
					for (i = 0; MAPOBJ_MAX - 3 > i; i++) {
						mapObj[i].init(i);
					}
				}
			}
		}
	}

	if (timer == objTimerU) {
		if (mapObj[0].getalive()) {
			if (!mapObj[3].getalive()) {
				switch (stageNum % 3) {
				case 1:
					flagU = false;
					objRxU = SCREEN_WIDTH + 32;
					objRyU = 6;
					for (i = 3; MAPOBJ_MAX > i; i++) {
						mapObj[i].init(i);
					}
					break;
				case 2:
					flagU = false;
					objRxU = SCREEN_WIDTH + 32;
					objRyU = (rndH / 16) * 8 + 30;
					if (objRyU == 30) { objRyU = 46; }
					for (i = 3; MAPOBJ_MAX > i; i++) {
						mapObj[i].init(i);
					}
					break;
				case 0:
					if (72 > TimerUtmp - TimerDtmp) {
						objTimerU = objTimerD + 128;
					}
					else {
						flagU = false;
						objRxU = SCREEN_WIDTH + 32;
						objRyU = (rndH / 16) * 8 + 30;
						if (objRyU == 30) { objRyU = 54; }
						for (i = 3; MAPOBJ_MAX > i; i++) {
							mapObj[i].init(i);
						}
					}
					break;
				}
			}
		}
		else {
			if (!mapObj[3].getalive()) {
				switch (stageNum % 3) {
				case 1:
					flagU = false;
					objRxU = SCREEN_WIDTH + 32;
					objRyU = 6;
					for (i = 3; MAPOBJ_MAX > i; i++) {
						mapObj[i].init(i);
					}
					break;
				case 2:
					flagU = false;
					objRxU = SCREEN_WIDTH + 32;
					objRyU = (rndH / 16) * 8 + 30;
					if (objRyU == 30) { objRyU = 46; }
					for (i = 3; MAPOBJ_MAX > i; i++) {
						mapObj[i].init(i);
					}
					break;
				case 0:
					if (72 > TimerDtmp - TimerUtmp) {
						objTimerD = objTimerU + 128;
					}
					else {
						flagU = false;
						objRxU = SCREEN_WIDTH + 32;
						objRyU = (rndH / 16) * 8 + 30;
						if (objRyU == 30) { objRyU = 54; }
						for (i = 3; MAPOBJ_MAX > i; i++) {
							mapObj[i].init(i);
						}
					}
					break;
				}
			}
		}
	}
}

void StageManager::boss_stage() {
	if (!boss_set) {
		boss.init();
		boss_set = true;
	}

	if (boss.getalive()) {
		stageTimer = STAGE_LIMIT + 2;
	}
	else if (stageTimer > STAGE_LIMIT + 2) {
		if (!bossShot[0].getalive()) {
			boss_set = false;
			stageTimer = 0;
			stageNum++;
		}
	}
	boss.update();
}