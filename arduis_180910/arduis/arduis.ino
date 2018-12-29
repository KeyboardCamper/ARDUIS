//#include <SPI.h>
#include <EEPROM.h>
#include <Arduboy2.h>
#include "gamecore.h"

void setup() {
	// put your setup code here, to run once:
	setupcore();

}

void loop() {
	// put your main code here, to run repeatedly:

	if (!(arduboy.nextFrame()))
	{
		return;
	}

	arduboy.clear();
	updatecore();
	arduboy.display();
}
