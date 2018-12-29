#ifndef STAGE_H
#define STAGE_H

class StageManager {
private:
	byte enemyTimer;
	byte objTimerU;
	byte objTimerD;
	byte objRxU, objRyU;
	byte objRxD, objRyD;
	bool flagU, flagD;
	byte stageTimer;
	bool boss_set;
public:
	byte getObjRxU() const { return objRxU; }
	byte getObjRyU() const { return objRyU; }
	byte getObjRxD() const { return objRxD; }
	byte getObjRyD() const { return objRyD; }
	bool getFlagU() const { return flagU; }
	bool getFlagD() const { return flagD; }
	void setobjTimerU() { objTimerU = (rndW % 32) * 8; }
	void setobjTimerD() { objTimerD = (rndW % 32) * 8; }
	void initialize();
	void update();
	void setup();
	void stage();
	void boss_stage();
};
#endif


