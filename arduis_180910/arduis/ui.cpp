#include "gamecore.h"
#include "ui.h"
#include "jiki.h"
#include "arduis_bitmaps.h"

extern Option option[OPTION_MAX];

Ui::Ui() {
}

void Ui::update() {
	static const byte* bitmaps[] = { gaugeEnable, gaugeSpeedUp_1, gaugeSpeedUp_2, gaugeSpeedUp_3,
		gaugeDouble, gaugeLaser, gaugeOption, gaugeBarrier };

	drawRect(0, 60, 12, 4);
	drawRect(16, 60, 12, 4);
	drawRect(32, 60, 12, 4);
	drawRect(48, 60, 12, 4);
	drawRect(64, 60, 12, 4);

	byte x;
	x = (gauge - 1) * 16;
	fillRect(x, 60, 12, 4);

	switch (gauge) {
	case 1:
		name = playerSpeed +1;
		if (name > 3) { name = 1; }
		break;
	case 2:
		name = 0;
		if (shotType != SHOT_DOUBLE) { name = 4;	}
		break;
	case 3:
		name = 0;
		if (shotType != SHOT_LASER) { name = 5;	}
		break;
	case 4:
		name = 0;
		if (4 > optionTotal) { name = 6;	}
		break;
	case 5:
		name = 0;
		if (!barrierAlive) { name = 7; }
		break;
	}
	drawBitmap(84, 60, bitmaps[name], 36, 8);

	drawBitmap(0, 0, scoreIcon, 8, 8);
	scoreDisp(score);
}

void Ui::powerup() {
	switch (gauge) {
	case 1:
		playerSpeed++;
		if (playerSpeed > 3) { playerSpeed = 1;	}
		name = 0;
		gauge = 0;
		break;
	case 2:
		if (shotType != SHOT_DOUBLE) {
			shotType = SHOT_DOUBLE;
			shotTotal = 2 + (2 * (optionTotal + 1));	// (SHOT_MAX / 5) + (SHOT_MAX / 5) * (optionTotal + 1);
			rapidMax = 1;
			name = 0;
			gauge = 0;
		}
		break;
	case 3:
		if (shotType != SHOT_LASER) {
			shotType = SHOT_LASER;
			shotTotal = 1 + (1 * (optionTotal + 1));	// (SHOT_MAX / SHOT_MAX) + (SHOT_MAX / SHOT_MAX) * (optionTotal + 1);
			rapidMax = 1;
			name = 0;
			gauge = 0;
		}
		break;
	case 4:
		if (4 > optionTotal) {
			option[optionTotal].init(ox[optionTotal], oy[optionTotal]);
			optionTotal++;
			switch (shotType) {
			case SHOT_NORMAL:
				shotTotal = 2 + (2 * (optionTotal + 1));	// (SHOT_MAX / 5) + (SHOT_MAX / 5) * (optionTotal + 1);
				break;
			case SHOT_DOUBLE:
				shotTotal = 2 + (2 * (optionTotal + 1));	// (SHOT_MAX / 5) + (SHOT_MAX / 5) * (optionTotal + 1);
				break;
			case SHOT_LASER:
				shotTotal = 1 + (1 * (optionTotal + 1));	// (SHOT_MAX / SHOT_MAX) + (SHOT_MAX / SHOT_MAX) * (optionTotal + 1);
				break;
			}
			name = 0;
			gauge = 0;
		}
		break;
	case 5:
		if (!barrierAlive) {
			barrierAlive = true;
			name = 0;
			gauge = 0;
		}
		break;
	}

}