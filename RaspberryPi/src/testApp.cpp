//copyright by @kalwalt https://www.kalwaltart.it for @Ecotopiaofart https://twitter.com/Ecotopiaofart please, leave this comment in place!

#include "testApp.h"
///application for the RaspberryPi controls two servos and one arcade button.

//--------------------------------------------------------------
void testApp::setup(){

ofSetLogLevel(OF_LOG_VERBOSE);

//setting sensor to false, so why are sure that nothing will happens until a button is pressed

sensor0=false;

//setup the ofxOsc sender
sender.setup(HOST, PORT);
cout << "listening for osc messages on port " << PORT << "\n";
receiver.setup(PORT);

//setup the wiringpi, this is special for the piface, we also reset the Led pin to LOW(0)
if(wiringPiSetupSys ()  == -1){
	printf("Error on wiringPi setup\n");}
	//pullUpDnControl (PIFACE , PUD_UP);
	pinMode (SERVO_1, OUTPUT) ;
	pinMode (SERVO_2, OUTPUT) ;
	piFaceSetup (PIFACE) ;
    	digitalWrite    (LED, LOW) ;
	digitalWrite    (SERVO_1, LOW) ;
	digitalWrite    (SERVO_2, LOW) ;
	softPwmCreate (SERVO_1, 0, 200) ;
	softPwmCreate (SERVO_2, 0, 200) ;
	position1 = 187;
	position2 = 187;
}

//this is the function that do the led blinking
void testApp::blinkingLed(){
for( int i = 0; i < 3; i++){
	digitalWrite(LED,HIGH);
        delay(500);
        digitalWrite(LED,LOW);
        delay(500);
        }
        led = false;
        sensor0=false;
        }


//--------------------------------------------------------------
void testApp::update(){

//when the button is pressed sensor0 0 true, and we sent an osc message like this: /buttonPressed 1 ( we can only send int type so this means that is true)
//if(digitalRead(PIFACE+BUTTON) == LOW){
if(digitalRead(PIFACE) == HIGH){
	sensor0=true;
	led = true;
	ofxOscMessage m;
	m.setAddress("/buttonPressed");
	m.addIntArg(1);
	sender.sendMessage(m);

} else {

	ofxOscMessage m;
	m.setAddress("/buttonPressed");
	m.addIntArg(0);
	sender.sendMessage(m);
	sensor0=false;
}
/*
while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);

		// check for mouse moved message
		if(m.getAddress() == "/servo/position1"){
		position1 =ofMap((float) m.getArgAsFloat(0), 0, 6, 180, 194);
		softPwmWrite(SERVO_1, position1);
		//cout << position << endl;
		}
		// check for mouse moved message
		if(m.getAddress() == "/servo/position1"){
		position2 =ofMap((float) m.getArgAsFloat(0), 0, 6, 180, 194);
		softPwmWrite(SERVO_2, position2);
		//cout << position << endl;
		}
		}
*/
ofSeedRandom();
softPwmWrite(SERVO_1, ofRandom(120,194));
softPwmWrite(SERVO_2, ofRandom(120,194));
delay(200);
}

//--------------------------------------------------------------
void testApp::draw(){

ofBackground(ofColor(0,0,0));
ofSetColor(190);
ofDrawBitmapString("position:"+ ofToString(position1 ),10,500);
//when button is pressed we are informed with a message on the window and with the led blinking
if(sensor0 == true){
	ofDrawBitmapString("Sensor at pin 0 activated",50,50);
	blinkingLed();
	sensor0=false;

}

}

void testApp::keyPressed(int key){

switch (key){

	case 'a':
		position1 --;
    		if(position1 < 180) position1 = 180;
    		softPwmWrite(SERVO_1, position1);
    		break;
	case 'd':
		position1 ++;
    		if(position1 > 194) position1 = 194;
		softPwmWrite(SERVO_1, position1);
		break;
	case 'z':
		position2 --;
    		if(position2 < 180) position2 = 180;
    		softPwmWrite(SERVO_2, position2);
    		break;
	case 'c':
		position2 ++;
    		if(position2 > 194) position2 = 194;
		softPwmWrite(SERVO_2, position2);
		break;
	}

}
