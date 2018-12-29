#ifndef JIKI_H
#define JIKI_H

class Jiki{
private:
	byte x, y;
	byte w, h;
	bool hit;
	bool alive;
	byte framePriv;
	byte timerPriv;
	bool move;
	byte rapid;
	byte counter;
public:
	bool getalive() const { return alive; }
	void sethit() { hit = true; }
	bool getmove() const { return move; }
	byte getx() const { return x - 8; }
	byte gety() const { return y; }
	byte getw() const { return w; }
	byte geth() const { return h; }
	Jiki();
	void initialize();
	void update();
	void dead();
};

class Option {
private:
	byte x, y;
	bool alive;
public:
	bool getalive() const { return alive; }
	byte getx() const { return x; }
	byte gety() const { return y; }
	void init(byte, byte);
	void update(byte, byte);
	void dead();
};
#endif


