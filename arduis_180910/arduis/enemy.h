#ifndef ENEMY_H
#define ENEMY_H

class Enemy {
private:
	byte x, y;
	byte w;
	byte angle;
	byte timerPriv;
	byte framePriv;

	void initE1();
	void initE2();
	void update2();
	void updateE1();
	void updateE2();
	void dead();
public:
	bool getalive() const;
	void sethit() { timerPriv = 128; }
	byte gettimer() const { return timerPriv; }
	byte getx() const { return x - 4; }
	byte gety() const { return y; }
	byte getw() const { return w; }

	void initialize();
	void init();
	void update();
};

class Capsule {
private:
	byte x, y;
	byte w;
	bool hit;
	bool alive;
public:
	bool getalive() const { return alive; }
	void sethit() { hit = true; }
	byte getx() const { return x - 4; }
	byte gety() const { return y; }
	byte getw() const { return w; }

	void initialize();
	void init(byte, byte);
	void update();
};

class MapObj {
private:
	byte x, y;
	byte cx;
	byte w, h;
	bool hit;
	bool alive;
	byte life;
	byte i, p;
	byte n;
	byte angle;
	byte timerPriv;
	byte framePriv;
	byte parts;
	bool type;

	void initS1();
	void initS2();
	void initS3();
	void updateS1();
	void updateS2();
	void updateS2EnemyU();
	void updateS2EnemyD();
	void updateS3();
	void updateS3EnemyMouth();
	void updateS3EnemyShot();
public:
	bool getType() const { return type; }
	bool getalive() const { return alive; }
	void sethit() { hit = true; }
	byte getx() const { return cx; }
	byte gety() const { return y; }
	byte getw() const { return w; }
	byte geth() const { return h; }

	void initialize();
	void init(byte);
	void update();
	void dead();
};
#endif


