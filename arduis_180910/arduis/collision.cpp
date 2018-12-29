#include "collision.h"
#include "gamecore.h"
#include "jiki.h"
#include "enemy.h"
#include "boss.h"
#include "shot.h"

extern Jiki jiki;
extern Shot shot[SHOT_MAX];
extern EnemyShot enemyShot[ENEMY_SHOT_MAX];
extern EnemyShot2 enemyShot2[ENEMY_IONRING_MAX];
extern BossShot bossShot[4];
extern Barrier barrier[2];
extern Enemy enemy;
extern MapObj mapObj[MAPOBJ_MAX];
extern Boss boss;
extern BossU bossU;
extern BossD bossD;
extern BossCore bossCore;
extern Capsule capsule;
extern Barrier barrier[2];
byte i = 0;
byte p = 0;

void Collision::check() {
	for (i = 0; shotTotal > i; i++) {
		if (enemy.getalive() && shot[i].getalive()) {
			if (abs(enemy.getw() + shot[i].getw(TYPE_NORMAL)) > abs(enemy.getx() - shot[i].getx(TYPE_NORMAL)) &&
				abs(enemy.getw() + shot[i].geth(TYPE_NORMAL)) > abs(enemy.gety() - shot[i].gety())) {
				enemy.sethit();
				shot[i].sethit();
			}
		}
		for (p = 0; ENEMY_IONRING_MAX > p; p++) {
			if (enemyShot2[p].getalive() && shot[i].getalive()) {
				if (abs(enemyShot2[p].getw() + shot[i].getw(TYPE_NORMAL)) > abs(enemyShot2[p].getx() - shot[i].getx(TYPE_NORMAL)) &&
					abs(enemyShot2[p].getw() + shot[i].geth(TYPE_NORMAL)) > abs(enemyShot2[p].gety() - shot[i].gety())) {
					enemyShot2[p].sethit();
					shot[i].sethit();
				}
			}
		}
		for (p = 0; MAPOBJ_MAX > p; p++) {
			if (mapObj[p].getalive() && shot[i].getalive()) {
				if (abs(mapObj[p].getw() + shot[i].getw(mapObj[p].getType())) > abs(mapObj[p].getx() - shot[i].getx(mapObj[p].getType())) &&
					abs(mapObj[p].geth() + shot[i].geth(mapObj[p].getType())) > abs(mapObj[p].gety() - shot[i].gety())) {
					mapObj[p].sethit();
					shot[i].sethit();
				}
			}
		}
		if (bossCore.getalive() && shot[i].getalive()) {
			if (abs(bossU.getw() + shot[i].getw(TYPE_MUTEKI)) > abs(bossU.getx() - shot[i].getx(TYPE_MUTEKI)) &&
				abs(bossU.geth() + shot[i].geth(TYPE_MUTEKI)) > abs(bossU.gety() - shot[i].gety())) {
				shot[i].sethit();
			}
			if (abs(bossD.getw() + shot[i].getw(TYPE_MUTEKI)) > abs(bossD.getx() - shot[i].getx(TYPE_MUTEKI)) &&
				abs(bossD.geth() + shot[i].geth(TYPE_MUTEKI)) > abs(bossD.gety() - shot[i].gety())) {
				shot[i].sethit();
			}
			if (abs(bossCore.getw() + shot[i].getw(TYPE_NORMAL)) > abs(bossCore.getx() - shot[i].getx(TYPE_NORMAL)) &&
				abs(bossCore.geth() + shot[i].geth(TYPE_NORMAL)) > abs(bossCore.gety() - shot[i].gety())) {
				bossCore.sethit();
				shot[i].sethit();
			}
		}
	}

	for (i = 0; ENEMY_SHOT_MAX > i; i++) {
		if (enemyShot[i].getalive()) {
			if (abs(enemyShot[i].getw() + jiki.getw()) > abs(enemyShot[i].getx() - jiki.getx()) &&
				abs(enemyShot[i].getw() + jiki.geth()) > abs(enemyShot[i].gety() - jiki.gety())) {
				jiki.sethit();
			}
		}
		for (p = 0; 2 > p; p++) {
			if (enemyShot[i].getalive() && barrier[p].getalive()) {
				if (abs(enemyShot[i].getw() + barrier[p].getw()) > abs(enemyShot[i].getx() - barrier[p].getx()) &&
					abs(enemyShot[i].geth() + barrier[p].getw()) > abs(enemyShot[i].gety() - barrier[p].gety())) {
					enemyShot[i].sethit();
					barrier[p].sethit();
				}
			}
		}
		/*
		for (p = 0; MAPOBJ_MAX > p; p++) {
			if (enemyShot[i].getalive() && mapObj[p].getalive()) {
				if (abs(enemyShot[i].getw() + mapObj[p].getw()) > abs(enemyShot[i].getx() - mapObj[p].getx()) &&
					abs(enemyShot[i].geth() + mapObj[p].geth()) > abs(enemyShot[i].gety() - mapObj[p].gety())) {
					enemyShot[i].sethit();
				}
			}
		}
		*/
	}

	if (enemy.getalive()) {
		if (abs(enemy.getw() + jiki.getw()) > abs(enemy.getx() - jiki.getx()) &&
			abs(enemy.getw() + jiki.geth()) > abs(enemy.gety() - jiki.gety())) {
			enemy.sethit();
			jiki.sethit();
		}
	}
	if (bossCore.getalive()) {
		if (abs(bossU.getw() + jiki.getw()) > abs(bossU.getx() - jiki.getx()) &&
			abs(bossU.geth() + jiki.geth()) > abs(bossU.gety() - jiki.gety())) {
			jiki.sethit();
		}
		if (abs(bossD.getw() + jiki.getw()) > abs(bossD.getx() - jiki.getx()) &&
			abs(bossD.geth() + jiki.geth()) > abs(bossD.gety() - jiki.gety())) {
			jiki.sethit();
		}
		if (abs(bossCore.getw() + jiki.getw()) > abs(bossCore.getx() - jiki.getx()) &&
			abs(bossCore.geth() + jiki.geth()) > abs(bossCore.gety() - jiki.gety())) {
			bossCore.sethit();
			jiki.sethit();
		}
		for (i = 0; 2 > i; i++) {
			if (barrier[i].getalive()) {
				if (abs(bossU.getw() + barrier[i].getw()) > abs(bossU.getx() - barrier[i].getx()) &&
					abs(bossU.geth() + barrier[i].getw()) > abs(bossU.gety() - barrier[i].gety())) {
					barrier[i].sethit();
				}
				if (abs(bossD.getw() + barrier[i].getw()) > abs(bossD.getx() - barrier[i].getx()) &&
					abs(bossD.geth() + barrier[i].getw()) > abs(bossD.gety() - barrier[i].gety())) {
					barrier[i].sethit();
				}
				if (abs(bossCore.getw() + barrier[i].getw()) > abs(bossCore.getx() - barrier[i].getx()) &&
					abs(bossCore.geth() + barrier[i].getw()) > abs(bossCore.gety() - barrier[i].gety())) {
					bossCore.sethit();
					barrier[i].sethit();
				}
			}
		}
	}

	for (i = 0; 2 > i; i++) {
		if (enemy.getalive() && barrier[i].getalive()) {
			if (abs(enemy.getw() + barrier[i].getw()) > abs(enemy.getx() - barrier[i].getx()) &&
				abs(enemy.getw() + barrier[i].getw()) > abs(enemy.gety() - barrier[i].gety())) {
				enemy.sethit();
				barrier[i].sethit();
			}
		}
	}

	for (i = 0; 4 > i; i++) {
		if (bossShot[i].getalive()) {
			if (abs(bossShot[i].getw() + jiki.getw()) > abs(bossShot[i].getx() - jiki.getx()) &&
				abs(bossShot[i].geth() + jiki.geth()) > abs(bossShot[i].gety() - jiki.gety())) {
				bossShot[i].sethit();
				jiki.sethit();
			}
		}
		for (p = 0; 2 > p; p++) {
			if (bossShot[i].getalive() && barrier[p].getalive()) {
				if (abs(bossShot[i].getw() + barrier[p].getw()) > abs(bossShot[i].getx() - barrier[p].getx()) &&
					abs(bossShot[i].geth() + barrier[p].getw()) > abs(bossShot[i].gety() - barrier[p].gety())) {
					bossShot[i].sethit();
					barrier[p].sethit();
				}
			}
		}
	}

	for (i = 0; MAPOBJ_MAX > i; i++) {
		if (mapObj[i].getalive()) {
			if (abs(mapObj[i].getw() + jiki.getw()) > abs(mapObj[i].getx() - jiki.getx()) &&
				abs(mapObj[i].geth() + jiki.geth()) > abs(mapObj[i].gety() - jiki.gety())) {
				mapObj[i].sethit();
				jiki.sethit();
			}
		}
		for (p = 0; 2 > p; p++) {
			if (mapObj[i].getalive() && barrier[p].getalive()) {
				if (abs(mapObj[i].getw() + barrier[p].getw()) > abs(mapObj[i].getx() - barrier[p].getx()) &&
					abs(mapObj[i].geth() + barrier[p].getw()) > abs(mapObj[i].gety() - barrier[p].gety())) {
					mapObj[i].sethit();
					barrier[p].sethit();
				}
			}
		}
	}

	if (capsule.getalive()) {
		if (abs(capsule.getw() + jiki.getw()) > abs(capsule.getx() - jiki.getx()) &&
			abs(capsule.getw() + jiki.geth()) > abs(capsule.gety() - jiki.gety())) {
			capsule.sethit();
		}
	}
}