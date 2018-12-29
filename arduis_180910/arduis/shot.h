#ifndef SHOT_H
#define SHOT_H

class ShotManager {
private:
	byte shotCount[5];
	void init2();
public:
	void initialize();
	void init();
	void update();
	void enemyShotManager(byte, byte);
	void enemyShotManager2(byte, byte);
};

class Shot{
private:
	byte x, y;
	byte w, h;
	byte l;
	byte laserLength;
	byte cx;
	bool hit;
	bool alive;
	bool btnRelease;
	byte i;
	byte name;
public:
	bool getalive() const { return alive; }
	void sethit() { hit = true; }
	byte getx(bool) const;
	byte gety() const { return y; }
	byte getw(bool) const;
	byte geth(bool) const;
	byte getname() const { return name; }

	void init(byte, byte, byte);
	void update();
	void updateN();
	void updateD();
	void updateL();
	void dead();
};

class BossShot {
private:
	byte x, y;
	byte w, h;
	bool hit;
	bool alive;
public:
	bool getalive() const { return alive; }
	void sethit() { hit = true; }
	byte getx() const { return x - 6; }
	byte gety() const { return y; }
	byte getw() const { return w; }
	byte geth() const { return h; }

	void init(byte, byte);
	void update();
	void dead();
};

class EnemyShot {
private:
	byte x, y;
	byte w;
	bool hit;
	bool alive;
	byte angle;
public:
	bool getalive() const { return alive; }
	void sethit() { hit = true; }
	byte getx() const { return x - 4; }
	byte gety() const { return y; }
	byte getw() const { return w; }
	byte geth() const { return w; }

	void init(byte, byte);
	void update();
	void dead();
};

class EnemyShot2 {
private:
	byte x, y;
	byte w;
	bool hit;
	bool alive;
	byte angle;
	byte timerPriv;
	byte framePriv;
public:
	bool getalive() const { return alive; }
	void sethit() { hit = true; }
	byte getx() const { return x - 4; }
	byte gety() const { return y; }
	byte getw() const { return w; }
	byte geth() const { return w; }

	void init(byte, byte);
	void update();
	void dead();
};

class Barrier {
private:
	byte x, y;
	byte w;
	bool hit;
	bool alive;
	bool moveEnd;
public:
	bool getalive() const { return alive; }
	void sethit() { hit = true; }
	byte getx() const { return x - 4; }
	byte gety() const { return y; }
	byte getw() const { return w; }

	void init(byte);
	void update(byte);
	void dead();
};
#endif


