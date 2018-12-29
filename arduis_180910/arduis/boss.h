#ifndef BOSS_H
#define BOSS_H

class Boss {
private:
	byte x, y;
	byte w, h;
	byte cx;
	bool alive;
	byte timerPriv;
	byte framePriv;
	bool moveEnd;
	byte wait;
	bool muki;
	void appearance();
	void attack();
public:
	bool getMoveEnd() const { return moveEnd; }
	bool getalive() const { return alive; }
	byte getx() const { return cx; }
	byte gety() const { return y; }
	byte getw() const { return w; }
	byte geth() const { return h; }

	void initialize();
	void init();
	void update();
	void dead();
};

class BossU {
private:
	byte x, y;
	byte w, h;
public:
	byte getx() const { return x + 4; }
	byte gety() const { return y; }
	byte getw() const { return w; }
	byte geth() const { return h; }

	void update();
};

class BossD {
private:
	byte x, y;
	byte w, h;
public:
	byte getx() const { return x + 4; }
	byte gety() const { return y; }
	byte getw() const { return w; }
	byte geth() const { return h; }

	void update();
};

class BossCore {
private:
	byte x, y;
	byte w, h;
	byte cx;
	bool hit;
	bool alive;
	byte counter;
	byte life;
	byte lifed;
public:
	bool getalive() const { return alive; }
	void sethit() { hit = true; }
	byte getx() const { return cx; }
	byte gety() const { return y; }
	byte getw() const { return w; }
	byte geth() const { return h; }

	void initialize();
	void init();
	void update();
	void dead();
};

class BossExplosion {
private:
	byte x, y;
	bool alive;
	byte timerPriv;
	byte framePriv;
public:
	bool getalive() const { return alive; }
	void clear();
	void init(byte, byte);
	void update();
};
#endif


