//copyright by @kalwalt https://www.kalwaltart.it for @Ecotopiaofart https://twitter.com/Ecotopiaofart please, leave this comment in place!

#pragma once

#include "ofMain.h"
#include <wiringPi.h>
#include <piFace.h>
#include <softPwm.h>
#include "pthread.h"
#include "ofxOsc.h"

#define HOST "192.168.0.255"
#define PORT 12345
#define	PIFACE	200
#define	LED	(PIFACE)
#define	SERVO_1 (PIFACE+1)
#define	SERVO_2 (PIFACE+2)
#define BUTTON  0


class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		void blinkingLed();
		void keyPressed(int key);
		bool sensor0;
			
		bool sensor1;
		bool led;
		int position1;
		int position2;

		ofxOscSender sender;
		ofxOscReceiver receiver;
};
