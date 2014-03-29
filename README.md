Ecotopia-of-art
===============

Project presented at my Master thesis in sculpture with the interactive, kinetic, augmented reality work "Ecotopia of art".
For a description of the project go on my web page: http://www.kalwaltart.it/home/en/artworks/new-media/interattivita/ecotopiaofart

From a point of view of the software and the hardware, i used one RaspberrryPi for controls two servos motors and one arcade button, and one OdroidU3 for the augmented reality application, all the visuals and sounds processing. I used Openframeworks for the visuals stuff and Supercollider for the sound processing. 

Features
--------

Openframeworks addons used:

	ofxThreadedImage by @armadillu (new addon i helped a bit to test)
	ofxXmlSettings 
	ofxTween by @arturoc
	ofxJSON by @bakercp
	ofxOAuth by @pelayo
	ofxTwitter by @pelayo mendez ( i helped in the development for the linux part)
	ofxDna by @s373
	ofx3DModelLoader 
	ofxOpenCv 
	ofxARtoolkitPlus 
	ofxBox2d 
	ofxOsc

OS used: 

	RasperryPi ---> wheezy Raspbian

	OdroidU3 ----> Ubuntu 13.10

The two boards (raspPi and OdroidU3) was connected in a network, so i let you to decide how to. 
I installed the wiringPi lib on my RaspberryPi, because i had trouble to add some .cpp files on the ofxWiringPi addon. So remember to install it.
If you find some part to be improved or you want to suggest some improvements e-mail me or ask in the Openframeworks forum: http://forum.openframeworks.cc/ , also if you have some issue report in github or in the OF forum.
 
OdroidU3 notes:

if you want to try the sound, you need to compile the latest Supercollider from github and install it on the System. Add on the Startup.scd 

>Server.local = s = Server.internal;

otherwise you can't hear the sound ( at least this is needed on the OU3)

This is also a work in progress, it was my thesis but, i hope, it will be performed on other places. When it is activated it send tweets to @Ecotopiaofart https://twitter.com/Ecotopiaofart.

useful links: 

RaspberryPi http://www.raspberrypi.org/
	
OdroidU3 http://www.hardkernel.com/

		




