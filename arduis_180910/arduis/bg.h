#ifndef BG_H
#define BG_H

class Title {
private:
	byte p;
	byte timerPriv;
public:
	void update();
	void start();
};

class StarManager {
private:
	bool set;
public:
	void init();
	void update();
};

class Star {
private:
	byte x, y;
public:
	byte type;
	void init();
	void update();
};

#endif


